/*
Declare uma variável inteira a = 15 e um ponteiro int *pa. Faça pa apontar para
a. Altere o valor de a para 50 utilizando apenas o ponteiro pa e exiba o novo
valor de a.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    int a;
    int *pa;

    a = 15;
    printf("Antigo Valor de A = %d \n", a);

    // Apontando o Ponteiro para a Variável A
    // e, em seguida, alterando o valor
    pa = &a;
    pa = 50;
    printf("Novo de Valor A = %d \n", pa);

    return 0;
}
