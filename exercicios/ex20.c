/*
(Baseado no Exercício 9 da aula) Crie a função int* menorVetorPonteiro(int *vt,
int n) que retorne diretamente o endereço do menor elemento do vetor.
*/

#include <stdio.h>
#include <stdlib.h>

int* menorVetorPonteiro(int *vt, int n){
    int *endMenor = vt;

    for(int i = 0; i < n; i++){
        if(*(vt + i) < *endMenor){
            endMenor = vt + i;
        }
    }

    return endMenor;
}

int main(){

    int *p;
    int num;
    int *menorEndereco;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    p = (int*) malloc(num *sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i+1);
        // &pont[i] == pont + 1
        scanf("%d", (p + i));
    }

    menorEndereco = menorVetorPonteiro(p, num);

    printf("Valor do Menor Valor do Ponteiro = %d \n", *menorEndereco);
    printf("Endereço do Menor Valor do Ponteiro = %p \n", (void*)menorEndereco);

    free(p);
    return 0;
}
