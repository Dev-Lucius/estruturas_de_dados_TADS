// Exercício 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Estruturas ----------

typedef struct aluno {
    int matricula;
    char nome[50];
    struct aluno *proximo;
} Aluno;

typedef struct lse {
    Aluno *primeiro;
    int n_elementos;
} LSE;

// ---------- Funções de apoio ----------

void mostraAluno(Aluno *a) {
    printf("Matricula: %d | Nome: %s\n", a->matricula, a->nome);
}

Aluno* criaAluno(int matricula, const char *nome) {
    Aluno *novo = (Aluno *) malloc(sizeof(Aluno));
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->proximo = NULL;
    return novo;
}

void apagaAluno(Aluno *a) {
    free(a);
}

int retornaQuantidade(LSE *ls) {
    return ls->n_elementos;
}

// ---------- Inserção ----------

void inserirNoInicio(LSE *ls, Aluno *novo) {
    novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->n_elementos++;
}

void inserirNoFim(LSE *ls, Aluno *novo) {
    novo->proximo = NULL;

    if (ls->primeiro == NULL) {
        ls->primeiro = novo;
    } else {
        Aluno *aux = ls->primeiro;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    ls->n_elementos++;
}

void inserirNaPosicao(LSE *ls, Aluno *novo, int pos) {
    if (pos < 0 || pos > ls->n_elementos) return;  // posição inválida

    if (pos == 0) {
        inserirNoInicio(ls, novo);
        return;
    }
    if (pos == ls->n_elementos) {
        inserirNoFim(ls, novo);
        return;
    }

    // chegar até o nó da posição pos-1
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    novo->proximo = aux->proximo;  // salva primeiro
    aux->proximo = novo;           // liga depois
    ls->n_elementos++;
}

// ---------- Remoção ----------

Aluno* removerNoInicio(LSE *ls) {
    Aluno *aux = ls->primeiro;
    if (aux != NULL) {
        ls->primeiro = aux->proximo;
        aux->proximo = NULL;
        ls->n_elementos--;
    }
    return aux;  // pode ser NULL (lista vazia)
}

Aluno* removerNoFim(LSE *ls) {
    // Caso 1: lista vazia
    if (ls->primeiro == NULL) {
        return NULL;
    }

    // Caso 2: só um elemento
    if (ls->primeiro->proximo == NULL) {
        Aluno *removido = ls->primeiro;
        ls->primeiro = NULL;
        ls->n_elementos--;
        return removido;
    }

    // Caso 3: dois ou mais elementos
    Aluno *anterior = NULL;
    Aluno *atual = ls->primeiro;

    while (atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = NULL;   // penúltimo vira o fim
    ls->n_elementos--;
    return atual;
}

Aluno* removerNaPosicao(LSE *ls, int pos) {
    if (ls->primeiro == NULL || pos < 0 || pos >= ls->n_elementos) {
        return NULL;  // lista vazia ou posição inválida
    }

    if (pos == 0) {
        return removerNoInicio(ls);
    }

    // chegar até o nó da posição pos-1
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    Aluno *removido = aux->proximo;
    aux->proximo = removido->proximo;  // "pula" o nó removido
    removido->proximo = NULL;
    ls->n_elementos--;
    return removido;  // quem chama deve dar apagaAluno() depois
}

// ---------- Exibição ----------

void mostraLista(LSE *ls) {
    Aluno *aux = ls->primeiro;
    while (aux != NULL) {
        mostraAluno(aux);
        aux = aux->proximo;
    }
    printf("Fim da Lista!\n");
}

void mostraAlunoNaPosicao(LSE *ls, int pos) {
    if (pos < 0 || pos >= ls->n_elementos) {
        printf("Posicao invalida!\n");
        return;
    }
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos; i++) {
        aux = aux->proximo;
    }
    mostraAluno(aux);
}

// ---------- Limpeza ----------

void apagaLista(LSE *ls) {
    Aluno *aux = ls->primeiro;
    while (aux != NULL) {
        Aluno *prox = aux->proximo;  // salva antes de liberar!
        apagaAluno(aux);
        aux = prox;
    }
    ls->primeiro = NULL;
    ls->n_elementos = 0;
}

