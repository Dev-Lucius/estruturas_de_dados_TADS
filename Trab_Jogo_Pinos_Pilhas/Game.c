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
// - Compilando o Codigo em C usando o padrão C11
// - Ele avisa sobre qualquer suspeita de Warning ou Falhas de Memoria
// gcc -Wall -Wextra -std=c11 -g -fsanitize=address,undefined Game.c -o Game

#include <stdio.h>
#include <stdlib.h>
// Fornece funções para manipular hora e data
#include <time.h>
// Declara variavel global errno (do tipo int)
// -> armazenar códigos de erro
#include <errno.h>
#include <string.h>

#define NUM_PILHAS 4 // 4 Pilhas principais
#define NUM_TEMPS 2 // 2 Pilhas Temporarias
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

// Se todos os elementos da Pilha possuem a mesma cor
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

// Ler um numero inteiro digitado pelo jogador
// A ideia é centralizar e padronizar a leitura de números digitados pelo jogador
int lerInteiro(const char *mensagem, long *valor) {

    char linha[100];
    char *fim;

    printf("%s", mensagem);

    // Verificando se a leitura foi realizada
    // fgets() --> Captura uma Linha completa
    if (fgets(linha, sizeof(linha), stdin) == NULL) {
        return 0;
    }

    // Verificando se a linha ultrapassou o buffer
    if (strchr(linha, '\n') == NULL && !feof(stdin)) {
        int caractere;

        while ((caractere = getchar()) != '\n' && caractere != EOF);

        return -1;
    }

    // Convertendo texto para numero
    errno = 0;
    // strtol() -> conversão de conteúdo
    long numero = strtol(linha, &fim, 10);

    // Verificando se a conversao falhou
    if (fim == linha || errno == ERANGE) {
        return -1;
    }

    // Ignorando espacos e quebras de linha
    while (*fim == ' ' || *fim == '\t' ||
           *fim == '\n' || *fim == '\r') {
        fim++;
    }

    // Verificando caracteres adicionais
    if (*fim != '\0') {
        return -1;
    }

    *valor = numero;

    return 1;
}


// Funções de Pilha
// Responsável por alocar dinamicamente um novo nó do tipo pino
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
// Criar uma Estrutura do Tipo Pilha
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

// Verifica se a Pilha não possui elementos 
int vazia(Pilha *p){
    return p->topo == NULL;
}

// Verifica se a quantidade atual de elementos atingiu a capacidade máxima de Pilha
int cheia(Pilha *p){
    return p->tamanho >= p->capacidade;
}

// push (empurrar)
// Adicionar um novo elemento ao Topo
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

