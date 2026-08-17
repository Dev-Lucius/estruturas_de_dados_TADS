/*
(Baseado no Exercício 8 da aula) Escreva a função void menorMaiorVetor(int *vt,
int n, int *menor, int *maior) que utilize internamente as funções criadas nos
exercícios 17 e 18 para obter o menor e maior elemento do vetor
simultaneamente.
*/

#include <stdio.h>
#include <stdlib.h>

void menorMaiorVetor(int *vt, int n, int *maior, int *menor){
    *maior = *vt;
    *menor = *vt;

    // Achando o Maior
    for(int i = 0; i < n; i++){
        if(*(vt + i) > *maior){
            *maior = *(vt + i); 
        }
    }

    // Achando o Menor
    for(int i = 0; i < n; i++){
        if(*(vt + i) < *menor){
            *menor = *(vt + i); 
        }
    }
}

int main(){

    int num;
    int *pont;
    int maiorValor;
    int menorValor;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    pont = (int*) malloc(num * sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i+1);
        // &pont[i] == pont + 1
        scanf("%d", (pont + i));
    }

    menorMaiorVetor(pont, num, &maiorValor, &menorValor);

    printf("Maior Valor do Ponteiro = %d \n", maiorValor);
    printf("Menor Valor do Ponteiro = %d \n", menorValor);

    free(pont);
    return 0;
}
