/*
Declare três variáveis (int x, float y, char z). Atribua valores a elas e imprima
seus valores e seus respectivos endereços de memória em hexadecimal
utilizando o especificador %p (ou %X) e o operador &.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int x;
    float y;
    char z;

    x = 10;
    y = 75.29;
    z = 'L';

    // Imprimindo Os valores
    printf("Imprimindo os Valores \n");
    printf("Variável X = %d \n", x);
    printf("Variável Y = %f \n", y);
    printf("Variável Z = %c \n", z);

    // Imprimindo os Endereços de Memória (em Hexadecimal)
    printf("Imprimindo os Endereços de Memória (Hexadecimal) \n");
    printf("Endereço de X = %p \n", &x);
    printf("Endereço de Y = %p \n", &y);
    printf("Endereço de Z = %p \n", &z);
}
