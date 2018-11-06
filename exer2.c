#include <stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <semaphore.h>

typedef struct Fila{
    int valor;
    struct Fila* prox;
}Queue;

typedef struct Cab{
    int quant;
    struct Fila* inicio;
    struct Fila* fim;
}Indexes;

Indexes *cab;
int capacidade = 5;

int fila_cheia(){
    return (cab->quant == capacidade);
}

int fila_vazia(){
    return(cab->quant==0);
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

int main(){
  // Inicia Fila e Cab
  cab = malloc(sizeof(Indexes));
  cab->inicio = NULL;
  cab->fim = NULL;
  cab->quant = 0;

  fila_insere(1);
  fila_insere(2);
  fila_insere(3);

  free(cab);
}
