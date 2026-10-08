#include <stdio.h>
#include <stdlib.h>

void imprimeVetor(int vt[], int n){
    for (int i = 0; i < n; i++){
        printf("v[%d] = %d \n", i, vt[i]);
    }
}

// O menor valor de um vetor
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

    for (int i = 1; i < n; i++){
        if (*(vt + i) > *pMaior){
            pMaior = vt + i;
        }
    }
    return pMaior;
}

// Valores repetidos (cada valor repetido aparece uma vez no resultado)
// Retorna um vetor alocado com malloc (quem chamar deve dar free)
// *qtd recebe a quantidade de valores repetidos encontrados
int* VetorRepetidos(int *vt, int n, int *qtd){
    *qtd = 0;

    if (n <= 0){
        return NULL;
    }

    int *repetidos = malloc(n * sizeof(int));
    if (repetidos == NULL){
        return NULL;
    }

    for (int i = 0; i < n; i++){
        // Se o valor já apareceu antes, ele já foi tratado
        int jaVisto = 0;
        for (int j = 0; j < i; j++){
            if (*(vt + j) == *(vt + i)){
                jaVisto = 1;
                break;
            }
        }
        if (jaVisto) continue;

        // Procura outra ocorrência do valor mais adiante
        for (int j = i + 1; j < n; j++){
            if (*(vt + j) == *(vt + i)){
                *(repetidos + *qtd) = *(vt + i);
                (*qtd)++;
                break;
            }
        }
    }

    if (*qtd == 0){
        free(repetidos);
        return NULL;
    }

    return repetidos;
}

int main(){

    int v[10] = {1, 1, 2, 2, 5, 6, 7, 8, 9, 10};
    int n = 10;
    int qtdRepetidos = 0;

    int *pMaiorValor = maiorVetorPonteiro(v, n);
    int *pMenorValor = menorVetorPonteiro(v, n);
    int *pRepetidos  = VetorRepetidos(v, n, &qtdRepetidos);

    if (pMaiorValor != NULL){
        printf("Maior elemento = %d\n", *pMaiorValor);
        printf("Endereco do Maior = %p\n", (void*)pMaiorValor);
    }

    printf("\n");

    if (pMenorValor != NULL){
        printf("Menor elemento = %d\n", *pMenorValor);
        printf("Endereco do Menor = %p\n", (void*)pMenorValor);
    }

    printf("\n");

    if (pRepetidos != NULL){
        printf("Valores repetidos (%d):\n", qtdRepetidos);
        imprimeVetor(pRepetidos, qtdRepetidos);
        free(pRepetidos);
    } else {
        printf("Nao ha valores repetidos.\n");
    }

    return 0;
}
