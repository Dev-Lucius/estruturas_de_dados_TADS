/*
Escreva um programa em C que utilize o operador sizeof para imprimir o
tamanho em bytes dos seguintes tipos: char, short int, int, long int, float,
double e long double. Imprima também o endereço de cada variável utilizada
*/

#include <stdio.h>
#include <stdlib.h>

int main(){
    char exemplochar = 'A';
    short int exemploShortInt = 'B';
    int exemploInt = 100;
    long int exemploLongInt = 1000;
    float exemploFloat = 20.00;
    double exemploDouble = 25.12345;
    long double exemploLongDouble = 99.987654321;

    printf("O Caractere %c Ocupa na Memória %ld Bytes \n", exemplochar, sizeof(exemplochar));
    printf("O Short Int %d Ocupa na Memória %ld Bytes \n", exemploShortInt, sizeof(exemploShortInt));
    printf("O Int %d Ocupa na Memória %ld Bytes \n", exemploInt, sizeof(exemploInt));
    printf("O Long Int %ld Ocupa na Memória %ld Bytes \n", exemploLongInt, sizeof(exemploLongInt));
    printf("O Float %f Ocupa na Memória %ld Bytes \n", exemploFloat, sizeof(exemploFloat));
    printf("O Double %f Ocupa na Memória %ld Bytes \n", exemploDouble, sizeof(exemploDouble));
    printf("O Long Double %Lf Ocupa na Memória %ld Bytes \n", exemploLongDouble, sizeof(exemploLongDouble));
}