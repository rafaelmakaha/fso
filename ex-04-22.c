#include<stdio.h>

typedef struct Ponto{
    int x;
    int y;
}ponto;

int main(){
    ponto  list[20];
    int i=0;

    
    for(i = 0; i < (sizeof(list)/sizeof(list[0])); i++ ){
        printf("%d\n", i);
    }
    


    return 0;
}