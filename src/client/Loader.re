module type Config = {
  type data;
  let query: {
    .
    "parse": Js.Json.t => data,
    "query": string,
    "variables": Js.Json.t,
  };

  [@react.component]
  let make: (~data: data) => React.element;
};

let style = ReactDOMRe.Style.make;
let str = ReasonReact.string;

exception Graphql_error(string);

let sendQuery = q =>
  Bs_fetch.(
    fetchWithInit(
      "/graphql",
      RequestInit.make(
        ~method_=Post,
        ~body=
          Js.Dict.fromList([
            ("query", Js.Json.string(q##query)),
            ("variables", q##variables),
          ])
          |> Js.Json.object_
          |> Js.Json.stringify
          |> BodyInit.make,
        ~credentials=Include,
        ~headers=
          HeadersInit.makeWithArray([|
            ("content-type", "application/json"),
          |]),
        (),
      ),
    )
    |> Js.Promise.then_(resp =>
         if (Response.ok(resp)) {
           Response.json(resp)
           |> Js.Promise.then_(data =>
                switch (Js.Json.decodeObject(data)) {
                | Some(obj) =>
                  Js.Dict.unsafeGet(obj, "data")
                  |>
                  q##parse
                  |> Js.Promise.resolve
                | None =>
                  Js.Promise.reject(
                    Graphql_error("Response is not an object"),
                  )
                }
              );
         } else {
           Response.text(resp)
           |> Js.Promise.then_(text =>
                Js.Promise.reject(
                  Graphql_error(
                    "Request failed: "
                    ++ string_of_int(Response.status(resp))
                    ++ " "
                    ++ Response.statusText(resp)
                    ++ "\n"
                    ++ text,
                  ),
                )
              );
         }
       )
  );

module F = (Config: Config) => {
  type state =
    | Loading
    | Error(string)
    | Loaded(Config.data);

  [@react.component]
  let make = () => {
    let (status, setStatus) = React.useState(() => Loading);
    React.useEffect0(() => {
      sendQuery(Config.query)
      |> Js.Promise.then_(response =>
           setStatus(_ => Loaded(response)) |> Js.Promise.resolve
         )
      |> Js.Promise.catch(_ =>
           setStatus(_ => Error("Couldn't get todos")) |> Js.Promise.resolve
         )
      |> ignore;
      None;
    });

    switch (status) {
    | Loading =>
      <div
        style={style(~alignItems="center", ~padding="5px", ~color="#ddd", ())}>
        {str("Loading")}
      </div>
    | Error(text) => <div> {str("Error")} {str(text)} </div>
    | Loaded(data) => <Config data />
    };
  };
};