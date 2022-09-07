#include <immintrin.h>
#include <stdio.h>
#include "aligned_allocator.hpp"
#include <numeric>
#include <iostream>
#include <fmt/ranges.h>
#include <benchmark/benchmark.h>

void print256ps(__m256& float_vec)
{
    float* flo = (float*) &float_vec;
    printf("%f, %f, %f, %f, %f, %f, %f, %f\n", flo[0], flo[1], flo[2], flo[3], flo[4], flo[5], flo[6], flo[7]);
}

void print(const char* msg, __m256& v)
{
    printf("%s ", msg);
    print256ps(v);
}

constexpr std::size_t NUM_FLOATS = 1 << 24;
constexpr std::size_t BATCH_SIZE = 8;
static_assert(NUM_FLOATS % BATCH_SIZE == 0);
constexpr std::size_t NUM_BATCHES = NUM_FLOATS / BATCH_SIZE;

using vector_type = AlignedVector<float, sizeof(float) * BATCH_SIZE>;

void adjacent_load_once(vector_type& input, vector_type& output)
{
    auto batch_a1 = _mm256_load_ps(input.data());

    for(size_t i = 0; i < NUM_BATCHES; i++)
    {
        auto batch_a0 = batch_a1;
        batch_a1 = _mm256_load_ps(input.data() +  BATCH_SIZE * (i + 1) );
        
        auto permuted = _mm256_permute2x128_si256(batch_a0, batch_a1, 0x21);
        auto batch_b0 =  _mm256_castsi256_ps(_mm256_alignr_epi8(permuted, batch_a0, sizeof(float)));
        auto out_batch = _mm256_add_ps(batch_a0,batch_b0);
        _mm256_store_ps(output.data() + BATCH_SIZE * i, out_batch);
    }
}

void adjacent_load_twice(vector_type& input, vector_type& output)
{
    for(size_t i = 0; i < NUM_BATCHES; i++)
    {
        auto batch_a0 = _mm256_load_ps(input.data() +  BATCH_SIZE * i );
        auto batch_b0 = _mm256_loadu_ps(input.data() +  BATCH_SIZE * i + 1 );
        auto out_batch = _mm256_add_ps(batch_a0, batch_b0);
        _mm256_store_ps(output.data() + BATCH_SIZE * i, out_batch);
    }
}

static void BM_adjacent_load_twice(benchmark::State& state) {

   auto input = vector_type(NUM_FLOATS + BATCH_SIZE);
    std::iota(input.begin(), input.end(), 0);
    auto output = vector_type(NUM_FLOATS);

   for (auto _ : state)
       adjacent_load_twice(input, output);

    //fmt::print("{}\n", output);
}
BENCHMARK(BM_adjacent_load_twice);

static void BM_adjacent_load_once(benchmark::State& state) {

   auto input = vector_type(NUM_FLOATS + BATCH_SIZE);
    std::iota(input.begin(), input.end(), 0);
    auto output = vector_type(NUM_FLOATS);

   for (auto _ : state)
       adjacent_load_once(input, output);

    //fmt::print("{}\n", output);
}
BENCHMARK(BM_adjacent_load_once);


BENCHMARK_MAIN();