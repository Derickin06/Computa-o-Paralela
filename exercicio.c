#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

int main() {
    int pid;
    int piperfds1[2], piperfds2[2],piperfds3[2];
    int returnstatus1, returnstatus2,returnstatus3;
    char palavra[20];
    char readpalavra[20];
    char palavranova[20];

    printf("Digite a palavra: ");
    scanf("%19s", palavra);

    printf("\n palavra digitada: %s \n", palavra );
    //processo pai escreve no pipe 01 e filho lê

    //pai escrevendo no pipe 01
    write(piperfds1[1], palavra, sizeof(palavra));
    //read(piperfds1[0], readpalavra, sizeof(readpalavra));

    pid = fork();

    if (pid == 0){
        read(piperfds1[0], readpalavra, sizeof(readpalavra));
        
        int n = strlen(readpalavra);
        for (int i=0;i<n;i++){
            palavranova[i] = readpalavra[n-1-i];
            
        }
        write(piperfds2[1], palavranova, sizeof(palavranova));
       // printf("Palavra invertida: %s \n", palavranova);
        return 1;
    }
    else{
        read(piperfds2[0], palavranova, sizeof(palavranova));
        printf("Palavra invertida: %s ", palavranova);

        if( strcmp(palavranova, readpalavra)){
            printf(" \n A palavra é palíndrome. \n");
        }
        else{
            printf("\n A palavra não é palíndrome.\n");
        }
        

    }





    return 1;

}