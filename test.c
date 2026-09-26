#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int inicio;
    int fim;
    int N;
    double *A;
    double *B;
    double *C;
} dados_thread;

void* mul_padrao(void* arg) {
    dados_thread* dados = (dados_thread*)arg;

    printf("Thread iniciou: %d - %d\n",
           dados->inicio,
           dados->fim);

    for (int i = dados->inicio; i < dados->fim; i++) {
        for (int j = 0; j < dados->N; j++) {

            double soma = 0.0;

            for (int k = 0; k < dados->N; k++) {
                soma += dados->A[i * dados->N + k] *
                        dados->B[k * dados->N + j];
            }

            dados->C[i * dados->N + j] = soma;
        }
    }

    printf("Thread terminou: %d - %d\n",
           dados->inicio,
           dados->fim);

    return NULL;
}

void print_matriz(double *matriz, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.2f ", matriz[i * N + j]);
        }
        printf("\n");
    }
}

int main(int argc, char* argv[]) {

    int N = strtol(argv[1], NULL, 10);
    int thread_count = strtol(argv[2], NULL, 10);

    pthread_t* thread_handles =
        malloc(thread_count * sizeof(pthread_t));

    dados_thread dados[thread_count];

    double* A = malloc(N * N * sizeof(double));
    double* B = malloc(N * N * sizeof(double));
    double* C = malloc(N * N * sizeof(double));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
            C[i * N + j] = 0.0;
        }
    }

    int intervalo = N / thread_count;

    for (int i = 0; i < thread_count; i++) {

        dados[i].inicio = i * intervalo;

        if (i == thread_count - 1) {
            dados[i].fim = N;
        } else {
            dados[i].fim = (i + 1) * intervalo;
        }

        dados[i].N = N;
        dados[i].A = A;
        dados[i].B = B;
        dados[i].C = C;

        printf("Criando thread %d: intervalo %d - %d\n",
               i,
               dados[i].inicio,
               dados[i].fim);

        pthread_create(
            &thread_handles[i],
            NULL,
            mul_padrao,
            &dados[i]
        );
    }

    // Espera todas as threads terminarem
    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }

    print_matriz(C, N);

    free(A);
    free(B);
    free(C);
    free(thread_handles);

    return 0;
}