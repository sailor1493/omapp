#include "axpy.h"
#include <omp.h>
#include <stdio.h>

#define smaller_comp(x, y) (x) * (y) + (y) + (x)
#define heavy_comp(x, y) smaller_comp(smaller_comp(x, y), smaller_comp(x, y))

void sequential_axpy(float alpha, float *x, float *y, int N) {
  for (int i = 0; i < N; ++i) {
    float x_ = x[i];
    y[i] = x_ * (alpha + alpha * alpha + alpha * alpha * alpha);
  }
}

void unoptimized_parallel_axpy(float alpha, float *x, float *y, int N) {
#pragma omp parallel for
  for (int i = 0; i < N; ++i) {
    float x_ = x[i];
    y[i] = x_ * (alpha + alpha * alpha + alpha * alpha * alpha);
  }
}

void parallel_axpy(float alpha, float *x, float *y, int N) {
  const int N_ = N;
  const float *x_ = x;
#pragma omp parallel for private(alpha)
  for (int i = 0; i < N_; ++i) {
    float alpha = alpha;
    float xi = x_[i];
    y[i] = xi * (alpha + alpha * alpha + alpha * alpha * alpha);
  }
}
