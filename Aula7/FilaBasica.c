// Fila de Clientes do Caixa (fila simplesmente encadeada)
// Compilar e Executar:
// gcc fila_caixa.c -o fila_caixa
// ./fila_caixa

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TAM_NOME 20

// ---------------------------------------------------------------
// Estruturas
// ---------------------------------------------------------------
typedef struct cliente
{ // dados do cliente bancário
    char nome[TAM_NOME];
    int operacao;           // 1 = saque, 2 = depósito
    float valor;
    int nFicha;
    struct cliente *proximo;
} Cliente;

typedef struct fila
{ // atributos de Fila
    Cliente *inicio;        // início (próximo a ser atendido)
    Cliente *fim;           // fim (último que chegou)
    int qtd;
} Fila;

// ---------------------------------------------------------------
// Leitura segura do teclado
// (substitui scanf + fflush(stdin), que causa comportamento indefinido)
// ---------------------------------------------------------------

// Lê uma linha inteira, remove o '\n' e descarta o excesso que não coube.
// Retorna 0 se a entrada acabou (EOF), 1 caso contrário.
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

// Lê um inteiro entre min e max, repetindo até ser válido
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

// Lê um valor monetário positivo (aceita vírgula ou ponto)
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

// Lê um nome (aceita espaços; nomes maiores que o campo são cortados)
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
// Operações da Fila
// ---------------------------------------------------------------
Fila *criaFila()
{
    Fila *fl = (Fila *)malloc(sizeof(Fila));
    if (fl == NULL)
        return NULL;
    fl->inicio = NULL; // inicialização da fila
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}

Cliente *cadastraNovoCliente(const char *nome, int op, float vl, int ficha)
{
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (novo == NULL)
        return NULL;
    snprintf(novo->nome, sizeof(novo->nome), "%s", nome); // respeita o tamanho
    novo->operacao = op;
    novo->valor = vl;
    novo->nFicha = ficha;
    novo->proximo = NULL;
    return novo;
}

// Insere no fim da fila
void enfileirar(Fila *fl, Cliente *cl)
{
    if (fl == NULL || cl == NULL)
        return;

    cl->proximo = NULL;
    if (fl->inicio == NULL)
    { // Fila vazia
        fl->inicio = cl;
    }
    else
    { // Fila com elementos
        fl->fim->proximo = cl;
    }
    fl->fim = cl;
    fl->qtd++;
}

// Remove e retorna o primeiro da fila (NULL se estiver vazia).
// Não imprime nada: quem chama decide como avisar o usuário.
Cliente *desenfileirar(Fila *fl)
{
    if (fl == NULL || fl->inicio == NULL)
        return NULL;

    Cliente *aux = fl->inicio;
    fl->inicio = aux->proximo;
    aux->proximo = NULL;
    fl->qtd--;
    if (fl->inicio == NULL) // a fila ficou vazia
        fl->fim = NULL;
    return aux;
}

static const char *nomeOperacao(int op)
{
    return (op == 1) ? "Saque" : (op == 2) ? "Depósito" : "Desconhecida";
}

void mostraCliente(const Cliente *cl)
{
    printf("\n\t Ficha: %d | Nome: %s | Operação: %s | Valor: R$ %.2f",
           cl->nFicha, cl->nome, nomeOperacao(cl->operacao), cl->valor);
}

void mostraFila(const Fila *fl)
{
    if (fl->inicio == NULL)
    {
        printf("\n\t Fila Vazia!!");
        return;
    }
    for (const Cliente *aux = fl->inicio; aux != NULL; aux = aux->proximo)
        mostraCliente(aux);
}

// Libera a memória de um cliente
void apagaCliente(Cliente *cl)
{
    free(cl);
}

// Libera todos os clientes e a própria fila
void apagaFila(Fila *fl)
{
    if (fl == NULL)
        return;

    Cliente *aux;
    while ((aux = desenfileirar(fl)) != NULL)
        apagaCliente(aux);
    free(fl);
}

void atendimentoCaixa(const Cliente *cl)
{
    printf("\n** Cliente em atendimento **");
    mostraCliente(cl);
}

// ---------------------------------------------------------------
// Menu
// ---------------------------------------------------------------
static void entraNaFila(Fila *fl, int *ficha)
{
    char nome[TAM_NOME];
    int operacao;
    float valor;

    printf("\n Função Insere na Fila.\n");
    if (!lerNome("Informe o seu nome: ", nome, sizeof nome))
        return;
    if (!lerInteiro("Informe a operação (1-saque, 2-depósito): ", 1, 2, &operacao))
        return;
    if (!lerValor("Informe o valor: ", &valor))
        return;

    Cliente *novo = cadastraNovoCliente(nome, operacao, valor, *ficha);
    if (novo == NULL)
    {
        printf("\n\t Erro: sem memória para cadastrar o cliente.\n");
        return;
    }

    enfileirar(fl, novo);
    printf("\n\t Cliente cadastrado! Ficha nº %d, posição %d na fila.\n",
           *ficha, fl->qtd);
    (*ficha)++;
}

static void atendeProximo(Fila *fl)
{
    printf("\n Função Atender Próximo Cliente.\n");
    Cliente *cl = desenfileirar(fl);
    if (cl == NULL)
    {
        printf("\n\t Não há ninguém na fila para atender.\n");
        return;
    }
    atendimentoCaixa(cl);
    apagaCliente(cl);
    printf("\n\t Atendimento concluído. Restam %d na fila.\n", fl->qtd);
}

void menuCaixa(Fila *fl)
{
    int op;
    int ficha = 1; // número da próxima ficha a ser entregue

    do
    {
        printf("\n\nInforme uma Opção:");
        printf("\n -- 1 - para Entrar na Fila");
        printf("\n -- 2 - para Atender o Próximo Cliente (ele sai da fila)");
        printf("\n -- 3 - para Mostrar a Fila");
        printf("\n -- 0 - para Sair do Programa\n");

        if (!lerInteiro("\nInforme sua Opção: ", 0, 3, &op))
            op = 0; // entrada encerrada (EOF): sai do programa

        switch (op)
        {
        case 1:
            entraNaFila(fl, &ficha);
            break;
        case 2:
            atendeProximo(fl);
            break;
        case 3:
            printf("\n Mostra a Fila: Total na Fila = %d", fl->qtd);
            mostraFila(fl);
            break;
        case 0:
            printf("\nFim do Expediente\n");
            break;
        }
    } while (op != 0);
}

int main()
{
    Fila *filaTeste = criaFila();
    if (filaTeste == NULL)
    {
        fprintf(stderr, "Erro: sem memória para criar a fila.\n");
        return 1;
    }

    menuCaixa(filaTeste);

    apagaFila(filaTeste); // libera quem ainda estava na fila
    return 0;
}