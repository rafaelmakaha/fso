#include<stdio.h>
#include<pthread.h>
#include <sys/types.h> 
#include <unistd.h> 
#include<stdlib.h>

int valor = 0;

void *runner(void *param){
    valor++;
    pthread_exit(0);
}

int main(int argc ,char *argv[]){
    pid_t pid;
    pthread_t tid;
    pthread_attr_t attr;

    pid = fork();
    printf("%d\n", pid);
    if(pid == 0){
        pthread_attr_init(&attr);
        pthread_create(&tid, &attr, runner, NULL);
        pthread_join(tid, NULL);
        printf("Filho terminou, caralho\n");
        printf("valor do filho: %d\n", valor);
    }else if(pid > 0){
        wait(NULL);
        printf("Valor do pai: %d\n", valor);
    }

    return 0;
}