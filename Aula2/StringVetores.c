#include <stdio.h>
#include <string.h>

/* ===========================================================
   EXERCICIOS 9, 10 e 11 - Vetores com retorno de ponteiro
   =========================================================== */

// 9) Retorna o ENDERECO do menor elemento do vetor
int* menorVetorPonteiro(int *vt, int n){
    int *pMenor = vt; // assume que o primeiro elemento e o menor
    for(int i = 1; i < n; i++){
        if(*(vt + i) < *pMenor)
            pMenor = (vt + i); // guarda o ENDERECO, nao o valor
    }
    return pMenor;
}

// 10) Retorna o ENDERECO do maior elemento do vetor
int* maiorVetorPonteiro(int *vt, int n){
    int *pMaior = vt;
    for(int i = 1; i < n; i++){
        if(*(vt + i) > *pMaior)
            pMaior = (vt + i);
    }
    return pMaior;
}

// Funcoes auxiliares (passagem por referencia) - exercicios 6 e 7
// usadas dentro do exercicio 11
void menorVetor(int *vt, int n, int *menor){
    *menor = vt[0];
    for(int i = 1; i < n; i++)
        if(vt[i] < *menor)
            *menor = vt[i];
}

void maiorVetor(int *vt, int n, int *maior){
    *maior = vt[0];
    for(int i = 1; i < n; i++)
        if(vt[i] > *maior)
            *maior = vt[i];
}

// 11) Reaproveita menorVetor e maiorVetor para preencher *menor e *maior
void menorMaiorVetorPonteiro(int *vt, int n, int *menor, int *maior){
    menorVetor(vt, n, menor);
    maiorVetor(vt, n, maior);
}


/* ===========================================================
   EXERCICIO 12 - Converte minutos em horas e minutos
   =========================================================== */

void Converte(int mnts, int *h, int *m){
    *h = mnts / 60;   // divisao inteira -> horas
    *m = mnts % 60;   // resto da divisao -> minutos
}


/* ===========================================================
   EXERCICIOS 13, 14, 15 e 16 - Strings: vogais e consoantes
   =========================================================== */

// Funcao auxiliar: verifica se um caractere e vogal
int ehVogal(char c){
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u' ||
            c=='A'||c=='E'||c=='I'||c=='O'||c=='U');
}

// Funcao auxiliar: verifica se um caractere e uma letra
int ehLetra(char c){
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

// 13) Copia todas as vogais da string 's' para o vetor 'vogais'
void extraiVogais(char *s, int n, char *vogais){
    int j = 0;
    for(int i = 0; i < n; i++){
        if(ehVogal(*(s + i)))
            *(vogais + j++) = *(s + i);
    }
    *(vogais + j) = '\0'; // finaliza a string resultante
}

// 14) Copia todas as consoantes da string 's' para o vetor 'consoantes'
void extraiConsoantes(char *s, int n, char *consoantes){
    int j = 0;
    for(int i = 0; i < n; i++){
        char c = *(s + i);
        if(ehLetra(c) && !ehVogal(c))
            *(consoantes + j++) = c;
    }
    *(consoantes + j) = '\0';
}

// 15) Conta quantas vogais existem na string
int contaVogais(char *s, int n){
    int cont = 0;
    for(int i = 0; i < n; i++)
        if(ehVogal(*(s + i)))
            cont++;
    return cont;
}

// 16) Conta quantas consoantes existem na string
int contaConsoantes(char *s, int n){
    int cont = 0;
    for(int i = 0; i < n; i++){
        char c = *(s + i);
        if(ehLetra(c) && !ehVogal(c))
            cont++;
    }
    return cont;
}


/* ===========================================================
   PROGRAMA PRINCIPAL - testa todas as funcoes acima
   =========================================================== */

int main(){

    printf("=== Exercicios 9, 10 e 11 - Menor e Maior (ponteiros) ===\n");
    int v[5] = {3, 4, 5, 2, 1};
    int n = 5;

    int *pMenor = menorVetorPonteiro(v, n);
    int *pMaior = maiorVetorPonteiro(v, n);
    printf("Menor elemento = %d (endereco %p)\n", *pMenor, (void*)pMenor);
    printf("Maior elemento = %d (endereco %p)\n", *pMaior, (void*)pMaior);

    int menor, maior;
    menorMaiorVetorPonteiro(v, n, &menor, &maior);
    printf("Via menorMaiorVetorPonteiro -> menor=%d  maior=%d\n\n", menor, maior);


    printf("=== Exercicio 12 - Converte minutos ===\n");
    int mnts = 135, h, m;
    Converte(mnts, &h, &m);
    printf("%d minutos = %dh e %dmin\n\n", mnts, h, m);


    printf("=== Exercicios 13, 14, 15 e 16 - Vogais e Consoantes ===\n");
    char frase[] = "Estrutura de Dados";
    int tamanho = strlen(frase); // strlen nao conta o '\0'

    char vogais[50], consoantes[50];
    extraiVogais(frase, tamanho, vogais);
    extraiConsoantes(frase, tamanho, consoantes);

    printf("Frase: %s\n", frase);
    printf("Vogais encontradas: %s\n", vogais);
    printf("Consoantes encontradas: %s\n", consoantes);
    printf("Quantidade de vogais: %d\n", contaVogais(frase, tamanho));
    printf("Quantidade de consoantes: %d\n", contaConsoantes(frase, tamanho));

    return 0;
}
