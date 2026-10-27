/**
 * Exercicio 1 - Parte 1
 *  - Implemente um Sistema de Atendimento Bancário
 *    * Implemente uma Fila de Clientes Prioritários;
 *    * Implemente uma fila de clientes comum;
 *      ° 1 => Prioritario
 *      ° 0 => Não Prioritario
 *    * Todo cliente deve escolher uma operação:
 *      ° 1 => Saque
 *      ° 2 => Deposito
 *    * Todo Cliente deve Informar o valor da Operação
 *
 * Compilar e Executar:
 * gcc atendimento_bancario.c -o atendimento_bancario
 * ./atendimento_bancario
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente {
    // dados do cliente bancário
    char nome[20];
    int operacao;           // 1 = Saque, 2 = Deposito
    float valor;
    int nFicha;
    int prioritario;        // 1 = Prioritario, 0 = Nao Prioritario
    struct cliente *proximo;
} Cliente;

typedef struct fila {
    // atributos de Fila
    Cliente *inicio;        // Inicio
    Cliente *fim;           // Fim
    int qtd;
} Fila;

Fila *criaFila() {
    Fila *fl = (Fila *) malloc(sizeof(Fila));
    if (fl == NULL) {
        return NULL;
    }
    fl->inicio = NULL;      // inicialização da fila
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}

/**
 * Função Auxiliar
 *  - Criando um Cliente (retorna NULL se os dados forem inválidos)
*/
Cliente *criaCliente(const char *nome, int operacao, float valor, int nFicha, int prioritario) {
    if (nome == NULL) {
        fprintf(stderr, "Erro: cliente sem nome.\n");
        return NULL;
    }
    if (operacao != 1 && operacao != 2) {
        fprintf(stderr, "Erro: operacao invalida (%d) para o cliente %s.\n", operacao, nome);
        return NULL;
    }
    if (prioritario != 0 && prioritario != 1) {
        fprintf(stderr, "Erro: prioridade invalida (%d) para o cliente %s.\n", prioritario, nome);
        return NULL;
    }
    if (valor <= 0) {
        fprintf(stderr, "Erro: valor invalido (%.2f) para o cliente %s.\n", valor, nome);
        return NULL;
    }

    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        return NULL;
    }
    snprintf(c->nome, sizeof(c->nome), "%s", nome);
    c->operacao = operacao;
    c->valor = valor;
    c->nFicha = nFicha;
    c->prioritario = prioritario;       // faltava esta linha na versão original
    c->proximo = NULL;
    return c;
}

/**
 * Enfileirar
 *  - Insere no Fim da Fila
*/
void enfileira(Fila *fl, Cliente *c) {
    if (fl == NULL || c == NULL) {
        return;
    }
    c->proximo = NULL;
    if (fl->inicio == NULL) {
        fl->inicio = c;
    } else {
        fl->fim->proximo = c;
    }
    fl->fim = c;
    fl->qtd++;
}

/**
 * Desenfileirar
 *  - Remove e retorna o primeiro da Fila (NULL se estiver vazia)
*/
Cliente *desenfileira(Fila *fl) {
    if (fl == NULL || fl->inicio == NULL) {
        return NULL;
    }
    Cliente *c = fl->inicio;
    fl->inicio = c->proximo;
    c->proximo = NULL;
    fl->qtd--;
    if (fl->inicio == NULL) {           // a fila ficou vazia
        fl->fim = NULL;
    }
    return c;
}

/**
 * Direciona UM cliente para a fila correta, conforme a prioridade
*/
void direcionarFilas(Fila *flComum, Fila *flPrioritaria, Cliente *c) {
    if (c == NULL) {
        return;
    }
    if (c->prioritario == 1) {
        enfileira(flPrioritaria, c);
    } else {
        enfileira(flComum, c);
    }
}

/**
 * Esvazia a fila de chegada, direcionando cada cliente (na ordem de chegada)
 * para a fila prioritária ou para a comum.
 * Os clientes são MOVIDOS (não copiados): cada um fica em uma única fila.
*/
void distribuiClientes(Fila *chegada, Fila *flComum, Fila *flPrioritaria) {
    Cliente *c;
    while ((c = desenfileira(chegada)) != NULL) {
        direcionarFilas(flComum, flPrioritaria, c);
    }
}

/**
 * Mostrando a Fila
*/
void mostraFila(const Fila *fl, const char *titulo) {
    printf("\n--- %s (%d clientes) ---\n", titulo, fl->qtd);
    if (fl->inicio == NULL) {
        printf("(fila vazia)\n");
        return;
    }
    int pos = 1;
    for (const Cliente *aux = fl->inicio; aux != NULL; aux = aux->proximo) {
        printf("%2d) Ficha %d | %-8s | %-8s | R$ %7.2f | %s\n",
               pos++, aux->nFicha, aux->nome,
               (aux->operacao == 1) ? "Saque" : "Deposito",
               aux->valor,
               (aux->prioritario == 1) ? "Prioritario" : "Comum");
    }
}

/**
 * Apagando a Fila
*/
void apagaFila(Fila *fl) {
    if (fl == NULL) {
        return;
    }
    Cliente *aux = fl->inicio;
    while (aux != NULL) {
        Cliente *prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    free(fl);
}


int main() {

    Fila *chegada = criaFila();             // fila geral, na ordem de chegada
    Fila *filaPrioritaria = criaFila();
    Fila *filaComum = criaFila();

    if (chegada == NULL || filaPrioritaria == NULL || filaComum == NULL) {
        fprintf(stderr, "Erro: sem memoria para criar as filas.\n");
        apagaFila(chegada);
        apagaFila(filaPrioritaria);
        apagaFila(filaComum);
        return 1;
    }

    // Clientes chegando ao banco (nome, operacao, valor, ficha, prioritario)
    enfileira(chegada, criaCliente("Ana",      1, 150.00f, 1, 1));
    enfileira(chegada, criaCliente("Lucas",    2, 550.00f, 2, 0));
    enfileira(chegada, criaCliente("Andressa", 1, 350.00f, 3, 0));
    enfileira(chegada, criaCliente("Pedro",    2, 250.00f, 4, 1));

    mostraFila(chegada, "Fila de chegada (antes de direcionar)");

    distribuiClientes(chegada, filaComum, filaPrioritaria);

    mostraFila(chegada,         "Fila de chegada (depois de direcionar)");
    mostraFila(filaPrioritaria, "Fila Prioritaria");
    mostraFila(filaComum,       "Fila Comum");

    apagaFila(chegada);
    apagaFila(filaPrioritaria);
    apagaFila(filaComum);
    return 0;
}
