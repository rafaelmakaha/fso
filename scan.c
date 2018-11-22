#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_CILINDROS 5000
#define CHAMADAS 1000

int main(int argc, char *argv[]){

  int fila[CHAMADAS];
  int proximo=0;

  srand(time(NULL));

  for(int i=0;i<CHAMADAS;i++){
    fila[i]= rand() % NUM_CILINDROS;
  }

  int montante = 0;
  int inicial = atoi(argv[1]);
  
  // Faz o sort na fila
  for(int i=0; i < CHAMADAS; i++){
      for(int j=i; j< CHAMADAS; j++){
          if(fila[i] > fila[j]){
              int temp = fila[i];
              fila[i] = fila[j];
              fila[j] = temp;
          }
      }
  }

  // Enonctra posição do primeiro a ser encontrado pela agulha
  for(int i=0; i < CHAMADAS; i++){
      if(fila[i] > inicial){
          proximo = i - 1;
      }
  }

  // Agulha vai até o inicio dos valores
  int atual = inicial;
  for(int i = proximo; i != 0; i--){
      montante += abs(fila[i] - atual);
      atual = fila[i];
  }
  montante += abs(atual - 0);

  // Agulha vai até o valor mais alto
  montante += abs(0 - fila[proximo+1]);
  for(int i = proximo + 1; i < CHAMADAS + 1; i++){
      montante += abs(fila[i] - fila[i+1]);
  }


  printf("%d cilindros\n",montante);

  return 0;
}
