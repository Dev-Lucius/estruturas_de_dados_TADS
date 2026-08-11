/*
(Baseado no Exercício 2 da aula) Leia duas variáveis inteiras A e B (idades).
Aloque memória dinamicamente para um inteiro apontado por *ps. Armazene
a soma A + B nesse espaço. Imprima:
    • O resultado da soma;
    • O endereço armazenado em ps e o endereço do próprio ponteiro &ps;
    • Os endereços das variáveis A e B
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int a;
    int b;
    int soma; 

    printf("Insira um Valor para a Variável A:  \n");
    scanf("%d", &a);

    printf("Insira um Valor para a Variável B: \n");
    scanf("%d", &b);

    soma = a + b;
    int *ps;
    ps = (int*) malloc(sizeof(int));
    ps = &soma;

    printf("Soma Total = %d \n", *ps);
    printf("Endereço de Memória A = %p \n", &a);
    printf("Endereço de Memória B = %p \n", &b);
    printf("Endereço de Memória PS = %p \n", &ps);

    return 0;
}
