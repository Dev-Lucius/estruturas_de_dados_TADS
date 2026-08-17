/*
(Baseado no Exercício 13 da aula) Escreva a função void extraiVogais(char *str,
char *vetorVogais) que copie apenas as vogais da string str para o vetor
vetorVogais utilizando ponteiros
*/

#include <stdio.h>
#include <stdlib.h>

/*
    Verifica se um determinado caractere é uma vogal.

    Retorno:
        * 1 → é uma vogal
        * 0 → não é uma vogal

*/
int isVogal(char c){
    return c == 'a' || c == 'e' || c == 'i' ||
           c == 'o' || c == 'u' ||
           c == 'A' || c == 'E' || c == 'I' ||
           c == 'O' || c == 'U';
}

void extraiVogal(char *str, char*vetorVogais){
    int j = 0;

    while (*str != '\0'){

        // Verifica se o Caractere Atual é uma Vogal
        // - *str é o valor do caractere atual
        if(isVogal(*str)) {
            // Cópia a Vogal encontrada para o vetor e Avança para a Próxima Posição
            *(vetorVogais + j) = *str;
            j++;
        }
        str++;
    }

    // Adicionando o Caractere nulo ao final do vetor
    // transformando ele em uma String Válida
    *(vetorVogais + j) = '\0';
}


int main() {

    char *str = "Estrutura de Dados";
    char vetorVogais[50];

    extraiVogal(str, vetorVogais);

    printf("Vogais: %s\n", vetorVogais);

    return 0;
}
