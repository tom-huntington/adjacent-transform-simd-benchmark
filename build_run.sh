#!/bin/sh

clang++ main.cpp -mavx2 -lfmt -lbenchmark -lpthread -std=c++2b -o adj_simd \
&& ./adj_simd