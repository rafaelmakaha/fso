#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t semaf;

int nAlunos,cCadeiras;
int *count;
int to_naFila = 1;


int set_alunos(){
  int alunos = (rand()%40)+3;
  return alunos;
}

void *runner1(int count[]){
  //função do assistente
  sem_wait(&semaf);



  sem_post(&semaf);
}

void *runner2(void *params){
  int flag=3;

  while(to_naFila == 1){
    // Variavel que o monitor vai usar para chamar proximo aluno
    // verifica propria posição na fila e se o monitor está disponivel
  }

  //função dos alunos
}

void *runner3(void *params){

}


int main(){

  nAlunos = set_alunos();
  cCadeiras =nAlunos/2;

  pthread_t monitor;
  pthread_t *aluno = malloc(sizeof(pthread_t)* nAlunos);

  pthread_create(&monitor,NULL,runner1(&count[n]),NULL);
  pthread_join(monitor,NULL);

  for(int i=0;i<n;i++){
    pthread_create(&aluno[i],NULL,runner2,NULL);
  }
  for(int i=0;i<n;i++){
    pthread_join(aluno[i],NULL);
  }

  free(aluno);
  return 0;
}
