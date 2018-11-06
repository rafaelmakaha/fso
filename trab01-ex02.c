#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>
#include <unistd.h>

int *valor_aluno;

int acabou = 0;

int TAM;
sem_t sem1; 
sem_t sem2;

// variáveis da fila
// int *fila;
// int inicio = 0;
// int fim = 0;
int capacidade;
// int qnt = 0;
typedef struct Fila{
    int valor;
    struct Fila* prox;
}Queue;

typedef struct Cab{
    int quant;
    struct Fila* init;
    struct Fila* inicio;
    struct Fila* fim;
}Indexes;

Indexes *cab;


// responsável por gerar a quantidade de alunos
int alunos(){
    int alunos = 2 + rand() % 50;
    return alunos;
}

// retorna o próximo da fila
int fila_proximo(){
    return cab->inicio->valor;
}

int fila_vazia(){
    return(cab->quant==0);
}

int fila_cheia(){
    return (cab->quant == capacidade);
}

void fila_insere(int valor) {
    Queue *novo = (Queue *)malloc(sizeof(Queue));
    novo->valor = valor;
    novo->prox = NULL;

    if(fila_cheia()){
        return ;
    }
    if(fila_vazia()){
        cab->inicio = novo;
        cab->fim = novo;
        cab->quant++;
    }else{
      cab->fim->prox = novo;
      cab->fim = novo;
      cab->quant ++;
    }
}

void fila_remove(){
    Queue *p;

    if(fila_vazia()){
        return ;
    }
    p = cab->inicio;
    cab->inicio = cab->inicio->prox;
    free(p);
    cab->quant--;
}

void fila_print(){
    Queue *p = cab->inicio;
    while(p->prox!=cab->fim){
        printf("%d",p->valor);
        if(p->prox==NULL){
            p->prox=cab->init;
        }
        p = p->prox;
    }
}

// ações do monitor
void *runner(void *param){
    while(!acabou){
        sleep(3);
        while(!fila_vazia()){
            sem_wait(&sem2);
            sem_wait(&sem1);
            sleep(2);
            sem_post(&sem1);
        }
        sem_post(&sem2);
        pthread_exit(0);
    }
}

// ações dos alunos
void *runner2(void *id) {
    int cont = 0;
    int *valor = id;
    while(cont < 3){
        sleep(1); // tempo de aluno estudando
        if(!fila_cheia()){ //se a fila não estiver cheia, entra na fila. se estiver, volta a estudar
            fila_insere(*valor);
            printf("O aluno %d entrou na fila\n", *valor);
            // fila_print();
            printf("Eu sou %d. Fila próximo = %d \n", *valor, fila_proximo());
            while(fila_proximo() != *valor) { // lopp esperando sua vez na fila
                sem_wait(&sem2);
                sem_post(&sem2);
            }
            printf("O aluno %d está sendo atendido\n", fila_proximo());
            // caso seja o próximo da fila, é atendido
            sem_wait(&sem1);
            sem_post(&sem1);
            printf("O aluno %d saiu da fila\n", fila_proximo());
            fila_remove();
            cont++;
        }else{
            printf("O aluno %d voltou a estudar, pois a fila estava cheia\n", *valor);
        }
        printf("O aluno %d voltou a estudar\n", *valor);      
        printf("\n");
    }
    printf("O aluno %d terminou os estudos\n", *valor);
    
    pthread_exit(0);
}


int main(int argc, char *argv[]){
    int i;
    int *a;
    pthread_t monitor;
    pthread_t *aluno;

    //TAM = alunos();
    TAM = 6;

    // Inicia Fila e Cab
    cab = malloc(sizeof(Indexes));
    cab->inicio = NULL;
    cab->fim = NULL;
    cab->quant = 0;

    // Cria a lista de alunos
    aluno = malloc(sizeof(pthread_t) * TAM);

    // Cria a fila de alunos
    capacidade = TAM/2;

    // Cria vetor resopnsável por armazenar as ID's dos alunos
    valor_aluno = malloc(sizeof(int) * TAM); 

    // Inicia os semáforos
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 1);

    // Inicia os alunos
    for(i = 0; i < TAM; i++){
        valor_aluno[i] = i; // vetor para armazenar todos os valores de i
        a = malloc(sizeof * a);  // ponteiro responsável pelos parâmetros para as threads
        a = &valor_aluno[i];  // valor do parâmetro para a thread
        pthread_create(&aluno[i], NULL, runner2, a);
    }

    // Inicia o Monitor
    pthread_create(&monitor, NULL, runner, NULL);

    for(i = 0; i < TAM; i++){
        pthread_join(aluno[i], NULL);
    }
    acabou = 1;
    pthread_join(monitor, NULL);
    
    free(cab);
    free(aluno);
    return 0;
}