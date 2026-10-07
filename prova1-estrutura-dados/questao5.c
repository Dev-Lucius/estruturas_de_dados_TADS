// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

// Estruturas
typedef struct musica{
    int id;
    char titulos[30];
    char artista[30];
    int duracao;
} Musica;

typedef struct no{
    Musica dado;
    struct no *anterior;
    struct no *proximo;
} No;

typedef struct lista{
    No *primeiro;
    No *ultimo;
    No *musicaAtual;
    char nome[30];
    int num;
} LSE;

// Funções
// 1. InserirNovaMusicaInicio
void inserirNovaMusicaInicio(LSE *ls, No *novo){
    novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->num++;
}

// 2. InserirNovaMusicaFim
void inserirNovaMusicaFim(LSE *ls, No *novo){
    novo->proximo = NULL;

    if(ls->primeiro == NULL){
        ls->primeiro = novo;
    } else {
        No *aux = ls->primeiro;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    ls->num++;
}

// 3. AvancarMusica
void avancarMusica(LSE *ls){
}

// 4. RetrocederMusica


// 5. MostrarPlaylist
void mostrarPlaylist(LSE *ls, Musica *ms){
    
}
