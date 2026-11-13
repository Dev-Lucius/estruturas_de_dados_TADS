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
// gcc -Wall -Wextra -std=c11 -g -fsanitize=address,undefined Game.c -o Game

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PILHAS 4
#define NUM_TEMPS 2
#define CAP_PILHA 4
#define PINOS_POR_COR 3

#define FACIL 1
#define MEDIO 2
#define DIFICIL 3

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
    Pilha *slots[NUM_PILHAS + NUM_TEMPS];
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

// converter enum em Textos
const char *nomeCor(Cor cor){
    switch(cor){
        case VERMELHO: return "Vermelho";
        case VERDE: return "Verde";
        case AZUL: return "Azul";
        case AMARELO: return "Amarelo";
        default: return "Vazio";
    }
}

// Funções de Pilha
// Criar Pilha
Pilha *criarPilha(int capacidade){
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    if(p == NULL){
        printf("\n --- Erro de memoria ao criar Pilha!!");
        return NULL;
    }
    p->topo = NULL;
    p->tamanho = 0;
    p->capacidade = capacidade;
    return p;
}

// Criar um Pino
Pino *criarPino(Cor cor){
    Pino *pn = (Pino*) malloc(sizeof(Pino));
    if(pn == NULL){
        printf("\n --- Erro de memoria ao criar Pino!!");
        return NULL;
    }
    pn->cor = cor;
    pn->prox = NULL;
    return pn;
}

int vazia(Pilha *p){
    return p->topo == NULL;
}

int cheia(Pilha *p){
    return p->tamanho >= p->capacidade;
}

// push
int push(Pilha *p, Pino *pn){
    if(p == NULL || pn == NULL){
        printf("\n --- PUSH nao Realizado - Pilha ou Pino invalido!!");
        return 0;
    }
    if(cheia(p)){
        printf("\n --- PUSH nao Realizado - Pilha cheia!!");
        return 0;
    }
    pn->prox = p->topo;
    p->topo = pn;
    p->tamanho++;
    return 1;
}

// pop
Pino *pop(Pilha *p){
    if(p == NULL || vazia(p)){
        printf("\n --- POP nao Realizado - Pilha Vazia Ou Invalida!!");
        return NULL;
    }

    Pino *removido = p->topo;
    p->topo = removido->prox;
    p->tamanho--;
    removido->prox = NULL;
    return removido;
}

// liberar Pilha --> free()
void liberarPilha(Pilha *p){
    if(p == NULL){
        return;
    }

    // Esvaziando a pilha
    // Cada pop devolve um no que precisa de Free
    while(!vazia(p)){
        Pino *pn = pop(p);
        free(pn);
    }
    free(p);
}

// Funções de Jogo
int inicializarJogo(Jogo *jogo, int nivel){
    if(jogo == NULL){
        return 0;
    }

    switch(nivel){
        case FACIL:
            jogo->temps_ativos = 2;
            break;

        case MEDIO:
            jogo->temps_ativos = 1;
            break;

        case DIFICIL:
            jogo->temps_ativos = 0;
            break;

        default:
            return 0;
    }

    // Inicializando os Ponteiros das Pilhas
    for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){
        jogo->slots[i] = NULL;
    }

    // Criando as Seis Pilhas
    for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){
        int capacidade;

        if(i < NUM_PILHAS){
            capacidade = CAP_PILHA;
        } else {
            capacidade = 1;
        }

        jogo->slots[i] = criarPilha(capacidade);

        // Verificando se a alocação foi realizada com sucesso
        if(jogo->slots[i] == NULL){
            printf("\n Erro Ao Inicializar o Jogo!");

            // Liberando memória alocada
            for(int j = 0; j < NUM_PILHAS + NUM_TEMPS; j++){
                liberarPilha(jogo->slots[j]);
                jogo->slots[j] = NULL;
            }
            return 0;
        }
    }

    // Inicializando os Contadores
    jogo->movimentos = 0;
    jogo->inicio = time(NULL);

    return 1;
}

