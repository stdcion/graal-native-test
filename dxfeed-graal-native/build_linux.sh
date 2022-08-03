#!/bin/sh
cmake --preset="conf-linux" -DCMAKE_BUILD_TYPE=Release .
cmake --build --preset="build-linux" --config=Release
ctest.exe --test-dir build/conf-linux -C Release --extra-verbose
