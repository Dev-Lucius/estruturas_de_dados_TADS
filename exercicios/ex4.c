/*
Escreva um programa que declare duas variáveis inteiras e compare seus
endereços na memória. O programa deve exibir qual das duas variáveis está
alocada no maior endereço de memória
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    int b;
    b = 10;

    int a;
    a = 70;
    
    printf("Endereço de Memória A = %p \n", &a);
    printf("Endereço de Memória B = %p \n", &b);

    if(&a > &b){
        printf("Endereço de Memória A é Maior \n");
    }

    if(&b > &a){
        printf("Endereço de Memória B é Maior \n");
    }

    if(&a == &b){
        printf("Ambos os Endereços de Memória são Iguais \n");
    }

    return 0;
}
