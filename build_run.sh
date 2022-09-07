#!/bin/sh

c++ main.cpp -mavx2 -lfmt -lbenchmark -lpthread -std=c++20 -o adj_simd \
&& ./adj_simd