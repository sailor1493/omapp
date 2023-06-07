#include "work.h"
#include <omp.h>
#include <stdio.h>

#define smaller_comp(x, y) (x) * (y) + (y) + (x)
#define heavy_comp(x, y) smaller_comp(smaller_comp(x, y), smaller_comp(x, y))

void vector_init(float a, float b, float *vec, int size) {
  for (int i = 0; i < size; i++) {
    vec[i] = (a + b) * b / (a + b);
  }
}

void unopt_init(float a, float b, float *vec, int size) {
#pragma omp parallel for
  for (int i = 0; i < size; i++) {
    vec[i] = heavy_comp(a, b);
  }
}

void opt_init(float a, float b, float *vec, int size) {
#pragma omp parallel
  {
    float result = heavy_comp(a, b);
#pragma omp for
    for (int i = 0; i < size; i++) {
      vec[i] = result;
    }
  }
}