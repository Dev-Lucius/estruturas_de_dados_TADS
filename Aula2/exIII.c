#include <stdio.h>
#include <stdlib.h>

int main(){

    // Exercícios III
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

    // a. Mostre o resultado de A + B, armazenado espaço referenciado por *ps;
    printf("\nSoma das Variáveis Referenciada por *ps = %.2f", *ps);

    // b. Mostre o endereço armazenado no ponteiro *Ps, e o valor referenciado;
    printf("\nEndereço Armazenado no Ponteiro = %p", (void*) ps);


    // c. Crie uma variável double C, e copie o valor referenciado no ponteiro *Ps para a variável C. 
    //    Mostre o valor de C;
    printf("\nValor da referenciado de *Ps para C = %.2f\n", c);

    free(ps);
    return 0;
}
