## [Initial Setup](https://emscripten.org/docs/getting_started/downloads.html)
1. Get the emsdk repo - `git clone https://github.com/emscripten-core/emsdk.git`
2. Enter that directory - `cd emsdk`
3. Fetch the latest version of the emsdk (not needed the first time you clone) - `git pull`
4. Download and install the latest SDK tools. - `./emsdk install latest`
5. Make the "latest" SDK "active" for the current user. (writes .emscripten file) - `./emsdk activate latest`
6. Activate PATH and other environment variables in the current terminal - `source ./emsdk_env.sh`
7. Ensure yarn is installed globally via `npm install --global yarn` to use with the npm package.

> ### Note 
> `git pull` will fetch the current list of tags, but very recent ones may not yet be present there. You can run ./emsdk update-tags to update the list of tags directly.


## Building

To build the necessary files, run the `build.sh` script from the wpilibjs directory. This will generate WASM, JS, and TS. Run the tests on the generated code by going into the node_module directory via `cd node_module` and running `yarn test`. To then publish the package, ensure the version number is incremented in `package.json` and run `npm publish --access public`.


## Structure

The outputs we actually use from building WPILib are a WASM file, a JavaScript file to load and provide proper bindings for said WASM file, and a TypeScript module file to provide type definitions. These files live inside the public folder of the node module, meaning they will be served from the root of the web server by Vite convention. This allows for the WASM to be loaded properly without modifying the Emscripten source code.

`index.ts` contains all the code to instantiate and distribute the generated code, allowing for easier use.


## Usage

This package should be used simply as any other node module, with the caveat that some functions may require type casting, as I'm not aware of a way to get Emscripten to properly type functions that return `emscripten::val`. Regardless, you can be assured that any such function will be returning a mathjs `Unit` object. This will appear in the typing as a function that returns `any`.

Another thing to note, constructors in general are mapped as closely as possible to the WPILib C++ counterparts, but once again if an argument is typed as `any`, it's always a mathjs `Unit`.


## Future Plans

### Units Library

May eventually expose all the functions directly without any shim for the units library in case people want to use their own stuff for that. That would kind of look like this for the unit bindings.

```
class_<units::meter_t>("Meter")
    .constructor<double>()
    .function("value", &units::meter_t::to<double>)
    ;
```

### Units Typing

Although mathjs does provide typing for units via the `Unit` class, I've not found a way to get this to be reflected in the generated TypeScript module. There is a way to define type bindings for `emscripten::val` in the source code, but at current it seems I would still have to manually duplicate the typings from mathjs into there, which is less than ideal.


### Modularity

Although the code is divided into the corresponding WPILib packages and such, the WASM is still currently bundled with the code even if the module is not used. The solution to this might be to have each WPILib module have it's own NPM package, but at current that is unscoped.