#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>

int thread_count;


typedef struct {
    int inicio;
    int fim;
    double *A;
    double *B;
    double *C;
} dados_thread;

void* mul_padrao(void* arg){
    dados_thread* dados = (dados_thread*)arg;

    printf("Thread iniciou: %d - %d \n", 
    dados->inicio, 
    dados->fim);


    for(int i = dados->inicio; i <= dados->fim; i++){
        dados->C[i] = dados->A[i] + dados->B[i];
    }

    for (int i = dados->inicio; i < dados->fim; i++) {
        for (int j = dados->inicio; j < dados->fim; j++) {
            for (int k = dados->inicio; k < dados->fim; k++) {
                dados->C[i * dados->fim + j] += dados->A[i * dados->fim + k] * dados->B[k * dados->fim + j];
            }
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

int main(int argc, char* argv[]){

    pthread_t* thread_handles;
    int N = strtol(argv[1], NULL, 10); // tamanho do vetor
    thread_count = strtol(argv[2], NULL, 10); //numero de threads
    dados_thread dados[thread_count];
    thread_handles = malloc(thread_count*sizeof(pthread_t));

    double* A = malloc(N * N * sizeof(double));
    double* B = malloc(N * N * sizeof(double));
    double* C = malloc(N * N * sizeof(double));

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            A[i * N + j] = (double)(i + j);
            B[i * N + j] = (double)(i * j);
        }
    }

    int intervalo = N / thread_count;


    for(int i=0; i < thread_count; i++) {
        dados[i].inicio = i * intervalo;
        if(i == thread_count - 1){
            dados[i].fim = N - 1;
        }else {
            dados[i].fim = (i + 1) * intervalo - 1;
        }
        dados[i].A = A; 
        dados[i].B = B;
        dados[i].C = C;
        printf("Criando thread: %d: intervalo %d - %d \n",
            i,
            dados[i].inicio,
            dados[i].fim);
        // thread criada
        pthread_create(&thread_handles[i], NULL, mul_padrao, &dados[i]);
    }

    for (int i = 0; i < thread_count; i++) {
        pthread_join(thread_handles[i], NULL);
    }

    //print_matriz(C,N);


}