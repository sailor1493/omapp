#include "work.h"
#include <omp.h>
#include <stdio.h>

#define level12(x, y) heavy_computation(x, y)
#define level11(x, y) heavy_computation(level12(x,y), level12(x,y))
#define level10(x, y) heavy_computation(level11(x,y), level11(x,y))
#define level9(x, y) heavy_computation(level10(x,y), level10(x,y))
#define level8(x, y) heavy_computation(level9(x,y), level9(x,y))
#define level7(x, y) heavy_computation(level8(x,y), level8(x,y))
#define level6(x, y) heavy_computation(level7(x,y), level7(x,y))
#define level5(x, y) heavy_computation(level6(x,y), level6(x,y))
#define level4(x, y) heavy_computation(level5(x,y), level5(x,y))
#define level3(x, y) heavy_computation(level4(x,y), level4(x,y))
#define level2(x, y) heavy_computation(level3(x,y), level3(x,y))
#define level1(x, y) heavy_computation(level2(x,y), level2(x,y))
#define level0(x, y) heavy_computation(level1(x,y), level1(x,y))
#define heavy_computation(x, y) ((x) + (y) * (y))

#define N 1 << 4

void init(float a, float b, float *vec, int size) {
  for (int i = 0; i < size; i++) {
    vec[0] = level0(a, b);
  }
}

void unopt_init(float a, float b, float *vec, int size) {
#pragma omp parallel for
  for (int i = 0; i < size; i++) {
    vec[0] =  level0(a, b);
  }
}

void opt_init(float a, float b, float *vec, int size) {
#pragma omp parallel
  {
    const float a_ = a, b_ = b;
#pragma omp for
    for (int i = 0; i < size; i++) {
      vec[0] = level0(a_, b_);
    }
  }
}