// embaralhar()
// -> Fisher-Yates
void embaralhar(Cor pinos[], int quantidade){
    for(int i = quantidade - 1; i > 0; i--){
        int j = rand() % (i + 1);

        // troca os elementos na posição
        Cor aux = pinos[i];
        pinos[i] = pinos[j];
        pinos[j] = aux; 
    }
}

// distribuirPinos()
int distribuirPinos(Jogo *jogo, Cor pinos[]){
    if(jogo == NULL || pinos == NULL){
        return 0;
    }

    for(int i = 0; i < NUM_PILHAS * PINOS_POR_COR; i++){
        
        // Descobrindo a Pilha de destino
        int indicePilha = i / PINOS_POR_COR;

        // Criando o Pino
        Pino *pn = criarPino(pinos[i]);

        if(pn == NULL){
            return 0;
        }

        // Inserindo o Pino na Pilha
        if(!push(jogo->slots[indicePilha], pn)){
            free(pn);
            return 0;
        }
    }
    return 1;
}

// exibirJogo()
void exibirJogo(Jogo *jogo){
    if(jogo == NULL) return;

    printf("\n========== TABULEIRO ==========\n");
    for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){

        if(i < NUM_PILHAS){
            printf("\nPilha P%d:\n", i + 1);
        } else {
            printf("\nTemporario T%d:\n", i - NUM_PILHAS + 1);
        }

        for(int j = jogo->slots[i]->tamanho - 1; j >= 0; j--){
            printf("[%s]\n", nomeCor(cor_na_posicao(jogo->slots[i], j)));
        }
    }
    printf("\n===============================\n");
}

// validarMovimento()
int validarMovimento(Jogo *jogo, int origem, int destino){
    if(jogo == NULL){
        printf("\nJogo inválido");
        return 0;
    }

    // Validando os Indices
    if(origem < 0 || origem >= NUM_PILHAS + NUM_TEMPS || destino < 0 || destino >= NUM_PILHAS + NUM_TEMPS){
        printf("\nIndice de Pilha Inválido!");
        return 0;
    }

    // validando se origem e destino sao iguais
    if(origem == destino){
        printf("\nOrigem e Destino Não Podem ser iguais");
        return 0;
    }

    // Validando a Existência das Pilhas
    if(jogo->slots[origem] == NULL || jogo->slots[destino] == NULL){
        printf("\nPilha Não Existe!");
        return 0;
    }

    // Verificando se o temporario esta disponivel
    if(origem >= NUM_PILHAS &&
       origem - NUM_PILHAS >= jogo->temps_ativos){

        printf("\nTemporario indisponivel neste nivel!");
        return 0;
    }

    if(destino >= NUM_PILHAS &&
       destino - NUM_PILHAS >= jogo->temps_ativos){

        printf("\nTemporario indisponivel neste nivel!");
        return 0;
    }

    // Verificando se a Origem  e Destino está Vazia
    if(vazia(jogo->slots[origem])){
        printf("\nA Pilha de Origem esta vazia");
        return 0;
    }

    if(vazia(jogo->slots[destino])){
        printf("\nA Pilha de Destino esta vazia");
        return 0;
    }
    return 1;
}

// MoverPino()

int moverPino(Jogo *jogo, int origem, int destino){

    // Validando o movimento
    if(!validarMovimento(jogo, origem, destino)){
        return 0;
    }

    // Retirando o pino do topo da origem
    Pino *pn = pop(jogo->slots[origem]);

    if(pn == NULL){
        return 0;
    }

    // Inserindo o pino no destino
    if(!push(jogo->slots[destino], pn)){

        // Se houver falha, devolve o pino a origem
        push(jogo->slots[origem], pn);

        return 0;
    }

    // Contabilizando o movimento
    jogo->movimentos++;
    return 1;
}

// Validando A Vitoria

