#include <stdio.h>
#include <string.h>

/* ===========================================================
   EXERCICIOS 9, 10 e 11 - Vetores com retorno de ponteiro
   =========================================================== */

// 9) Retorna o ENDEREÇO do menor elemento do vetor
int* menorVetorPonteiro(int *vt, int n) {

    if (n <= 0)
        return NULL;

    int *pMenor = vt;

    for (int i = 1; i < n; i++) {

        if (*(vt + i) < *pMenor) {
            pMenor = vt + i;
        }
    }

    return pMenor;
}


// 10) Retorna o ENDEREÇO do maior elemento do vetor
int* maiorVetorPonteiro(int *vt, int n) {

    if (n <= 0)
        return NULL;

    int *pMaior = vt;

    for (int i = 1; i < n; i++) {

        if (*(vt + i) > *pMaior) {
            pMaior = vt + i;
        }
    }

    return pMaior;
}


// Exercício 6
// Recebe o endereço de uma variável e deposita nela o menor valor
void menorVetor(int *vt, int n, int *menor) {

    if (n <= 0)
        return;

    *menor = *vt;

    for (int i = 1; i < n; i++) {

        if (*(vt + i) < *menor) {
            *menor = *(vt + i);
        }
    }
}


// Exercício 7
// Recebe o endereço de uma variável e deposita nela o maior valor
void maiorVetor(int *vt, int n, int *maior) {

    if (n <= 0)
        return;

    *maior = *vt;

    for (int i = 1; i < n; i++) {

        if (*(vt + i) > *maior) {
            *maior = *(vt + i);
        }
    }
}


// 11) Utiliza as funções anteriores para obter
// o menor e o maior valor do vetor
void menorMaiorVetorPonteiro(int *vt, int n, int *menor, int *maior) {

    menorVetor(vt, n, menor);
    maiorVetor(vt, n, maior);
}


/* ===========================================================
   EXERCICIO 12 - Converte minutos em horas e minutos
   =========================================================== */

void Converte(int mnts, int *h, int *m) {

    *h = mnts / 60;
    *m = mnts % 60;
}


/* ===========================================================
   EXERCICIOS 13, 14, 15 e 16 - Strings
   =========================================================== */

// Verifica se o caractere é uma vogal
int ehVogal(char c) {

    return (
        c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'
    );
}


// Verifica se o caractere é uma letra
int ehLetra(char c) {

    return (
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z')
    );
}


// 13) Copia todas as vogais da string para o vetor vogais
void extraiVogais(char *s, int n, char *vogais) {

    int j = 0;

    for (int i = 0; i < n; i++) {

        if (ehVogal(*(s + i))) {
            *(vogais + j) = *(s + i);
            j++;
        }
    }

    *(vogais + j) = '\0';
}


// 14) Copia todas as consoantes da string para o vetor consoantes
void extraiConsoantes(char *s, int n, char *consoantes) {

    int j = 0;

    for (int i = 0; i < n; i++) {

        char c = *(s + i);

        if (ehLetra(c) && !ehVogal(c)) {
            *(consoantes + j) = c;
            j++;
        }
    }

    *(consoantes + j) = '\0';
}


// 15) Conta quantas vogais existem na string
int contaVogais(char *s, int n) {

    int cont = 0;

    for (int i = 0; i < n; i++) {

        if (ehVogal(*(s + i))) {
            cont++;
        }
    }

    return cont;
}


// 16) Conta quantas consoantes existem na string
int contaConsoantes(char *s, int n) {

    int cont = 0;

    for (int i = 0; i < n; i++) {

        char c = *(s + i);

        if (ehLetra(c) && !ehVogal(c)) {
            cont++;
        }
    }

    return cont;
}


/* ===========================================================
   PROGRAMA PRINCIPAL
   =========================================================== */

int main() {

    /* =======================================================
       EXERCICIOS 9, 10 e 11
       ======================================================= */

    printf("=== Exercicios 9, 10 e 11 ===\n");

    int v[5] = {3, 4, 5, 2, 1};
    int n = 5;

    // Exercício 9
    int *pMenor = menorVetorPonteiro(v, n);

    // Exercício 10
    int *pMaior = maiorVetorPonteiro(v, n);

    if (pMenor != NULL) {
        printf("Menor elemento = %d\n", *pMenor);
        printf("Endereco do menor = %p\n", (void*)pMenor);
    }

    if (pMaior != NULL) {
        printf("Maior elemento = %d\n", *pMaior);
        printf("Endereco do maior = %p\n", (void*)pMaior);
    }


    // Exercício 11
    int menor;
    int maior;

    menorMaiorVetorPonteiro(v, n, &menor, &maior);

    printf("Menor = %d\n", menor);
    printf("Maior = %d\n\n", maior);


    /* =======================================================
       EXERCICIO 12
       ======================================================= */

    printf("=== Exercicio 12 ===\n");

    int mnts = 135;
    int h;
    int m;

    Converte(mnts, &h, &m);

    printf("%d minutos = %d horas e %d minutos\n\n",
           mnts, h, m);


    /* =======================================================
       EXERCICIOS 13, 14, 15 e 16
       ======================================================= */

    printf("=== Exercicios 13, 14, 15 e 16 ===\n");

    char frase[] = "Estrutura de Dados";

    int tamanho = strlen(frase);

    char vogais[50];
    char consoantes[50];

    extraiVogais(frase, tamanho, vogais);
    extraiConsoantes(frase, tamanho, consoantes);

    printf("Frase: %s\n", frase);

    printf("Vogais: %s\n", vogais);

    printf("Consoantes: %s\n", consoantes);

    printf("Quantidade de vogais: %d\n",
           contaVogais(frase, tamanho));

    printf("Quantidade de consoantes: %d\n",
           contaConsoantes(frase, tamanho));


    return 0;
}
