/*
(Baseado no Exercício 7 da aula) Escreva a função void maiorVetor(int *vt, int n,
int *maior) que encontre o maior elemento do vetor e armazene na variável
apontada por maior
*/

#include <stdio.h>
#include <stdlib.h>

void maiorVetor(int *vt, int n, int *maior){
    *maior = *vt;
    for(int i = 0; i < n; i++){
        if(*(vt + i) > *maior){
            *maior = *(vt + i); 
        }
    }
}

int main(){

    int num;
    int *pont;
    int maiorValor;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    pont = (int*) malloc(num * sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i+1);
        // &pont[i] == pont + 1
        scanf("%d", (pont + i));
    }

    maiorVetor(pont, num, &maiorValor);
    printf("Maior Valor do Ponteiro = %d \n", maiorValor);

    free(pont);
    return 0;
}
