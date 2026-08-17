/*
Crie uma função void imprimeVetorPonteiro(int *p, int n) que imprima todos
os elementos de um vetor de inteiros utilizando navegação por ponteiro *(p +
i) em vez do operador de subscrito p[i]
*/

#include <stdio.h>
#include <stdlib.h>

void imprimeVetorPonteiro(int *p, int n){
    for(int i = 0; i < n; i++){
        printf("Ponteiro[%d] = %d \n", i, *(p + i));
    }
}

int main(){

    int *pont;
    int num;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    pont = (int*) malloc(num *sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i);
        // &pont[i] == pont + 1
        scanf("%d", (pont + i));
    }

    // Imprimindo o Ponteiro
    imprimeVetorPonteiro(pont, num);

    free(pont);
    return 0;
}

