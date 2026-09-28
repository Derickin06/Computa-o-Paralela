#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

int thread_count;

typedef struct {
    int inicio;
    int fim;
    int N;
    int bloco;

    double *A;
    double *B;
    double *C;
} dados_thread;


/*
 * Multiplicação de matrizes com blocagem
 */
void* mul_padrao(void* arg) {

    dados_thread* dados = (dados_thread*)arg;

    int inicio = dados->inicio;
    int fim = dados->fim;
    int N = dados->N;
    int bloco = dados->bloco;



    /*
     * ii -> blocos das linhas
     * kk -> blocos da dimensão K
     * jj -> blocos das colunas
     */
    for (int ii = inicio; ii < fim; ii += bloco) {

        int i_fim = ii + bloco;

        if (i_fim > fim) {
            i_fim = fim;
        }

        for (int kk = 0; kk < N; kk += bloco) {

            int k_fim = kk + bloco;

            if (k_fim > N) {
                k_fim = N;
            }

            for (int jj = 0; jj < N; jj += bloco) {

                int j_fim = jj + bloco;

                if (j_fim > N) {
                    j_fim = N;
                }

                /*
                 * Multiplicação dentro do bloco
                 */
                for (int i = ii; i < i_fim; i++) {

                    for (int k = kk; k < k_fim; k++) {

                        double Aik = dados->A[i * N + k];

                        for (int j = jj; j < j_fim; j++) {

                            dados->C[i * N + j] +=
                                Aik * dados->B[k * N + j];
                        }
                    }
                }
            }
        }
    }

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

    if (argc < 3) {
       // printf("Uso: %s <N> <numero_threads>\n", argv[0]);
        return 1;
    }


    pthread_t* thread_handles;

    int N = strtol(argv[1], NULL, 10);

    thread_count = strtol(argv[2], NULL, 10);


    if (N <= 0 || thread_count <= 0) {

       // printf("N e numero de threads devem ser maiores que zero.\n");

        return 1;
    }


    /*
     * Calcula o tamanho utilizado para a blocagem.
     *
     * 3 matrizes:
     *
     * A -> N * N * sizeof(double)
     * B -> N * N * sizeof(double)
     * C -> N * N * sizeof(double)
     *
     * Portanto:
     *
     * Bl = 3 * (N * N * sizeof(double))
     */
    long Bl = 3 * (N * N * sizeof(double));


    /*
     * Bl está em bytes.
     *
     * Para transformar esse valor em uma dimensão
     * de bloco, usamos a raiz quadrada.
     *
     * Exemplo:
     *
     * bloco ≈ sqrt(Bl / sizeof(double))
     */
    int bloco = (int)sqrt(
        (double)Bl / sizeof(double)
    );


    /*
     * Garante que o bloco seja pelo menos 1
     */
    if (bloco < 1) {
        bloco = 1;
    }


    /*
     * Não deixa o bloco ser maior que N
     */
    if (bloco > N) {
        bloco = N;
    }


    //printf("N = %d\n", N);
    //printf("Threads = %d\n", thread_count);
    //printf("Bl = %ld bytes\n", Bl);
    //printf("Tamanho do bloco = %d\n\n", bloco);


    /*
     * Alocação
     */
    dados_thread dados[thread_count];

    thread_handles =
        malloc(thread_count * sizeof(pthread_t));


    double* A =
        malloc(N * N * sizeof(double));

    double* B =
        malloc(N * N * sizeof(double));

    double* C =
        malloc(N * N * sizeof(double));


    if (A == NULL ||
        B == NULL ||
        C == NULL ||
        thread_handles == NULL) {

        printf("Erro na alocacao de memoria.\n");

        free(A);
        free(B);
        free(C);
        free(thread_handles);

        return 1;
    }


    /*
     * Inicialização das matrizes
     */
    for (int i = 0; i < N; i++) {

        for (int j = 0; j < N; j++) {

            A[i * N + j] = (double)(i + j);

            B[i * N + j] = (double)(i * j);

            C[i * N + j] = 0.0;
        }
    }


    /*
     * Divide as linhas da matriz C
     * entre as threads.
     */
    int intervalo = N / thread_count;

    // time inicializado
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);

    for (int i = 0; i < thread_count; i++) {
        dados[i].inicio = i * intervalo;  
        if (i == thread_count - 1) {
            dados[i].fim = N;

        } else {
            dados[i].fim =
                (i + 1) * intervalo;
        }

        dados[i].N = N;
        dados[i].bloco = bloco;
        dados[i].A = A;
        dados[i].B = B;
        dados[i].C = C;

        int resultado = pthread_create(
            &thread_handles[i],
            NULL,
            mul_padrao,
            &dados[i]
        );
        if (resultado != 0) {
            printf(
                "Erro ao criar thread %d.\n",
                i
            );
         free(A);
            free(B);
            free(C);
            free(thread_handles);

            return 1;
        }
    }
    /*
     * Espera todas as threads terminarem
     */
    for (int i = 0; i < thread_count; i++) {
        pthread_join(
            thread_handles[i],
            NULL
        );
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);

    long long elapsed =
        (end.tv_sec - start.tv_sec) * 1000000000LL +
        (end.tv_nsec - start.tv_nsec);

    printf("Tempo: %lld ns\n", elapsed);

    // print_matriz(C, N);
    return 0;
}
