/*
Baseado no Exercício 4 da aula) Crie a função void somaAB(int a, int b, int *pab)
que armazene no ponteiro *pab o resultado da soma de a e b. 
Na main, exiba o valor final da variável associada
*/

#include <stdio.h>
#include <stdlib.h>

void somaBasica(int a, int b, int *pab){
    *pab = a + b;
}

int main(){
    int x, y;
    int *soma = (int*) malloc(sizeof(int));
    
    x = 10;
    y = 20;
    somaBasica(x, y, soma);

    printf("Soma = %d \n", *soma);

    return 0;
}
