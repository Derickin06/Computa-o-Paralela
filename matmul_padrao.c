#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {

    //Iniciando matrizes

    int N = 1024;

    double* A = malloc(N * N * sizeof(double));
    double* B = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }
    // iniciando matriz resultante C:
    double* C = malloc(N * N * sizeof(double));

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);


     for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                C[i * N + j] += A[i * N + k] * B[k * N + j];
            }
        }
    }

     clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    long long elapsed =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);

    printf("Tempo: %lld ns\n", elapsed);

    return 0;
}
