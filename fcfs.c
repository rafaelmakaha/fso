#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define NUM_DISCOS 5000
#define TOTAL_SOLICITACOES 1000

int main(int argc, char *argv[]){
    int cilindros[TOTAL_SOLICITACOES];

    srand(time(NULL));
    for(int i = 0; i < TOTAL_SOLICITACOES; i ++){
        cilindros[i] = rand() % NUM_DISCOS;
    }

    int posicao = atoi(argv[1]);
    int montante = 0;

    printf("%d\n", posicao);

    montante += abs(posicao - cilindros[0]);
    for(int i=1; i < TOTAL_SOLICITACOES; i++){
        montante += abs(cilindros[i] - cilindros[i-1]);
    }

    printf("\nMontante: %d\n", montante);
    return 0;
}