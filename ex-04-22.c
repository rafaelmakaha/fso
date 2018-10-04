#include<stdio.h>

typedef struct Ponto{
    int x;
    int y;
}ponto;

int length(ponto *list){
    return (sizeof(list)/sizeof(list[0]));
}

int main(){
    ponto  list[20];
    int i=0;

    
    for(i = 0; i < length(list); i++ ){
        printf("%d\n", i);
    }
    


    return 0;
}