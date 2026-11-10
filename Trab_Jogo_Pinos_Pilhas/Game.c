/*

- Trabalho Consiste Em:
    12 pinos, 4 cores: 3 pinos de cada cor.
    4 pilhas (P1–P4), capacidade 4 cada, mais 2 temporários (capacidade 1 cada).
    Início aleatório: 3 pinos por pilha, embaralhados (sobra 1 espaço livre em cada pilha).
    Objetivo: cada pilha com uma só cor.
    3 níveis: Fácil (Temp1 + Temp2), Médio (só Temp1), Difícil (sem temporários).
    Obrigatório: validar movimentos, validar fim de jogo, contar tempo (time()) e/ou movimentos, interface em terminal.
*/

// Compilação do Código
// gcc Game.c -o Game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PILHAS 4
#define NUM_TEMPS 2
#define CAP_PILHA 4
#define PINOS_POR_COR 3

// Estruturas
typedef enum {
    VAZIO = 0,
    VERMELHO,
    VERDE,
    AZUL,
    AMARELO
} Cor;

typedef struct Pino{
    Cor cor;
    struct Pino *prox;
} Pino;

typedef struct {
    Pino *topo;
    int tamanho; // quantos pinos há agora
    int capacidade; // 4 nas pilhas, 1 nos temporários
} Pilha;

typedef struct {
    Pilha slots[NUM_PILHAS + NUM_TEMPS];
    int temps_ativos;
    int movimentos;
    time_t inicio;
} Jogo;

// Funções Auxiliares
// Descobrindo a cor do topo
Cor cor_do_topo(Pilha *p){
    if(p->topo == NULL) return VAZIO;
    return p->topo->cor;
}

// Descobrindo a cor na posição
Cor cor_na_posicao(Pilha *p, int pos) {   
    if (pos < 0 || pos >= p->tamanho) return VAZIO;
    
    // quantos "prox" desde o topo
    int passos = p->tamanho - 1 - pos;   
    Pino *atual = p->topo;
    
    for (int i = 0; i < passos; i++){
        atual = atual->prox;
    }
    
    return atual->cor;
}

int pilha_uma_cor(Pilha *p){
    if(p->topo == NULL) return 0;
    
    Cor c = p->topo->cor;
    for(Pino *n = p->topo->prox; n != NULL; n = n->prox){
        if(n->cor != c) return 0;
    }
    return 1;
}

int main(){
    printf("Bem-Vindo ao Jogo de Pinos \n");

    return 0;
}