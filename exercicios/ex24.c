/*
(Baseado no Exercício 16 da aula) Escreva uma função int contaConsoantes(char
*str) que retorne a quantidade de consoantes presentes na string utilizando
navegação por ponteiro
*/

#include <stdio.h>
#include <stdlib.h>

int contaConsoantes(char *str){
    int contador = 0;
    
    // Enquanto um Caracter da String não For nulo ...
    while(*str != '\0'){
        if(
            *str != 'a' && *str != 'e' && *str != 'i' && *str != 'o' && *str != 'u' &&
            *str != 'A' && *str != 'E' && *str != 'I' && *str != 'O' && *str != 'U'
         ){
            contador++;
        }
        str++;
    }
    return contador;
}

int main(){
    
    char *exemplo = "Gato";

    int qtdConsoantes = contaConsoantes(exemplo);

    printf("Quantidade de Vogais = %d \n", qtdConsoantes);

    return 0;
}