// pop (desempilhar)
// remove e retorna o elemento do topo
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
// Responsável por separar as Estruturas necessárias para uma nova partida
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
// -> Algoritmo de Fisher-Yates
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
// Função cuja responsabilidade por criar nós dos pinos e inseri-los nas pilhas principais 
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
// Função que monta o Tabuleiro
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
// Responsável por verificar se uma movimentação pode ser Realizada
int validarMovimento(Jogo *jogo, int origem, int destino){
    
    if(jogo->slots[origem] == NULL || jogo->slots[destino] == NULL){
    printf("\nPilha Não Existe!");
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

    // Verificando se o Destino esta cheio
    if(cheia(jogo->slots[destino])){
        printf("\nA Pilha de Destino esta Cheia");
        return 0;
    }
    return 1;
}

// MoverPino()
// Responsável por executar efetivamente a movimentação
int moverPino(Jogo *jogo, int origem, int destino){

    // Validando o movimento
    if(!validarMovimento(jogo, origem, destino)){
        return 0;
    }

    // Retirando o pino do topo da origem
    Pino *pn = pop(jogo->slots[origem]);

    if(pn == NULL){
        printf("\nErro ao retirar o pino da origem!");
        return 0;
    }

    // Inserindo o pino no destino
    if(!push(jogo->slots[destino], pn)){

        // Restaurando o pino na origem
        if(!push(jogo->slots[origem], pn)){
            printf("\nErro critico ao restaurar o pino!");
            return -1;
        }

        printf("\nFalha ao inserir o pino no destino!");
        return 0;
    }

    // Contabilizando o movimento
    jogo->movimentos++;
    return 1;
}

// função validarVitoria
// um jogador vence quando:
// - as quatro pilhas principais possuem exatamente tres pinos
// - Cada pilha principal tem apenas uma cor
// - as quatro pilhas apresentam cores distintas
// - as pilhas temporárias estavam vazias
int validarVitoria(Jogo *jogo){

    // Verificando se o jogo existe
    if(jogo == NULL){
        return 0;
    }

    // Registrando as cores encontradas
    int coresEncontradas[5] = {0};

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

        // Verificando se todos os pinos possuem a mesma cor
        if(!pilha_uma_cor(p)){
            return 0;
        }

        // Identificando a cor do topo
        Cor cor = cor_do_topo(p);

        // Verificando se a cor e valida
        if(cor < VERMELHO || cor > AMARELO){
            return 0;
        }

        // Impedindo duas pilhas da mesma cor
        if(coresEncontradas[cor]){
            return 0;
        }

        coresEncontradas[cor] = 1;
    }

    // Verificando se todas as quatro cores foram utilizadas
    for(int i = VERMELHO; i <= AMARELO; i++){
        if(!coresEncontradas[i]){
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

// menu de dificuldade que aparece antes de iniciar a partida
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


// Executar a partida
int executarJogo(Jogo *jogo){

    // Verificando se o jogo existe
    if(jogo == NULL){
        printf("\nJogo invalido!");
        return -1;
    }

    long opcao; // opcao escolhida pelo jogador
    long origem; // armazena a pilha de onde o pino será retirado
    long destino; // armazena a pilha que receberá o pino
    int encerramento = 0; // Controlando o encerramento da partida

    // Loop principal da partida
    while(1){

        // Verificando se o jogador venceu
        if(validarVitoria(jogo)){
            printf("\n\n========== VITORIA ==========");
            printf("\nParabens! Voce organizou todos os pinos!");
            break;
        }

        // Exibindo o tabuleiro atual
        exibirJogo(jogo);

        // Exibindo o menu de acoes equanto o jogo ainda não acabar
        printf("\n========== MENU DO JOGO ==========");
        printf("\n1 - Mover pino");
        printf("\n0 - Encerrar partida");
        printf("\n==================================\n");

        // Recebendo uma opcao valida do jogador
        int leitura;

        // repete a leitura enquanto o valor for inválido!
        do {
            leitura = lerInteiro(
                "\nEscolha uma opcao: ", &opcao
            );

            if(leitura == -1){
                printf("\nOpcao invalida! Digite um numero.\n");
            }

        } while(leitura == -1);

        // Verificando se a entrada foi encerrada
        if(leitura == 0){
            printf("\nEntrada encerrada.");
            encerramento = 1;
            break;
        }

        // Verificando a opcao escolhida no menu
        if(opcao == 0){

            printf("\nEncerrando a partida...");
            break;

        } else if(opcao == 1){

            // Recebendo a pilha de origem
            leitura = lerInteiro("\nDigite a pilha de origem (1-6): ", &origem);

            // Verifica se a Entrada foi encerrada
            if(leitura == 0){
                printf("\nEntrada encerrada.");
                encerramento = 1;
                break;
            }

            // Verificando se a origem foi informada corretamente
            // e se corresponde a uma das pilhas existentes
            if(leitura == -1 || origem < 1 || origem > NUM_PILHAS + NUM_TEMPS){
                printf("\nPilha de origem invalida!");
                continue;
            }

            // Recebendo a pilha de destino
            leitura = lerInteiro("Digite a pilha de destino (1-6): ", &destino);

            if(leitura == 0){
                printf("\nEntrada encerrada.");
                encerramento = 1;
                break;
            }

            // Verificando se o Destino foi informado corretamente
            if(leitura == -1 || destino < 1 || destino > NUM_PILHAS + NUM_TEMPS){
                printf("\nPilha de destino invalida!");
                continue;
            }

            // Convertendo os indices para o vetor slots
            // O jogador digita de 1 a 6, mas o vetor usa 0 a 5
            origem--;
            destino--;

            // Executando o movimento
            // A funcao moverPino realiza as validacoes
            // e manipula os nos das pilhas
            int resultado = moverPino(jogo, (int)origem, (int)destino);

            // Verificando o Resultado dos Movimentos
            if(resultado == 1){
                printf("\nMovimento realizado com sucesso!");
                printf("\nTotal de movimentos: %d", jogo->movimentos);

            } else if(resultado == -1){
                printf("\nFalha critica ao restaurar o pino!");
                encerramento = 1;
                break;
            } else {
                printf("\nNao foi possivel realizar o movimento!");
            }
        } else {
            printf("\nOpcao inexistente!");
        }
    }

    // Calculando o tempo de partida
    time_t fim = time(NULL); // horario atual
    double tempoTotal = difftime(fim, jogo->inicio); // calcula a diferença entre dois horarios

    // conversões
    long segundos = (long)tempoTotal;
    long horas = segundos / 3600;
    long minutos = (segundos % 3600) / 60;
    long restante = segundos % 60;

    // Exibindo as estatisticas finais
    printf("\n\n========== RESULTADO ==========");
    printf("\nMovimentos realizados: %d", jogo->movimentos);
    printf("\nTempo de partida: %02ld:%02ld:%02ld",
           horas, minutos, restante);
    printf("\n===============================");

    // Retornando o resultado da partida
    if(validarVitoria(jogo)){
        return 1;
    }

    return encerramento ? 0 : 0;
}




int main(){

    // Inicializando o gerador de numeros aleatorios
    srand(time(NULL));

    // Criando a estrutura do jogo
    Jogo jogo;

    printf("\nBem-vindo ao Jogo de Pinos!\n");

    // Selecionando a dificuldade
    int dificuldade = menuDificuldade();

    // Verificando se o jogador deseja sair
    if(dificuldade == 0){
        printf("\nEncerrando o jogo...\n");
        return 0;
    }

    // Verificando se a dificuldade e valida
    if(dificuldade == -1){
        printf("\nOpcao invalida!\n");
        return 1;
    }

    // Inicializando as pilhas e configurando a partida
    if(!inicializarJogo(&jogo, dificuldade)){
        printf("\nErro ao inicializar o jogo!\n");
        return 1;
    }

    // Criando o vetor com tres pinos de cada cor
    Cor pinos[NUM_PILHAS * PINOS_POR_COR] = {
        VERMELHO, VERMELHO, VERMELHO,
        VERDE, VERDE, VERDE,
        AZUL, AZUL, AZUL,
        AMARELO, AMARELO, AMARELO
    };

    // Embaralhando os pinos
    embaralhar(pinos, NUM_PILHAS * PINOS_POR_COR);

    // Distribuindo os pinos nas pilhas principais
    if(!distribuirPinos(&jogo, pinos)){

        printf("\nErro ao distribuir os pinos!");

        // Liberando as pilhas em caso de falha
        for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){
            liberarPilha(jogo.slots[i]);
            jogo.slots[i] = NULL;
        }

        return 1;
    }

    // Iniciando a partida
    executarJogo(&jogo);

    // Liberando a memoria de todas as pilhas
    for(int i = 0; i < NUM_PILHAS + NUM_TEMPS; i++){

        liberarPilha(jogo.slots[i]);

        jogo.slots[i] = NULL;
    }

    return 0;
}

