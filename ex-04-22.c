#include<stdio.h>
#include<stdlib.h>

typedef struct Ponto{
    float x;
    float y;
}ponto;

int main(){
    ponto  list[100];
    int i=0;
    int list_len = (sizeof(list)/sizeof(list[0]));
    int rand_max = 2.00;
    
    for(i = 0; i < list_len; i++ ){
        printf("%d\n", i);
        if(rand()%2 == 0){
            list[i].x = ((float)rand()/(float)(RAND_MAX) * rand_max);
        }else{
            list[i].x = -((float)rand()/(float)(RAND_MAX) * rand_max);            
        }
        if(rand()%2 == 0){
            list[i].y = ((float)rand()/(float)(RAND_MAX) * rand_max);
        }else{
            list[i].y = -((float)rand()/(float)(RAND_MAX) * rand_max);
        }
        printf("X: %f; Y: %f\n", list[i].x, list[i].y);
    }
    


    return 0;
}