#pragma once

void sequential_axpy(float alpha, float *, float *y, int N);

void unoptimized_parallel_axpy(float alpha, float *, float *y, int N);

void parallel_axpy(float alpha, float *, float *y, int N);