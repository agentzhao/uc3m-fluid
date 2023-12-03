#!/bin/bash 

mkdir cmake-build-debug && cd cmake-build-debug && cmake .. && cd ..
cmake --build cmake-build-debug
touch out/output.fld
cmake-build-debug/fluid/fluid 1 small.fld out/output.fld
