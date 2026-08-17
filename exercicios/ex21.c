/*
(Baseado no Exercício 10 da aula) Crie a função int* maiorVetorPonteiro(int *vt,
int n) que retorne o endereço do maior elemento do veto
*/

#include <stdio.h>
#include <stdlib.h>

int* maiorVetorPonteiro(int *vt, int n){
    int *endMaior = vt;

    for(int i = 0; i < n; i++){
        if(*(vt + i) > *endMaior){
            endMaior = vt + i;
        }
    }

    return endMaior;
}

int main(){

    int *p;
    int num;
    int *maiorEndereco;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    p = (int*) malloc(num *sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i+1);
        // &pont[i] == pont + 1
        scanf("%d", (p + i));
    }

    // Agora maiorEndereco é realmente um ponteiro.
    maiorEndereco = maiorVetorPonteiro(p, num);

    printf("Valor do Menor Valor do Ponteiro = %d \n", *maiorEndereco);
    printf("Endereço do Menor Valor do Ponteiro = %p \n", (void*)maiorEndereco);

    free(p);
    return 0;
}
