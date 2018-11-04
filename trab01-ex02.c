#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include <unistd.h>

int valor_aluno;
int dorme = 1;

int TAM;
sem_t sem1; 
sem_t sem2;

// variáveis da fila
int *fila;
int inicio = 0;
int fim = 0;
int capacidade;
int qnt = 0;

// responsável por gerar a quantidade de alunos
int alunos(){
    int alunos = 2 + rand() % 50;
    return alunos;
}

// retorna o próximo da fila
int fila_proximo(){
    return fila[inicio];
}

int fila_vazia(){
    return(qnt == 0);
}

int fila_cheia(){
    if(qnt == capacidade)
        return 1;
    else
        return 0;
}

void fila_insere(int valor) {
    if(fim++ == capacidade){
        fim = 0;
        fila[fim] = valor;
    }else{
        fila[fim++] = valor;
        qnt++;
    }
}

void fila_remove(){
    if(inicio++ == capacidade){
        inicio = 0;
        qnt--;
    }else{
        inicio++;
        qnt--;
    }
}

// ações do monitor
void *runner(void *param){
    sleep(3);
    sem_wait(&sem2);
    while(!fila_vazia()){
        sem_wait(&sem1);
        sleep(1);
        sem_post(&sem1);
    }
    sem_post(&sem2);
    pthread_exit(0);
}

// ações dos alunos
void *runner2(void *id) {
    int cont = 0;
    int valor = valor_aluno;
    
    while(cont != 3){
        sleep(1); // tempo de aluno estudando
        if(!fila_cheia()){ //se a fila não estiver cheia, entra na fila. se estiver, volta a estudar
            fila_insere(valor);
            printf("O aluno %d entrou na fila\n", valor);
            while(fila_proximo() != valor) { // lopp esperando sua vez na fila
                sem_wait(&sem1);

                printf("to dentro\n");
            }
            printf("O aluno %d está sendo atendido\n", fila_proximo());
            // caso seja o próximo da fila, é atendido
            sem_wait(&sem1);
            sem_post(&sem1);
            fila_remove();
            cont++;
        }
    }
    
    pthread_exit(0);
}


int main(int argc, char *argv[]){
    int i;
    pthread_t monitor;
    pthread_t *aluno;

    //TAM = alunos();
    TAM = 4;

    // Cria a lista de alunos
    aluno = malloc(sizeof(pthread_t) * TAM);

    // Cria a fila de alunos
    capacidade = TAM/2;
    fila = malloc(sizeof(int) * capacidade);

    // Inicia os semáforos
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);

    // Inicia os alunos
    for(i = 0; i < TAM; i++){
        valor_aluno = i;
        pthread_create(&aluno[i], NULL, runner2, NULL);
    }

    // Inicia o Monitor
    pthread_create(&monitor, NULL, runner, NULL);

    for(i = 0; i < TAM; i++){
        pthread_join(aluno[i], NULL);
    }
    pthread_join(monitor, NULL);
    
    free(fila);
    free(aluno);
    return 0;
}