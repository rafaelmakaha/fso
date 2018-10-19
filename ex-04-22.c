#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct Ponto{
    float x;
    float y;
}ponto;

int main(){
    int total = 10000;
    ponto list[total];
    int i=0;
    int list_len = (sizeof(list)/sizeof(list[0]));
    float rand_max = 1.00;
    float qnt_dentro = 0;
    float pi = 0;
    double distancia = 0;
    
    for(i = 0; i < list_len; i++ ){
        printf("%d\n", i);

        // Cria os pontos aleatórios
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

        // Verifica se o ponto criado está na circunferência
        distancia = list[i].x * list[i].x;
        printf("%lf\n",distancia);
        distancia += list[i].y * list[i].y;
        printf("%lf\n",distancia);
        if (sqrt(distancia) <= 1){
            qnt_dentro ++;
        }
    }

    pi = 4.0 * (qnt_dentro / (float) total);
    printf("Pi é aproximadamente: %f\n", pi);

    return 0;
}