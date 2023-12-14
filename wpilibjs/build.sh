#!/usr/bin/env bash

# if want to change to including bindings in source files, use this https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html?highlight=javascript%20library#binding-libraries

# run this from in the wpilibjs directory

source ./emsdk/emsdk_env.sh

mkdir -p build && cd build

export CFLAGS="-Wno-error"
export CXXFLAGS="-Wno-error"

# get makefiles
# -DLIBSSH_INCLUDE_DIRS=/opt/homebrew/libssh/0.10.5_1/include -DLIBSSH_LIBRARIES=/opt/homebrew/libssh/0.10.5_1/lib
emcmake cmake ../.. -DCMAKE_PREFIX_PATH="/opt/homebrew/lib" -DBUILD_SHARED_LIBS=OFF -DFOR_JS=ON -DWITH_JAVA=OFF -DWITH_CSCORE=OFF -DWITH_NTCORE=OFF -DWITH_WPILIB=OFF -DWITH_EXAMPLES=OFF -DWITH_TESTS=OFF -DWITH_GUI=OFF -DWITH_SIMULATION_MODULES=OFF -Wunused-but-set-variable -Wno-error

echo "Project configured"

# get object files
# VERBOSE=1
emmake make  -ij 4 # -f path/to/file/that/overwrites/stupid/env/vars

echo "Project built"

# get html/js/wasm
# i think need to use --post-js instead of --js-library since i'm not calling the functions in the js library from the C++ code yet
# --bind?
# --js-library ../src/library.js
# -s MODULARIZE 
# -s ENVIRONMENT=node\
    # -O3 \
    # --closure 1 should compile with closure once i get stuff working well

    # --js-library ../src/library.js \
    # -s WASM_BIGINT \
emcc \
    --embind-emit-tsd wpilib.d.ts \
    -std=c++20 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -lembind lib/libwpiutil.a lib/libwpimath.a wpilibjs/CMakeFiles/wpilibjs.dir/src/wpilibjs.cpp.o \
    -o wpilib.js
# TODO: this works, but there are weird undefined symbol errors -- weird undefined symbol errors were from me accidentally setting the cmake target as executable instead of library, since setting target executable means it tries to do the linking as well, but we want to do linking via emcc command directly

mv wpilib.{js,wasm,d.ts} ../node_module/public/

echo "Project linked"

# yarn build

echo "JS Built"

# TODO: get typescript definitions