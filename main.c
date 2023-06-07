#include <getopt.h>
#include <omp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "axpy.h"
#include "util.h"

#define DEFAULT_SIZE 1 << 30

static void print_help(const char *prog_name) {
  printf("Usage: %s [-h] [-t num_threads] [-n num_iterations] [-m mode] N\n",
         prog_name);
  printf("Options:\n");
  printf("     -h : print this page.\n");
  printf("     -t : number of threads (default: 1)\n");
  printf("     -n : number of iterations (default: 1)\n");
  printf("     -m : mode of axpy (default: sequential)\n");
  printf("      N : vector size. (default: %d)\n", DEFAULT_SIZE);
}

static int N = DEFAULT_SIZE;
static int num_threads = 1;
static int num_iterations = 1;

#define SEQUENTIAL 0
#define UNOPT 1
#define OPT 2
static int mode = SEQUENTIAL;

char *modes[3] = {"Sequential", "Unoptimized OpenMP", "Optimized OpenMP"};

static void parse_opt(int argc, char **argv) {
  int c;
  while ((c = getopt(argc, argv, "ht:n:m:")) != -1) {
    switch (c) {
    case 'n':
      num_iterations = atoi(optarg);
      break;
    case 't':
      num_threads = atoi(optarg);
      break;
    case 'm':
      mode = atoi(optarg);
      break;
    case 'h':
    default:
      print_help(argv[0]);
      exit(0);
    }
  }
  for (int i = optind, j = 0; i < argc; ++i, ++j) {
    switch (j) {
    case 0:
      N = atoi(argv[i]);
      break;
    default:
      break;
    }
  }
  printf("Options:\n");
  printf("  Problem size: N = %d\n", N);
  printf("  Number of threads: %d\n", num_threads);
  printf("  Number of iterations: %d\n", num_iterations);
  printf("  Mode: %s\n", modes[mode]);
  printf("\n");
}

int main(int argc, char **argv) {
  parse_opt(argc, argv);

  printf("Initializing... ");
  fflush(stdout);
  float *x, *y;

  // Initialize random seed
  timer_init();

  // Allocate vectors
  alloc_vec(&x, N);
  alloc_vec(&y, N);

  // Set each element to a random value
  rand_vec(x, N);
  rand_vec(y, N);

  printf("done!\n");

  // set function
  void (*axpy)(float, float *, float *, int) = NULL;
  switch (mode) {
  case SEQUENTIAL:
    axpy = sequential_axpy;
    break;
  case UNOPT:
    axpy = unoptimized_parallel_axpy;
    break;
  case OPT:
    axpy = parallel_axpy;
    break;
  default:
    printf("Invalid mode: %d\n", mode);
    exit(1);
  }

  omp_set_num_threads(num_threads);

  // WARMUP
  float alpha = 1.0;
  axpy(alpha, x, y, N);

  double elapsed_time_sum = 0;
  for (int i = 0; i < num_iterations; ++i) {
    printf("Calculating...(iter=%03d) ", i);
    fflush(stdout);

    timer_start(0);
    axpy(alpha, x, y, N);

    double elapsed_time = timer_stop(0);
    printf("%f sec\n", elapsed_time);
    elapsed_time_sum += elapsed_time;
  }

  double elapsed_time_avg = elapsed_time_sum / num_iterations;
  printf("Avg. time: %f sec\n", elapsed_time_avg);
  return 0;
}