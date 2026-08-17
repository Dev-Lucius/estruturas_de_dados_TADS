/*
(Baseado no Exercício 6 da aula) Escreva a função void menorVetor(int *vt, int n,
int *menor) que identifique o menor valor dentro do vetor vt e o deposite na
variável passada por referência menor.
*/

/*
    Cheet
    vt       → endereço do primeiro elemento
    vt + 1   → endereço do segundo elemento
    *vt      → valor do primeiro elemento
    *(vt+1)  → valor do segundo elemento
*/
#include <stdio.h>
#include <stdlib.h>

void menorVetor(int *vt, int n, int *menor){
    *menor = *vt;
    for(int i = 0; i < n; i++){
        if(*(vt + i) < *menor){
            *menor = *(vt + i); 
        }
    }
}

int main(){

    int num;
    int *pont;
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

    menorVetor(pont, num, &menorValor);
    printf("Menor Valor do Ponteiro = %d \n", menorValor);

    free(pont);
    return 0;
}
