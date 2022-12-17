#!/bin/bash

DIR_BASE=$(pwd)
echo ${DIR_BASE}

cd build
cmake -DCMAKE_BUILD_TYPE=Debug .. 
make -j5
cd ..