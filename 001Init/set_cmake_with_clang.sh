#!/bin/bash

rm -rf build
mkdir build
cd build

CXX=clang++ CC=clang cmake ..
