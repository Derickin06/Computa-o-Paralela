#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// para compilar: gcc -O0 -Wall matmul_blocagem.c -o matmul_blocagem_O0
//para executar: valgrind --tool=cachegrind --cache-sim=yes ./matmul_padrao_O0 N
int main(){

    //Iniciando matrizes

    int N = 1536;

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
 

    for (int i = 0; i < N; i++) {
        for (int k = 0; k < N; k++) {
            double r = A[i * N + k];

            for (int j = 0; j < N; j++) {
            C[i * N + j] += r * B[k * N + j];
            }
        }
    }

    // time inicializado
   // struct timespec start, end;
   // clock_gettime(CLOCK_MONOTONIC_RAW, &start);

   
    /* clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    long long elapsed =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);
    printf("Tempo: %lld ns\n", elapsed);
    */

    return 0;
}