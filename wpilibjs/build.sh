#!/usr/bin/env bash

# run this from in the wpilibjs directory
source ./emsdk/emsdk_env.sh

mkdir -p build && cd build

export CFLAGS="-Wno-error"
export CXXFLAGS="-Wno-error"

# get makefiles
# -DLIBSSH_INCLUDE_DIRS=/opt/homebrew/libssh/0.10.5_1/include -DLIBSSH_LIBRARIES=/opt/homebrew/libssh/0.10.5_1/lib
# -DCMAKE_PREFIX_PATH="/opt/homebrew/lib"

    # -DCMAKE_LIBRARY_PATH=/opt/homebrew/opt/protobuf@3/lib \
    # -DProtobuf_INCLUDE_DIR=/opt/homebrew/opt/protobuf@3/include \
    # -DProtobuf_PROTOC_EXECUTABLE=/opt/homebrew/opt/protobuf@3/bin/protoc \

    # -DCMAKE_PREFIX_PATH="/opt/homebrew/opt" \
    # -DCMAKE_LIBRARY_PATH=/usr/local/opt/protobuf@3/lib \
    # -DProtobuf_DIR=/opt/homebrew/opt/protobuf/25.1/lib/cmake/protobuf \
emcmake cmake ../.. \
    -DProtobuf_LIBRARY=1 \
    -DProtobuf_LIBRARIES=/opt/homebrew/opt/protobuf/lib \
    -DProtobuf_INCLUDE_DIR=/opt/homebrew/opt/protobuf/include \
    -DProtobuf_PROTOC_EXECUTABLE=/opt/homebrew/opt/protobuf/bin/protoc \
    -DWITH_JAVA=OFF \
    -DWITH_EXAMPLES=ON \
    -DBUILD_SHARED_LIBS=OFF \
    -DFOR_JS=ON \
    -DWITH_JAVA=OFF \
    -DWITH_CSCORE=OFF \
    -DWITH_NTCORE=OFF \
    -DWITH_WPILIB=OFF \
    -DWITH_EXAMPLES=OFF \
    -DWITH_TESTS=OFF \
    -DWITH_GUI=OFF \
    -DWITH_SIMULATION_MODULES=OFF \
    -Wunused-but-set-variable \
    -Wno-error

echo "Project configured"

# get object files
emmake make  -i -j4

echo "Project built"

# get html/js/wasm
emcc \
    --embind-emit-tsd wpilib.d.ts \
    -std=c++20 \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -lembind lib/libwpiutil.a lib/libwpimath.a wpilibjs/CMakeFiles/wpilibjs.dir/src/wpilibjs.cpp.o \
    -o wpilib.js

mv wpilib.{js,wasm,d.ts} ../node_module/public/

echo "Project linked"

# yarn build

echo "JS Built"

# TODO: get typescript definitions