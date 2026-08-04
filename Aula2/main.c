#include <stdio.h>

int main(){
    // Exercício 1
    // Variável de Idades
    int a, b, s;
    a = 10, b = 20;
    s = a + b;
    
    
    // Ponteiro
    int *ps;
    ps = &s;

    // Novo Ponteiro
    int *pab;
    pab = &a;

    // Variável Auxiliar (aux)
    int aux;

    // a. Mostre o resultado armazenado em S.
    printf("Soma = %d", s);
    
    // b. Mostre o endereço armazenado pelo ponteiro *ps e o endereço de S;
    printf("\nEndereço Ponteiro = %p", &ps);
    printf("\nEndereço Variável S = %p", &s);

    // c. Mostre o endereço do ponteiro *ps, mostre o conteúdo referenciado por *ps
    printf("\nEndereço Ponteiro = %p | Coteúdo Referenciado = %d", &ps, *ps);
    
    // d. Defina um ponteiro *pab, mostre o endereço e o conteúdo da variável A, usando *pab
    printf("\nEndereço Ponteiro = %p | Contéudo da Variável A usando *pab = %d", &pab, *pab);


    // e. Após, troque o endereço armazenado em *pab, pelo endereço da variável B, mostre o seu conteúdo e endereço armazenado em pab;
    aux = *pab;
    *pab = b;
    b = aux;
    printf("\nEndereço Ponteiro = %p | Contéudo da Variável B (Trocado Com A) usando *pab = %d \n", &pab, *pab);

    // ----

    // Exercício 2
    return 0;
}
