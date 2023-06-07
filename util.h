#pragma once

void timer_init();

void timer_start(int i);

double timer_stop(int i);

void alloc_vec(float **m, int N);

void rand_vec(float *m, int N);

void zero_vec(float *m, int N);