/*
Escreva uma função void troca(int *a, int *b) que receba dois ponteiros para
inteiros e troque os valores das variáveis originais. Escreva uma função main
para testar
*/

#include <stdio.h>
#include <stdlib.h>

// Criando a Função
void troca(int *a, int *b){
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int main(){

    int x = 100, y = 200;
    
    printf("Variáveis Antes da Troca: \n");
    printf("Variável X = %d \n", x);
    printf("Variável Y = %d \n", y);

    // Fazendo a Troca
    troca(&x, &y);
    printf("Variáveis Depois da Troca: \n");
    printf("Variável X = %d \n", x);
    printf("Variável Y = %d \n", y);

    return 0;
}
