#include <stdio.h>
#include <stdlib.h>

void somaAB(int a, int b, int*pab){
    *pab = a + b;
}

int main(){

    int valorA, valorB;
    int *soma = (int*)malloc(sizeof(int));
    
    valorA = 10, valorB = 20;
    somaAB(valorA, valorB, soma);
    
    printf("\nSoma = %d \n", *soma);

    return 0;
}