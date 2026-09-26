#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <math.h>


int thread_count;

typedef struct {
    int inicio;
    int fim;
    float *A;
    float *B;
    float *C;
} dados_thread;

void* mul_padrao(void* arg){
    dados_thread* dados = (dados_thread*)arg;

    printf("Thread iniciou: %d - %d \n", 
    dados->inicio, 
    dados->fim);


    for(int i = dados->inicio; i <= dados->fim; i++){
        dados->C[i] = dados->A[i] + dados->B[i];
    }
    


    printf("Thread terminou: %d - %d\n",
       dados->inicio,
       dados->fim);
    return NULL;

} 








int main(int argc, char* argv[]){

    pthread_t* thread_handles;
    int N = strtol(argv[1], NULL, 10); // tamanho do vetor
    thread_count = strtol(argv[2], NULL, 10); //numero de threads
    dados_thread dados[thread_count];
    thread_handles = malloc(thread_count*sizeof(pthread_t));








}