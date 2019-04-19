open Shared.Types;

module GQL = Graphql_lwt;

let song =
  GQL.Schema.(
    obj("song", ~fields=_ =>
      [
        field(
          "id", ~args=Arg.[], ~typ=non_null(int), ~resolve=({ctx: ()}, p) =>
          p.id
        ),
        field(
          "name", ~args=Arg.[], ~typ=non_null(string), ~resolve=(_ctx, p) =>
          p.name
        ),
        field(
          "lang", ~args=Arg.[], ~typ=non_null(string), ~resolve=(_ctx, p) =>
          p.lang
        ),
        field(
          "lyrics",
          ~args=Arg.[],
          ~typ=non_null(list(non_null(string))),
          ~resolve=(_ctx, p) =>
          p.lyrics
        ),
      ]
    )
  );

let schema =
  GQL.Schema.(
    schema([
      io_field(
        "schedule",
        ~args=Arg.[],
        ~typ=non_null(list(non_null(song))),
        ~resolve=(_ctx, ()) =>
        Lwt_result.return(DB.schedule)
      ),
    ])
  );