int validarVitoria(Jogo *jogo){

    // Verificando se o jogo existe
    if(jogo == NULL){
        return 0;
    }

    // Verificando as quatro pilhas principais
    for(int i = 0; i < NUM_PILHAS; i++){

        Pilha *p = jogo->slots[i];

        // Verificando se a pilha existe
        if(p == NULL){
            return 0;
        }

        // Cada pilha deve possuir exatamente 3 pinos
        if(p->tamanho != PINOS_POR_COR){
            return 0;
        }

        // Todos os pinos devem possuir a mesma cor
        if(!pilha_uma_cor(p)){
            return 0;
        }
    }

    // Verificando se os temporarios estao vazios
    for(int i = NUM_PILHAS; i < NUM_PILHAS + NUM_TEMPS; i++){

        Pilha *p = jogo->slots[i];

        if(p == NULL || !vazia(p)){
            return 0;
        }
    }
    return 1;
}

// menu de dificuldade
int menuDificuldade(){

    int opcao;

    printf("\n========== DIFICULDADE ==========");
    printf("\n1 - Facil (2 temporarios)");
    printf("\n2 - Medio (1 temporario)");
    printf("\n3 - Dificil (nenhum temporario)");
    printf("\n0 - Sair");
    printf("\nEscolha uma dificuldade: ");

    if(scanf("%d", &opcao) != 1){
        while(getchar() != '\n');
        return -1;
    }

    switch(opcao){
        case 1:
            return FACIL;
        case 2:
            return MEDIO;
        case 3:
            return DIFICIL;
        case 0:
            return 0;
        default:
            return -1;
    }
}

int main(){

    // Inicializando o gerador de numeros aleatorios
    srand(time(NULL));

    Jogo jogo;

    printf("\nBem-vindo ao Jogo de Pinos!\n");

    int dificuldade = menuDificuldade();

    if(dificuldade == 0){
        printf("\nEncerrando o jogo...\n");
        return 0;
    }

    if(dificuldade == -1){
        printf("\nOpcao invalida!\n");
        return 1;
    }

    // Inicializando o jogo no nivel FACIL
    if(!inicializarJogo(&jogo, dificuldade)){
        printf("\nErro ao inicializar o jogo!");
        return 1;
    }

    // Criando o vetor de pinos
    Cor pinos[NUM_PILHAS * PINOS_POR_COR] = {
        VERMELHO, VERMELHO, VERMELHO,
        VERDE, VERDE, VERDE,
        AZUL, AZUL, AZUL,
        AMARELO, AMARELO, AMARELO
    };

    // Embaralhando os pinos
    embaralhar(pinos, NUM_PILHAS * PINOS_POR_COR);

    // Distribuindo os pinos
    if(!distribuirPinos(&jogo, pinos)){

        printf("\nErro ao distribuir os pinos!");

        // Liberando a memoria alocada
        for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){
            liberarPilha(jogo.slots[i]);
            jogo.slots[i] = NULL;
        }

        return 1;
    }

    // Exibindo o tabuleiro inicial
    exibirJogo(&jogo);

    // Testando a movimentacao
    printf("\n\n========== TESTE DE MOVIMENTO ==========");

    if(moverPino(&jogo, 0, 1)){
        printf("\nMovimento realizado com sucesso!");
    } else {
        printf("\nNao foi possivel realizar o movimento!");
    }

    // Contabilizando movimentos
    printf("\nTotal de movimentos: %d", jogo.movimentos);

    // Exibindo o tabuleiro atualizado
    exibirJogo(&jogo);

    printf("\n\n========== TESTE DE VITORIA ==========");

    if(validarVitoria(&jogo)){
        printf("\nParabens! Voce venceu!");
    } else {
        printf("\nA partida ainda nao terminou.");
    }

    // Liberando a memoria
    for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){
        liberarPilha(jogo.slots[i]);
        jogo.slots[i] = NULL;
    }

    return 0;
}

