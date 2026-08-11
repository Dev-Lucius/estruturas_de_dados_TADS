/*
Crie um programa que leia dois inteiros, num1 e num2. Declare ponteiros para
ambos e, através dos ponteiros, calcule e exiba a soma, a diferença e o produto
entre eles.
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
   
   // Variáveis
   int num1, num2;
   num1 = 10;
   num2 = 2;

    // Operarações
    int soma;
    int diferenca;
    int produto;

   // Ponteiros
   int *pnum1 = (int*) malloc(sizeof(int));
   int *pnum2 = (int*) malloc(sizeof(int));

   pnum1 = &num1; 
   pnum2 = &num2;

   soma = *pnum1 + *pnum2;
   diferenca = *pnum1 - *pnum2;
   produto = *pnum1 * *pnum2;

   printf("Soma = %d \n", soma);
   printf("Subtração = %d \n", diferenca);
   printf("Produto = %d \n", produto);

  return 0;
}
