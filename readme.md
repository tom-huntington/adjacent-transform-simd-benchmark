Adjacent Transform SIMD Benchmark

Answers my [SO question](https://stackoverflow.com/q/73603420/11998382) whether adjacent transform can be speed up in SIMD by loading the data one once.

NUM_FLOATS = 1 << 8
```
Run on (4 X 3299.05 MHz CPU s)
CPU Caches:
  L1 Data 32 KiB (x4)
  L1 Instruction 32 KiB (x4)
  L2 Unified 256 KiB (x4)
  L3 Unified 6144 KiB (x1)
Load Average: 0.30, 0.15, 0.05
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_adjacent_load_twice       13.4 ns         13.4 ns     51912108
BM_adjacent_load_once        20.0 ns         20.0 ns     34998915
```

NUM_FLOATS = 1 << 16
```
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_adjacent_load_twice      15353 ns        15353 ns        43726
BM_adjacent_load_once       14747 ns        14747 ns        47232
```

NUM_FLOATS = 1 << 24
```
-----------------------------------------------------------------
Benchmark                       Time             CPU   Iterations
-----------------------------------------------------------------
BM_adjacent_load_twice   17027173 ns     17027210 ns           41
BM_adjacent_load_once    16796627 ns     16796678 ns           41
```
