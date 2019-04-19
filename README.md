# credo

ReasonML full-stack repo for church service presentation

## Run Project with Server

```sh
yarn install
yarn dev
```

To run with the Parcel server run `yarn dev` and view in the browser at http://localhost:1234. Running in this environment provides hot reloading and support for routing; just edit and save the file and the browser will automatically refresh.

## Build for Production

```sh
yarn clean
```

**To enable dead code elimination**, change `bsconfig.json`'s `package-specs` `module` from `"commonjs"` to `"es6"`. Then re-run the above command. This will allow Parcel to remove unused code.
