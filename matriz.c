#include <stdio.h>
#include <stdlib.h>


/*               OBSERVAÇÕES

Inicialização determinística para matrizes quadradas N x N
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }
 Ordem de Linha (Row-Major) - Excelente Localidade Espacial 
    long pares = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }
 Ordem de Coluna (Column-Major) - Pobre Localidade Espacial

    long pares = 0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }


1. Meça os tempos de execução com alta precisão (clock_gettime) e calcule a razão de desaceleração (slowdown
= Tcoluna/Tlinha).



2. Problema de blocagem:  Multiplicação de Matrizes com Blocagem (Tiling):

    for (int ii = 0; ii < N; ii += B) {
        for (int jj = 0; jj < N; jj += B) {
            for (int kk = 0; kk < N; kk += B) {
                *Multiplicação do bloco B x B* 
                for (int i = ii; i < ii + B && i < N; i++) {
                    for (int k = kk; k < kk + B && k < N; k++) {
                        double r = A[i * N + k];
                        for (int j = jj; j < jj + B && j < N; j++) {
                            C[i * N + j] += r * B[k * N + j];
                        }
                    }
                }
            }
        }
    }







*/







int main() {
    
//Iniciando matrizes

    int N = 512;

    double* A = malloc(N * N * sizeof(double));
    double* B = malloc(N * N * sizeof(double));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

      /*        //    print de teste para matriz(10X10)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", A[i]);
        }
        printf("\n");
    }
    */

   long pares = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares++;
            }
        }
    }
    //printf("%ld \n", pares);

    long pares2 = 0;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if ((int)A[i * N + j] % 2 == 0) {
                pares2++;
            }
        }
    }
    printf("%ld \n", pares2);









    return 0;
}