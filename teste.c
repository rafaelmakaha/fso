#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<pthread.h>
#include<string.h>


char s[50];
int TAM = 3;

void *test(void *param){
    printf("Insira uma string: ");
    scanf("%s", s);
    pthread_exit(0);
}

void *test2(void *param){
    printf("Você inseriu a string: %s\n", s);
    pthread_exit(0);
}

void *test3(void *param){
    strcpy(s,"rsrs");
    printf("Eu alterei para: %s\n", s);
    pthread_exit(0);
}

int main(int argc, char *argv[]){
    pthread_t tid[TAM];
    pthread_attr_t attr;

    int i = 1;
    while(i < 4){
        switch(i){
            case 1:
                pthread_create(&tid[i], NULL, test, NULL);
            break;
            case 2:
                pthread_create(&tid[i], NULL, test2,NULL);
            break;
            case 3:
                pthread_create(&tid[i], NULL, test3,NULL);
            break;
            default:
                printf("sei lá, fi\n");
        }
        pthread_join(tid[i], NULL);
        i++;
    }


    return 0;
}