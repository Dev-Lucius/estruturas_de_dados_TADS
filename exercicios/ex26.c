/*
(Baseado no Exercício 14 da aula) Escreva a função void extraiConsoantes(char *str, char *vetorConsoantes) 
que extraia apenas as consoantes da string original para um novo vetor.
*/

#include <stdio.h>
#include <stdlib.h>

int isConsoante(char c){
    return c != 'a' && c != 'e' && c != 'i' &&
           c != 'o' && c != 'u' &&
           c != 'A' && c != 'E' && c != 'I' &&
           c != 'O' && c != 'U';
}

void extraiConsoante(char *str, char*vetorConsoantes){
    int j = 0;

    while (*str != '\0'){

        // Verifica se o Caractere Atual é uma Vogal
        // - *str é o valor do caractere atual
        if(isConsoante(*str)) {
            // Cópia a Vogal encontrada para o vetor e Avança para a Próxima Posição
            *(vetorConsoantes + j) = *str;
            j++;
        }
        str++;
    }

    // Adicionando o Caractere nulo ao final do vetor
    // transformando ele em uma String Válida
    *(vetorConsoantes + j) = '\0';
}

int main(){
    
    char *str = "Internacional"; // ntrncnl
    char vetorConsoantes[sizeof(str)];

    extraiConsoante(str, vetorConsoantes);

    printf("Consoantes = %s  \n", vetorConsoantes);

    return 0;
}
