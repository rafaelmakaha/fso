#include<stdio.h>
#include<pthread.h>
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>

int maximo = 5000;
int total_pontos = 0;
int pontos_internos = 0;
pthread_mutex_t lock;

void *verifica(void *params){
    srand(time(NULL));

    for(int i; i < maximo; i++){
        pthread_mutex_lock(&lock);
        total_pontos++;
        pthread_mutex_unlock(&lock);

        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if(((x*x)+(y*y) <= 1)){
            pthread_mutex_lock(&lock);
            pontos_internos++;
            pthread_mutex_unlock(&lock);
        }
    }

    pthread_exit(0);
}

int main(int argc, char *argv[]){
    int TAM = 10;

    pthread_t tid[TAM];

    pthread_mutex_init(&lock,NULL);

    for(int i=0; i < TAM; i++){
        int flag = pthread_create(&tid[i], NULL, verifica, &maximo);
        if (flag != 0){
            printf("Erro ao criar thread\n");
            exit(EXIT_FAILURE);
        }
    }

    for(int i=0; i < TAM; i++){
        int status = pthread_join(tid[i], NULL);
        if(status != 0){
            printf("Erro ao encerrar thread\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Pontos totais: %d\n", total_pontos);
    printf("Pontos internos a circunferência: %d\n", pontos_internos);
    double pi = 4 * (double)pontos_internos/(double)total_pontos;
    printf("Pi: %lf\n", pi);


    return 0;
}