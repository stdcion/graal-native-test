#!/bin/sh
cmake --preset="conf-mac" -DCMAKE_BUILD_TYPE=Release .
cmake --build --preset="build-mac" --config=Release
