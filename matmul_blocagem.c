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
    //escolhendo tamanho de bloco em cache (Bl):
    long Bl = 3*(N* N * sizeof(double));


    // time inicializado
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for (int ii = 0; ii < N; ii += Bl) {
        for (int jj = 0; jj < N; jj += Bl) {
            for (int kk = 0; kk < N; kk += Bl) {

                //*Multiplicação do bloco Bl x Bl* 
                for (int i = ii; i < ii + Bl && i < N; i++) {
                    for (int k = kk; k < kk + Bl && k < N; k++) {
                        double r = A[i * N + k];
                        for (int j = jj; j < jj + Bl && j < N; j++) {
                            C[i * N + j] += r * B[k * N + j];
                        }
                    }
                }
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