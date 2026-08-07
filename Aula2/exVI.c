#include <stdio.h>
#include <stdlib.h>

void dividaAB(int *pa, int *pb, int *pab){
    if(*pb == 0){
        printf("Impossível Dividir por 0");
        return;
    }
    *pab = *pa / *pb;
}

int main(){
    
    int *valorA = (int*)malloc(sizeof(int));
    int *valorB = (int*)malloc(sizeof(int));
    int *divisor = (int*)malloc(sizeof(int));
    
    *valorA = 50;
    *valorB = 2;
    dividaAB(valorA, valorB, divisor);

    printf("\n Divisão = %d \n", *divisor);

    free(valorA);
    free(valorB);
    free(divisor);

    return 0;
}
