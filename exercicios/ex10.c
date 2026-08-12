/*
Solicite ao usuário o tamanho de um vetor de inteiros $N$. Aloque
dinamicamente memória para $N$ inteiros usando malloc, preencha-o com
números informados pelo usuário, exiba-os e libere a memória
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int num;
    int n;

    printf("Insira o Tamanho n de um Array \n");
    scanf("%d", &n);

    int *vet;
    vet = (int *) malloc(n * sizeof(int)); 

    for(int i = 0; i < n; i++){
        printf("Insira um Valor ao Vetor[%d]: \n", i);
        scanf("%d", &num);
        vet[i] = num;
    }

    // Imprimindo o Vetor
    for(int i = 0; i < n; i++){
        printf("Vetor[%d] = %d \n", i, vet[i]);
    }

    return 0;
}
