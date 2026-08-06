#include <stdio.h>
#include <stdlib.h>

int main(){

    /*
    Com base no exercício anterior (3), copie o endereço armazenado no ponteiro *ps, para o ponteiro *qs;
    */

    double a, b, s;
    a = 56.76, b = 67.89, s = a + b;

    // Nova Variável C
    double c;

    double *ps = (double*)malloc(sizeof(double));

    if(ps == NULL){
        printf("Erro ao Alocar Memória. \n");
        return 1;
    }

    *ps = s;
    c = *ps;

    // Novo Ponteiro
    double *qs = (double*)malloc(sizeof(double));
    *qs = *ps;

    // 1. Some 100 ao valor referenciado no ponteiro *qs;
    *qs = *qs + 100;
    printf("\nPonteiro *qs Somado com 100 = %.2f", *qs);

    // 2. Mostre os valores referenciados por *ps e *qs;
    printf("\nValor Referenciado de *ps = %.2f", *ps); 
    printf("\nValor Referenciado de *qs = %.2f", *qs); 

    // 3. Copie o valor do ponteiro *qs para a variável A;
    printf("\nVariável A Antes da Troca = %.2f", a);
    a = *qs;
    printf("\nVariável A Depois da Troca = %.2f", a);

    // 4. Atribua o endereço da variável B, ao ponteiro *qs;
    printf("\nEndereço da Variável B Antes da Troca = %p", &b);
    qs = &b;
    printf("\nEndereço da Variável B Depois da Troca = %p \n", &b);


    // 5. Use o ponteiro *qs, para subtrair 10 do valor da variável B;
    printf("\nVariável B Antes da Subtração = %.2f", b);
    *qs = *qs - 10;
    printf("\nVariável B Antes da Subtração = %.2f", b);

    // 6. Mostre os valores de A, B e *qs
    printf("\nVariável A = %.2f", a);
    printf("\nVariável B = %.2f", b);
    printf("\nPonteiro *qs = %.2f \n", *qs);

    return 0;
}