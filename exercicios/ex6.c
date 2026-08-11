/*
Crie um ponteiro para inteiro iniciado com NULL. Aloque memória
dinamicamente usando malloc para armazenar um valor inteiro. Verifique se a
alocação foi bem-sucedida, atribua um valor lido pelo usuário, imprima-o e
libere a memória com free.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    
    int *p;
    p = NULL;

    p = (int*) malloc(sizeof(int)); 

    printf("Insira um Valor para o Ponteiro P: \n");
    scanf("%d", &*p);

    printf("Novo Valor de P = %d \n", *p);

    return 0;   
}
