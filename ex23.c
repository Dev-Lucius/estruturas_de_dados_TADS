/*
(Baseado no Exercício 15 da aula) Escreva uma função int contaVogais(char *str)
que percorra uma string utilizando ponteiros e retorne a quantidade total de
vogais.
*/

#include <stdio.h>
#include <stdlib.h>

int contaVogais(char *str){
    int contador = 0;
    
    // Enquanto um Caracter da String não For nulo ...
    while(*str != '\0'){
        if(
            *str == 'a' || *str == 'e' || *str == 'i' || *str == 'o' || *str == 'u' ||
            *str == 'A' || *str == 'E' || *str == 'I' || *str == 'O' || *str == 'U'
         ){
            contador++;
        }
        str++;
    }
    return contador;
}

int main(){
    
    char *exemplo = "Exemplo";

    int qtdVogais = contaVogais(exemplo);

    printf("Quantidade de Vogais = %d \n", qtdVogais);

    return 0;
}
