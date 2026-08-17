/*
Crie uma função void operacoes(int a, int b, int *soma, int *diff, int *prod) que
receba dois inteiros e retorne, por referência, a soma, a diferença e o produto
entre eles.
*/

#include <stdio.h>
#include <stdlib.h>

void operacoes(int a, int b, int *soma, int *diff, int *prod){
    *soma = a + b;
    *diff = a - b;
    *prod = a * b;
}

int main(){

    int num1, num2;
    int *psoma, *pdiff, *pprod;

    psoma = (int*) malloc(sizeof(int));
    pdiff = (int*) malloc(sizeof(int));
    pprod = (int*) malloc(sizeof(int));

    num1 = 10;
    num2 = 2;

    operacoes(num1, num2, psoma, pdiff, pprod);

    printf("Soma = %d \n", *psoma);
    printf("Diferença = %d \n", *pdiff);
    printf("Produto = %d \n", *pprod);

    return 0;
}
