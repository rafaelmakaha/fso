#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

int TAM;

int alunos(){
    int alunos = 2 + rand() % 50;
    return alunos;
}

void *runner(void *param){

    pthread_exit(0);
}


int main(int argc, char *argv[]){
    pthread_t monitor;
    pthread_t *aluno;

    TAM = alunos();

    aluno = malloc(sizeof(pthread_t) * TAM);

    free(aluno);
    return 0;
}