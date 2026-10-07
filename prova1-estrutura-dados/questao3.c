// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

void imprimeVetor(int vt[], int n){
    for (int i=0; i<n; i++){
        printf("v[%d] = %d \n", i, vt[i]);
    }
}

// O menor Valor de um Vetor
int* menorVetorPonteiro(int *vt, int n){
    if (n <= 0) {
        return NULL;
    }

    int *pMenor = vt;

    for (int i = 1; i < n; i++) {
        if (*(vt + i) < *pMenor) {
            pMenor = vt + i;
        }
    }
    return pMenor;
}

// O maior valor de um vetor
int* maiorVetorPonteiro(int *vt, int n){
    if (n <= 0){
        return NULL;
    }

    int *pMaior = vt;

    for(int i = 1; i < n; i++){
        if(*(vt + i) > *pMaior){
            pMaior = vt + i;
        }
    }
    return pMaior;
}

// Repetidos
int* VetorRepetidos(int *vt, int n){
    if(n <= 0){
        return NULL;
    }

    int *repetidos;

    for(int i = 1; i < n; i++){
        if(*vt == *(vt + i)){
            repetidos == vt;
        }
    }
    return repetidos;
}

int main(){

    int v[10] = {1, 1, 2, 2, 5, 6, 7, 8, 9, 10};
    int n = 10;

    int *pMaiorValor = maiorVetorPonteiro(v, n);
    int *pMenorValor = menorVetorPonteiro(v, n);
    int *pRepetidos = VetorRepetidos(v, n);

    if(pMaiorValor != NULL){
        printf("Maior elemento = %d\n", *pMaiorValor);
        printf("Endereco do Maior = %p\n", (int*)pMaiorValor);
    }

    printf("\n");

    if(pMenorValor != NULL){
        printf("Menor elemento = %d\n", *pMenorValor);
        printf("Endereco do Menor = %p\n", (int*)pMenorValor);
    }

    printf("\n");

    if(pRepetidos != NULL){
        printf("Vetor Repetidos = %d\n", *pRepetidos);
    }

    return 0;
}