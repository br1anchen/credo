open Shared.Types;

module Schedule = {
  module ScheduleQuery = [%graphql
    {|
      {
        schedule @bsRecord {
          id
          name
          lang
          lyrics
        }
      }
    |}
  ];

  let query = ScheduleQuery.make();

  type data = {. "schedule": schedule};

  [@react.component]
  let make = (~data) => {
    <div>
      {Array.map(
         song =>
           <div key={song.id |> string_of_int}>
             {ReasonReact.string(song.name)}
           </div>,
         data##schedule,
       )
       |> ReasonReact.array}
    </div>;
  };
};

module GraphQLSchedule = Loader.F(Schedule);