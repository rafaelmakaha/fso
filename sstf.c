#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_CILINDROS 5000
#define CHAMADAS 1000

int main(int argc, char *argv[]){

  int fila[CHAMADAS];
  srand(time(NULL));
  int new;

  for(int i=0;i<CHAMADAS;i++){
    fila[i]= rand() % NUM_CILINDROS;
  }

  int montante = 0;
  int inicial = atoi(argv[1]);

  for(int j=0;j<CHAMADAS;j++){
    int menor = 5001;
    for(int i=0;i<CHAMADAS;i++){
      if(abs(fila[i]-inicial)<menor){
        menor = abs(fila[i]-inicial);
        new=i;
      }
    }
    montante += menor;
    inicial = new;
  }

  printf("%d cilindros\n",montante);

  return 0;
}
