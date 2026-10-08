// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

// Estruturas
typedef struct musica {
    int id;
    char titulos[30];
    char artista[30];
    int duracao;            // em segundos
} Musica;

typedef struct no {
    Musica dado;
    struct no *anterior;
    struct no *proximo;
} No;

typedef struct lista {
    No *primeiro;
    No *ultimo;
    No *musicaAtual;
    char nome[30];
    int num;
} Playlist;

// Funções auxiliares

// Inicializa a playlist vazia
void inicializarPlaylist(Playlist *ls, const char *nome) {
    ls->primeiro = NULL;
    ls->ultimo = NULL;
    ls->musicaAtual = NULL;
    ls->num = 0;
    snprintf(ls->nome, sizeof(ls->nome), "%s", nome);
}

// Cria um nó com a música informada
No* criarNo(Musica m) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        return NULL;
    }
    novo->dado = m;
    novo->anterior = NULL;
    novo->proximo = NULL;
    return novo;
}

// Libera todos os nós da playlist
void liberarPlaylist(Playlist *ls) {
    No *aux = ls->primeiro;
    while (aux != NULL) {
        No *prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    ls->primeiro = NULL;
    ls->ultimo = NULL;
    ls->musicaAtual = NULL;
    ls->num = 0;
}

// Funções

// 1. InserirNovaMusicaInicio
void inserirNovaMusicaInicio(Playlist *ls, No *novo) {
    if (ls == NULL || novo == NULL) {
        return;
    }

    novo->anterior = NULL;
    novo->proximo = ls->primeiro;

    if (ls->primeiro == NULL) {
        // Lista vazia: o novo nó é o primeiro, o último e o atual
        ls->ultimo = novo;
        ls->musicaAtual = novo;
    } else {
        ls->primeiro->anterior = novo;
    }

    ls->primeiro = novo;
    ls->num++;
}

// 2. InserirNovaMusicaFim
void inserirNovaMusicaFim(Playlist *ls, No *novo) {
    if (ls == NULL || novo == NULL) {
        return;
    }

    novo->proximo = NULL;
    novo->anterior = ls->ultimo;

    if (ls->ultimo == NULL) {
        // Lista vazia: o novo nó é o primeiro, o último e o atual
        ls->primeiro = novo;
        ls->musicaAtual = novo;
    } else {
        ls->ultimo->proximo = novo;
    }

    ls->ultimo = novo;
    ls->num++;
}

// 3. AvancarMusica
void avancarMusica(Playlist *ls) {
    if (ls == NULL || ls->musicaAtual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    if (ls->musicaAtual->proximo == NULL) {
        printf("Voce ja esta na ultima musica.\n");
        return;
    }

    ls->musicaAtual = ls->musicaAtual->proximo;
}

// 4. RetrocederMusica
void retrocederMusica(Playlist *ls) {
    if (ls == NULL || ls->musicaAtual == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    if (ls->musicaAtual->anterior == NULL) {
        printf("Voce ja esta na primeira musica.\n");
        return;
    }

    ls->musicaAtual = ls->musicaAtual->anterior;
}

// 5. MostrarPlaylist (a música atual é marcada com ">")
void mostrarPlaylist(const Playlist *ls) {
    if (ls == NULL) {
        return;
    }

    printf("=== Playlist: %s (%d musicas) ===\n", ls->nome, ls->num);

    if (ls->primeiro == NULL) {
        printf("(vazia)\n\n");
        return;
    }

    for (No *aux = ls->primeiro; aux != NULL; aux = aux->proximo) {
        printf("%s [%d] %s - %s (%d:%02d)\n",
               (aux == ls->musicaAtual) ? ">" : " ",
               aux->dado.id,
               aux->dado.titulos,
               aux->dado.artista,
               aux->dado.duracao / 60,
               aux->dado.duracao % 60);
    }
    printf("\n");
}

int main() {
    Playlist pl;
    inicializarPlaylist(&pl, "Favoritas");

    Musica m1 = {1, "Bohemian Rhapsody", "Queen", 354};
    Musica m2 = {2, "Hotel California", "Eagles", 391};
    Musica m3 = {3, "Imagine", "John Lennon", 183};

    inserirNovaMusicaFim(&pl, criarNo(m1));
    inserirNovaMusicaFim(&pl, criarNo(m2));
    inserirNovaMusicaInicio(&pl, criarNo(m3));

    mostrarPlaylist(&pl);

    avancarMusica(&pl);
    avancarMusica(&pl);
    mostrarPlaylist(&pl);

    avancarMusica(&pl);     // ja esta na ultima
    retrocederMusica(&pl);
    mostrarPlaylist(&pl);

    liberarPlaylist(&pl);
    return 0;
}
