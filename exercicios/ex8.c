/*
(Baseado no Exercício 3 da aula) Leia dois valores double A e B (pesos). Aloque
memória dinamicamente para armazenar a soma A + B apontada por *ps. Em
seguida, declare uma variável double C, copie o valor referenciado por *ps
para C e exiba C. Libere a memória.
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
    ps = &soma;

    printf("Soma Total = %f \n", *ps);

    double c;
    c = *ps;
    
    printf("Soma Total (Referenciada em C): %f \n", c);

    free(ps);
    return 0;
}
