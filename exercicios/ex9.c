/*
(Baseado no Exercício 4 da aula) A partir do exercício anterior, crie um segundo
ponteiro *qs e faça-o receber o mesmo endereço de *ps.
    • Somar 100 ao valor referenciado por *qs e exibir *ps e *qs;
    • Apontar qs para a variável B e subtrair 10 do seu valor usando *qs;
    • Exibir os valores finais
*/

#include <stdio.h>
#include <stdlib.h>

int main(){

    double a;
    double b;
    double soma;

    printf("Insira um Valor para a Variável A:  \n");
    scanf("%lf", &a);

    printf("Insira um Valor para a Variável B: \n");
    scanf("%lf", &b);

    soma = a + b;

    double *ps;
    ps = (double*) malloc(sizeof(double));
    *ps = soma;

    printf("Soma Total = %f \n", *ps);

    double c;
    c = *ps;
    
    printf("Soma Total (Referenciada em C): %f \n", c);

    // Criando o Segundo Ponteiro
    double *qs;
    qs = (double*) malloc(sizeof(double));
    qs = ps;

    // Somar 100 ao valor referenciado por *qs e exibir *ps e *qs;
    *qs = *qs + 100;
    printf("Ponteiro PS = %f \n", *ps);
    printf("Ponteiro QS = %f \n", *qs);

    // Apontar qs para a variável B e subtrair 10 do seu valor usando *qs
    qs = &b;
    *qs = *qs - 10;
    printf("Novo Ponteiro QS = %f \n", *qs);

    // Exibir Valores Finais
    printf("Variável A = %f \n", a);
    printf("Variável B = %f \n", b);
    printf("Variável C = %f \n", c);
    printf("Ponteiro PS = %f \n", *ps);
    printf("Ponteiro QS = %f \n", *qs);

    free(ps);
    return 0;
}
