/**
 * Exercício 2 - Sistema de Atendimento Bancário (Partes 1 a 4)
 *
 *  Parte 1: Caixa e Gerente, cada um com fila Prioritária e fila Comum
 *           (o Gerente não tem operação nem valor)
 *  Parte 2: Quadro com o número da última ficha atendida em cada fila
 *  Parte 3: Regras de chamada
 *           - Caixa: Prioritário -> Comum -> Prioritário -> Comum ...
 *           - Gerente: chama sempre que houver alguém na fila
 *  Parte 4: Duas listas simplesmente encadeadas (LSE) de LOG,
 *           uma para o Caixa e outra para o Gerente
 *
 * Compilar e Executar:
 * gcc atendimento_completo.c -o atendimento_completo
 * ./atendimento_completo
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME 20
#define SERV_CAIXA 1
#define SERV_GERENTE 2

// ---------------------------------------------------------------
// Estruturas
// ---------------------------------------------------------------
typedef struct cliente
{
    char nome[TAM_NOME];
    int servico;            // 1 = Caixa, 2 = Gerente
    int operacao;           // 1 = Saque, 2 = Depósito (0 no Gerente)
    float valor;            // 0 no Gerente
    int nFicha;
    int prioritario;        // 1 = Prioritário, 0 = Comum
    struct cliente *proximo;
} Cliente;

typedef struct fila
{
    Cliente *inicio;
    Cliente *fim;
    int qtd;
} Fila;

// Um registro de LOG (nó da LSE): guarda uma CÓPIA dos dados do cliente atendido
typedef struct registro
{
    int ordem;              // ordem de atendimento dentro deste log
    int nFicha;
    char nome[TAM_NOME];
    int prioritario;
    int operacao;
    float valor;
    struct registro *proximo;
} Registro;

typedef struct listaLog
{
    Registro *primeiro;
    Registro *ultimo;       // permite inserir no fim em O(1)
    int qtd;
    char nome[30];
} ListaLog;

// Quadro: número da última ficha atendida (0 = ninguém atendido ainda)
typedef struct quadro
{
    int caixaPrioritario;
    int caixaComum;
    int gerentePrioritario;
    int gerenteComum;
} Quadro;

// Todo o estado do banco em um só lugar
typedef struct banco
{
    Fila *caixaPrior;
    Fila *caixaComum;
    Fila *gerentePrior;
    Fila *gerenteComum;
    Quadro quadro;
    ListaLog *logCaixa;
    ListaLog *logGerente;
    int proximaFicha;
    int turnoPrioritario;   // Caixa: 1 = a vez é do prioritário, 0 = do comum
} Banco;

// ---------------------------------------------------------------
// Leitura segura do teclado
// ---------------------------------------------------------------
static int lerLinha(const char *msg, char *buf, size_t tam)
{
    printf("%s", msg);
    fflush(stdout);

    if (fgets(buf, (int)tam, stdin) == NULL)
        return 0;

    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n')
        buf[len - 1] = '\0';
    else
    { // linha maior que o buffer: descarta o resto
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    return 1;
}

static int temTexto(const char *s)
{
    for (; *s; s++)
        if (!isspace((unsigned char)*s))
            return 1;
    return 0;
}

static int lerInteiro(const char *msg, int min, int max, int *valor)
{
    char buf[32];
    while (lerLinha(msg, buf, sizeof buf))
    {
        char *fim;
        long n = strtol(buf, &fim, 10);
        if (fim != buf && *fim == '\0' && n >= min && n <= max)
        {
            *valor = (int)n;
            return 1;
        }
        printf("Entrada inválida. Digite um número entre %d e %d.\n", min, max);
    }
    return 0;
}

static int lerValor(const char *msg, float *valor)
{
    char buf[32];
    while (lerLinha(msg, buf, sizeof buf))
    {
        for (char *p = buf; *p; p++)
            if (*p == ',')
                *p = '.';

        char *fim;
        double v = strtod(buf, &fim);
        if (fim != buf && *fim == '\0' && v > 0 && v < 1e9)
        {
            *valor = (float)v;
            return 1;
        }
        printf("Valor inválido. Digite um número positivo (ex.: 150.50).\n");
    }
    return 0;
}

static int lerNome(const char *msg, char *nome, size_t tam)
{
    while (lerLinha(msg, nome, tam))
    {
        if (temTexto(nome))
            return 1;
        printf("O nome não pode ficar vazio.\n");
    }
    return 0;
}

// ---------------------------------------------------------------
// Cliente e Fila
// ---------------------------------------------------------------

// Cria um cliente. Retorna NULL se os dados forem inválidos.
// No atendimento com o Gerente, operação e valor são ignorados.
Cliente *criaCliente(const char *nome, int servico, int operacao, float valor,
                     int nFicha, int prioritario)
{
    if (nome == NULL || (servico != SERV_CAIXA && servico != SERV_GERENTE))
    {
        fprintf(stderr, "Erro: cliente sem nome ou serviço inválido.\n");
        return NULL;
    }
    if (prioritario != 0 && prioritario != 1)
    {
        fprintf(stderr, "Erro: prioridade inválida (%d) para %s.\n", prioritario, nome);
        return NULL;
    }
    if (servico == SERV_CAIXA)
    {
        if (operacao != 1 && operacao != 2)
        {
            fprintf(stderr, "Erro: operação inválida (%d) para %s.\n", operacao, nome);
            return NULL;
        }
        if (valor <= 0)
        {
            fprintf(stderr, "Erro: valor inválido (%.2f) para %s.\n", valor, nome);
            return NULL;
        }
    }
    else
    {
        operacao = 0;
        valor = 0;
    }

    Cliente *c = (Cliente *)malloc(sizeof(Cliente));
    if (c == NULL)
        return NULL;
    snprintf(c->nome, sizeof(c->nome), "%s", nome);
    c->servico = servico;
    c->operacao = operacao;
    c->valor = valor;
    c->nFicha = nFicha;
    c->prioritario = prioritario;
    c->proximo = NULL;
    return c;
}

void apagaCliente(Cliente *c)
{
    free(c);
}

Fila *criaFila()
{
    Fila *fl = (Fila *)malloc(sizeof(Fila));
    if (fl == NULL)
        return NULL;
    fl->inicio = NULL;
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}

void enfileira(Fila *fl, Cliente *c)
{
    if (fl == NULL || c == NULL)
        return;
    c->proximo = NULL;
    if (fl->inicio == NULL)
        fl->inicio = c;
    else
        fl->fim->proximo = c;
    fl->fim = c;
    fl->qtd++;
}

// Remove e retorna o primeiro da fila (NULL se vazia)
Cliente *desenfileira(Fila *fl)
{
    if (fl == NULL || fl->inicio == NULL)
        return NULL;
    Cliente *c = fl->inicio;
    fl->inicio = c->proximo;
    c->proximo = NULL;
    fl->qtd--;
    if (fl->inicio == NULL)
        fl->fim = NULL;
    return c;
}

void apagaFila(Fila *fl)
{
    if (fl == NULL)
        return;
    Cliente *aux;
    while ((aux = desenfileira(fl)) != NULL)
        apagaCliente(aux);
    free(fl);
}

static void mostraCliente(const Cliente *c)
{
    printf("Ficha %d | %s | %s", c->nFicha, c->nome,
           c->prioritario ? "Prioritário" : "Comum");
    if (c->servico == SERV_CAIXA)
        printf(" | %s R$ %.2f", c->operacao == 1 ? "Saque" : "Depósito", c->valor);
}

static void mostraFila(const Fila *fl, const char *titulo)
{
    printf("\n--- %s (%d) ---\n", titulo, fl->qtd);
    if (fl->inicio == NULL)
    {
        printf("  (vazia)\n");
        return;
    }
    int pos = 1;
    for (const Cliente *aux = fl->inicio; aux != NULL; aux = aux->proximo)
    {
        printf("  %d) ", pos++);
        mostraCliente(aux);
        printf("\n");
    }
}

// ---------------------------------------------------------------
// Logs (Lista Simplesmente Encadeada)
// ---------------------------------------------------------------
ListaLog *criaListaLog(const char *nome)
{
    ListaLog *lg = (ListaLog *)malloc(sizeof(ListaLog));
    if (lg == NULL)
        return NULL;
    lg->primeiro = NULL;
    lg->ultimo = NULL;
    lg->qtd = 0;
    snprintf(lg->nome, sizeof(lg->nome), "%s", nome);
    return lg;
}

// Insere no fim do log uma cópia dos dados do cliente. Retorna 1 se deu certo.
int registraLog(ListaLog *lg, const Cliente *c)
{
    Registro *r = (Registro *)malloc(sizeof(Registro));
    if (r == NULL)
        return 0;
    r->ordem = lg->qtd + 1;
    r->nFicha = c->nFicha;
    snprintf(r->nome, sizeof(r->nome), "%s", c->nome);
    r->prioritario = c->prioritario;
    r->operacao = c->operacao;
    r->valor = c->valor;
    r->proximo = NULL;

    if (lg->primeiro == NULL)
        lg->primeiro = r;
    else
        lg->ultimo->proximo = r;
    lg->ultimo = r;
    lg->qtd++;
    return 1;
}

static void mostraLog(const ListaLog *lg)
{
    printf("\n--- LOG %s (%d registros) ---\n", lg->nome, lg->qtd);
    if (lg->primeiro == NULL)
    {
        printf("  (vazio)\n");
        return;
    }
    for (const Registro *r = lg->primeiro; r != NULL; r = r->proximo)
    {
        printf("  %2d) Ficha %d | %s | %s", r->ordem, r->nFicha, r->nome,
               r->prioritario ? "Prioritário" : "Comum");
        if (r->operacao != 0)
            printf(" | %s R$ %.2f", r->operacao == 1 ? "Saque" : "Depósito", r->valor);
        printf("\n");
    }
}

void apagaListaLog(ListaLog *lg)
{
    if (lg == NULL)
        return;
    Registro *aux = lg->primeiro;
    while (aux != NULL)
    {
        Registro *prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    free(lg);
}

// ---------------------------------------------------------------
// Banco
// ---------------------------------------------------------------
void apagaBanco(Banco *b)
{
    if (b == NULL)
        return;
    apagaFila(b->caixaPrior);
    apagaFila(b->caixaComum);
    apagaFila(b->gerentePrior);
    apagaFila(b->gerenteComum);
    apagaListaLog(b->logCaixa);
    apagaListaLog(b->logGerente);
    free(b);
}

Banco *criaBanco()
{
    Banco *b = (Banco *)calloc(1, sizeof(Banco)); // tudo começa zerado/NULL
    if (b == NULL)
        return NULL;

    b->caixaPrior = criaFila();
    b->caixaComum = criaFila();
    b->gerentePrior = criaFila();
    b->gerenteComum = criaFila();
    b->logCaixa = criaListaLog("Caixa");
    b->logGerente = criaListaLog("Gerente");
    b->proximaFicha = 1;
    b->turnoPrioritario = 1;    // Regra: o Caixa SEMPRE começa pelo prioritário

    if (!b->caixaPrior || !b->caixaComum || !b->gerentePrior || !b->gerenteComum ||
        !b->logCaixa || !b->logGerente)
    {
        apagaBanco(b);          // apaga só o que chegou a ser criado
        return NULL;
    }
    return b;
}

// Coloca o cliente na fila certa (serviço + prioridade)
static void direcionaCliente(Banco *b, Cliente *c)
{
    if (c->servico == SERV_CAIXA)
        enfileira(c->prioritario ? b->caixaPrior : b->caixaComum, c);
    else
        enfileira(c->prioritario ? b->gerentePrior : b->gerenteComum, c);
}

// Cria o cliente, entrega a ficha e coloca na fila. Retorna a ficha (0 = erro).
int cadastraCliente(Banco *b, const char *nome, int servico, int operacao,
                    float valor, int prioritario)
{
    Cliente *c = criaCliente(nome, servico, operacao, valor, b->proximaFicha, prioritario);
    if (c == NULL)
        return 0;
    direcionaCliente(b, c);
    return b->proximaFicha++;
}

// ---- Parte 2: Quadro ------------------------------------------------
static void atualizaQuadro(Quadro *q, const Cliente *c)
{
    if (c->servico == SERV_CAIXA)
    {
        if (c->prioritario)
            q->caixaPrioritario = c->nFicha;
        else
            q->caixaComum = c->nFicha;
    }
    else
    {
        if (c->prioritario)
            q->gerentePrioritario = c->nFicha;
        else
            q->gerenteComum = c->nFicha;
    }
}

static void imprimeFicha(int n)
{
    if (n > 0)
        printf("%02d", n);
    else
        printf("--");
}

static void mostraQuadro(const Quadro *q)
{
    printf("\n=========== ÚLTIMOS CLIENTES ATENDIDOS ===========");
    printf("\n Atendimento ao Caixa");
    printf("\n    Prioritário N° = "); imprimeFicha(q->caixaPrioritario);
    printf("\n    Comum       N° = "); imprimeFicha(q->caixaComum);
    printf("\n Atendimento Gerente");
    printf("\n    Prioritário N° = "); imprimeFicha(q->gerentePrioritario);
    printf("\n    Comum       N° = "); imprimeFicha(q->gerenteComum);
    printf("\n==================================================\n");
}

// ---- Parte 3: Regras de chamada --------------------------------------

// Escolhe o próximo cliente do Caixa (alternando prioritário/comum).
// Se a fila da vez estiver vazia, atende a outra para o caixa não ficar parado,
// e a vez NÃO muda (quem foi "pulado" continua sendo o próximo da vez).
static Cliente *proximoDoCaixa(Banco *b)
{
    Cliente *c = NULL;

    if (b->turnoPrioritario)
    {
        if (b->caixaPrior->qtd > 0)
        {
            c = desenfileira(b->caixaPrior);
            b->turnoPrioritario = 0;            // próximo: comum
        }
        else if (b->caixaComum->qtd > 0)
        {
            c = desenfileira(b->caixaComum);    // sem prioritário: vez continua dele
        }
    }
    else
    {
        if (b->caixaComum->qtd > 0)
        {
            c = desenfileira(b->caixaComum);
            b->turnoPrioritario = 1;            // próximo: prioritário
        }
        else if (b->caixaPrior->qtd > 0)
        {
            c = desenfileira(b->caixaPrior);    // sem comum: vez continua dele
        }
    }
    return c;
}

// Gerente: chama sempre que houver alguém (prioritários primeiro)
static Cliente *proximoDoGerente(Banco *b)
{
    Cliente *c = desenfileira(b->gerentePrior);
    if (c == NULL)
        c = desenfileira(b->gerenteComum);
    return c;
}

// Atende: atualiza o quadro, grava no log correspondente e libera o cliente
static void atende(Banco *b, Cliente *c, const char *guiche)
{
    printf("\n>>> Chamando ao %s: ", guiche);
    mostraCliente(c);
    printf("\n");

    atualizaQuadro(&b->quadro, c);                                  // Parte 2

    ListaLog *log = (c->servico == SERV_CAIXA) ? b->logCaixa : b->logGerente;
    if (!registraLog(log, c))                                       // Parte 4
        printf("Aviso: sem memória para registrar no log.\n");

    apagaCliente(c);
}

static void chamaCaixa(Banco *b)
{
    Cliente *c = proximoDoCaixa(b);
    if (c == NULL)
    {
        printf("\n\t Não há clientes na fila do Caixa.\n");
        return;
    }
    atende(b, c, "Caixa");
}

static void chamaGerente(Banco *b)
{
    Cliente *c = proximoDoGerente(b);
    if (c == NULL)
    {
        printf("\n\t Não há clientes na fila do Gerente.\n");
        return;
    }
    atende(b, c, "Gerente");
}

// ---------------------------------------------------------------
// Menu
// ---------------------------------------------------------------
static void mostraFilas(const Banco *b)
{
    mostraFila(b->caixaPrior,   "Caixa - Prioritários");
    mostraFila(b->caixaComum,   "Caixa - Comuns");
    mostraFila(b->gerentePrior, "Gerente - Prioritários");
    mostraFila(b->gerenteComum, "Gerente - Comuns");
}

static void mostraLogs(const Banco *b)
{
    mostraLog(b->logCaixa);
    mostraLog(b->logGerente);
}

static void cadastraInterativo(Banco *b)
{
    char nome[TAM_NOME];
    int servico, prior, operacao = 0;
    float valor = 0;

    printf("\n Retirar ficha.\n");
    if (!lerNome("Nome: ", nome, sizeof nome))
        return;
    if (!lerInteiro("Atendimento (1-Caixa, 2-Gerente): ", 1, 2, &servico))
        return;
    if (!lerInteiro("Prioritário? (1-Sim, 0-Não): ", 0, 1, &prior))
        return;
    if (servico == SERV_CAIXA)
    { // com o Gerente não há operação nem valor
        if (!lerInteiro("Operação (1-Saque, 2-Depósito): ", 1, 2, &operacao))
            return;
        if (!lerValor("Valor: ", &valor))
            return;
    }

    int ficha = cadastraCliente(b, nome, servico, operacao, valor, prior);
    if (ficha == 0)
        printf("\n\t Erro ao cadastrar o cliente.\n");
    else
        printf("\n\t Ficha nº %d - %s, fila %s.\n", ficha,
               servico == SERV_CAIXA ? "Caixa" : "Gerente",
               prior ? "Prioritária" : "Comum");
}

static void carregaExemplo(Banco *b)
{
    //                   nome       serviço       op  valor    prior
    cadastraCliente(b, "Ana",      SERV_CAIXA,   1, 150.00f, 1);
    cadastraCliente(b, "Lucas",    SERV_CAIXA,   2, 550.00f, 0);
    cadastraCliente(b, "Andressa", SERV_CAIXA,   1, 350.00f, 0);
    cadastraCliente(b, "Pedro",    SERV_CAIXA,   2, 250.00f, 1);
    cadastraCliente(b, "Marta",    SERV_GERENTE, 0,   0.00f, 1);
    cadastraCliente(b, "Joao",     SERV_GERENTE, 0,   0.00f, 0);
    cadastraCliente(b, "Bia",      SERV_CAIXA,   1,  90.00f, 1);
    cadastraCliente(b, "Caio",     SERV_GERENTE, 0,   0.00f, 0);
    printf("\n\t 8 clientes de exemplo cadastrados (fichas 1 a 8).\n");
}

static void menu(Banco *b)
{
    int op;
    do
    {
        printf("\n\n===== Atendimento Bancário =====");
        printf("\n -- 1 - Retirar ficha (novo cliente)");
        printf("\n -- 2 - Chamar próximo cliente ao Caixa");
        printf("\n -- 3 - Chamar próximo cliente ao Gerente");
        printf("\n -- 4 - Mostrar as filas");
        printf("\n -- 5 - Mostrar o quadro de atendimento");
        printf("\n -- 6 - Mostrar os logs");
        printf("\n -- 7 - Carregar clientes de exemplo");
        printf("\n -- 0 - Sair do Programa\n");

        if (!lerInteiro("\nInforme sua Opção: ", 0, 7, &op))
            op = 0; // entrada encerrada (EOF): sai do programa

        switch (op)
        {
        case 1: cadastraInterativo(b); break;
        case 2: chamaCaixa(b);         break;
        case 3: chamaGerente(b);       break;
        case 4: mostraFilas(b);        break;
        case 5: mostraQuadro(&b->quadro); break;
        case 6: mostraLogs(b);         break;
        case 7: carregaExemplo(b);     break;
        case 0:
            printf("\nFim do Expediente. Registros do dia:\n");
            mostraLogs(b);
            break;
        }
    } while (op != 0);
}

int main()
{
    Banco *banco = criaBanco();
    if (banco == NULL)
    {
        fprintf(stderr, "Erro: sem memória para criar o banco.\n");
        return 1;
    }

    menu(banco);

    apagaBanco(banco);  // libera filas (com quem ainda estiver nelas) e logs
    return 0;
}