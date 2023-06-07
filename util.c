#include "util.h"

#include <math.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

static double start_time[8];

void timer_init() { srand(time(NULL)); }

static double get_time() {
  struct timespec tv;
  clock_gettime(CLOCK_MONOTONIC, &tv);
  return tv.tv_sec + tv.tv_nsec * 1e-9;
}

void timer_start(int i) { start_time[i] = get_time(); }

double timer_stop(int i) { return get_time() - start_time[i]; }

void alloc_vec(float **m, int N) {
  *m = (float *)aligned_alloc(32, sizeof(float) * N);
  if (*m == NULL) {
    printf("Failed to allocate memory for mat.\n");
    exit(0);
  }
}

void rand_vec(float *m, int N) {
  unsigned int seeds[64];
  for (int i = 0; i < 64; i++) {
    seeds[i] = rand();
  }

#pragma omp parallel
  {
    int tid = omp_get_thread_num();
    unsigned int seed = seeds[tid];
#pragma omp for
    for (int j = 0; j < N; j++) {
      m[j] = (float)rand_r(&seed) / RAND_MAX - 0.5;
    }
  }
}

void zero_vec(float *m, int N) { memset(m, 0, sizeof(float) * N); }