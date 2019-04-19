# credo

ReasonML full-stack repo for church service presentation

## Run front-end with Server

```sh
yarn install
yarn dev
```

To run with the Parcel server run `yarn dev` and view in the browser at http://localhost:1234. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

## Build front-end for Production

```sh
yarn build
```

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above command. This will allow Parcel to remove unused code.

## Run back-end server

**Note**: _it's a quiet startup; check http://localhost:8080/graphql to see that it's running!_

- `npm install -g esy`
- `esy @server`
- `esy @server x credo`

## Neat tricks

- GraphQL schema fully defined in Reason (see [`src/server/schema.re`](./src/server/schema.re))
- There's also a GraphiQL instance at `localhost:8080/graphql` for exploring and
  playing with the queries and mutations.

## License

MIT
