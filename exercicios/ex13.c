/*
(Baseado no Exercício 5 da aula) Crie a função void dividaAB(int *pa, int *pb,
double *pab) que receba o endereço de dois inteiros, realize a divisão entre
eles (convertendo para double) e atribua o resultado ao ponteiro *pab
*/

#include <stdio.h>
#include <stdlib.h>

void divisaoPadrao(int *pa, int *pb, double *pab){
    if(*pb == 0){
        printf("Divisor não Pode ser igual a Zero");
    }

    *pab = (double)(*pa / *pb);
}

int main() {

    int *pan, *pbn;
    double *divisao = (double*) malloc(sizeof(double*));

    *pan = 10;
    *pbn = 2;
    divisaoPadrao(pan, pbn, divisao);

    printf("Divisão = %.2f \n", *divisao);

    return 0
}
