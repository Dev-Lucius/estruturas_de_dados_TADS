/*
(Baseado no Exercício 12 da aula) Escreva a função void converte(int mnts, int
*h, int *m). A função deve atribuir aos endereços de h e m as horas (mnts / 60)
e minutos restantes (mnts % 60). Teste na main
*/

// Resumo
/*
    | Expressão  | Significado                     |
    | ---------- | ------------------------------- |
    | `int *p`   | declara ponteiro                |
    | `p`        | endereço armazenado no ponteiro |
    | `*p`       | valor naquele endereço          |
    | `&x`       | endereço de `x`                 |
    | `p + 1`    | próximo elemento                |
    | `*(p + 1)` | valor do próximo elemento       |
    | `p[i]`     | valor na posição `i`            |
    | `*(p + i)` | equivalente a `p[i]`            |
*/

#include<stdio.h>
#include<stdlib.h>

void converte(int mnts, int *h, int *m){
    *h = mnts / 60;  
    *m = mnts % 60;
}

int main (){

    int minutos;
    int *horas = (int*) malloc(sizeof(int));
    int *minutosRestantes = (int*) malloc(sizeof(int));

    minutos = 123;

    converte(minutos, horas, minutosRestantes);

    printf("Minutos = %d \n", minutos);
    printf("Horas = %d \n", *horas);
    printf("Minutos Restantes = %d \n", *minutosRestantes);

    return 0;
}

