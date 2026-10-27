/**
 * Exercicios
 * Com base em uma Fila de Clientes Faça:
 *  - Função troca o primeiro da fila para o fim da fila;
 *  - Função troca o último da fila para a primeira posição;
 *  - Função copia fila (cria uma nova fila com os elementos iguais da fila principal)
 *  - Função troca o 5° elemento da fila para o fim da fila;
 *  - Função inverte fila, inverte todos elementos da fila;
 *  - Após cada função mostre a lista atualizada.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cliente{ 
    // dados do cliente bancário
    char nome[20];
    int operacao; // 1 = deposito, 2= deposito, 3 = pagamento
    float valor;
    int nFicha;
    struct cliente *proximo;
} Cliente;

typedef struct fila{   
    // atributos de Fila
    Cliente *inicio; // Inicio
    Cliente *fim;    // Fim
    int qtd;
} Fila;

Fila *criaFila(){
    Fila *fl = (Fila *)malloc(sizeof(Fila));
    fl->inicio = NULL; // inicialização da fila
    fl->fim = NULL;
    fl->qtd = 0;
    return fl;
}

/**
 * Função Auxiliar
 *  - Criando um Cliente
*/
// Criar Cliente
Cliente *criaCliente(const char *nome, int operacao, float valor, int nFicha) {
    Cliente *c = (Cliente *) malloc(sizeof(Cliente));
    if (c == NULL) {
        return NULL;
    }
    snprintf(c->nome, sizeof(c->nome), "%s", nome);
    c->operacao = operacao;
    c->valor = valor;
    c->nFicha = nFicha;
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
    if (fl->inicio == NULL) {       // fila vazia
        fl->inicio = c;
    } else {
        fl->fim->proximo = c;
    }
    fl->fim = c;
    fl->qtd++;
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
    for (Cliente *aux = fl->inicio; aux != NULL; aux = aux->proximo) {
        printf("%2d) Ficha %d | %-8s | op %d | R$ %.2f\n",
               pos++, aux->nFicha, aux->nome, aux->operacao, aux->valor);
    }
}

/**
 * Apagando a Fila
*/
void apagaFila(Fila *fl) {
    Cliente *aux = fl->inicio;
    while (aux != NULL) {
        Cliente *prox = aux->proximo;
        free(aux);
        aux = prox;
    }
    free(fl);
}


// Exercicios
/**
 * Ex01
 *  - Troca o primeiro da fila para o fim da fila
*/
void PrimeiroParaFim(Fila *fl){
    // 1° Caso
    // Se a Fila for vazia, ou tiver apenas um elementos
    if(fl == NULL || fl->qtd < 2){
        return;
    }

    // Guarda o Primeiro
    Cliente *c = fl->inicio;

    // o Segundo passa a ser o Primeiro
    fl->inicio = c->proximo;
    c->proximo = NULL;

    // Liga o antigo Primeiro ao Final
    fl->fim->proximo = c;
    fl->fim;
}

/**
 * Ex02
 *  - Troca o último da fila para a primeira posição
*/
void ultimoParaInicio(Fila *fl){
    if(fl == NULL || fl->qtd < 2){
        return;
    }

    // Precisamos do PENÚLTIMO para "soltar" o último
    Cliente *penultimo = fl->inicio;

    while (penultimo->proximo != fl->fim){
        penultimo = penultimo->proximo;
    }

    Cliente *ultimo = fl->fim;

    // Penultimo vira o Novo Fim
    penultimo->proximo = NULL; 

    // último aponta para o antigo inicio
    ultimo->proximo = fl->inicio;

    // Invertendo o ultimo com o primeiro
    fl->inicio = ultimo;
    fl->fim = penultimo;
}

/**
 * Ex03
 *  - Copia a fila (nova fila com clientes novos, de mesmos dados)
*/
Fila *copiaFila(const Fila *original){
    Fila *copia = criaFila();

    if(copia == NULL){
        return NULL;
    }

    for (Cliente *aux = original->inicio; aux != NULL; aux = aux->proximo) {
        Cliente *novo = criaCliente(aux->nome, aux->operacao,aux->valor, aux->nFicha);
        enfileira(copia, novo);
    }
    return copia;
}

/**
 * Ex04
 *  - Troca o elemento da posição n (1 = primeiro) para o fim da fil
*/
void trocaPosicaoParaFim(Fila *fl, int n) {
    if (fl == NULL || n < 1 || n > fl->qtd) {
        printf("\nPosicao %d invalida (a fila tem %d clientes).\n", n, fl->qtd);
        return;
    }
    if (n == 1) {
        primeiroParaFim(fl);
        return;
    }

    // já é o último
    if (n == fl->qtd) {
        return;                        
    }

    // chega até o nó ANTES do n-ésimo
    Cliente *anterior = fl->inicio;     
    for (int i = 1; i < n - 1; i++) {
        anterior = anterior->proximo;
    }

    // n-ésimo cliente
    Cliente *c = anterior->proximo;

    // "costura" a fila sem ele    
    anterior->proximo = c->proximo;     
    c->proximo = NULL;

    fl->fim->proximo = c;
    fl->fim = c;
}

/**
 * Ex04 (versão pedida)
 *  - Troca o 5º elemento para o fim da fila
 */
void quintoParaFim(Fila *fl) {
    trocaPosicaoParaFim(fl, 5);
}

/**
 * Ex05
 *  - Inverte a Fila (Inverter o Sentido)
*/
void invertaFila(Fila *fl) {
    if (fl == NULL || fl->qtd < 2) {
        return;
    }
    Cliente *anterior = NULL;
    Cliente *atual = fl->inicio;
    fl->fim = fl->inicio;               // o antigo primeiro será o último
    while (atual != NULL) {
        Cliente *prox = atual->proximo; // guarda o próximo antes de mexer
        atual->proximo = anterior;      // inverte a ligação
        anterior = atual;
        atual = prox;
    }
    fl->inicio = anterior;              // o antigo último será o primeiro
}

int main() {
    Fila *fila = criaFila();
 
    enfileira(fila, criaCliente("Ana",    1, 150.00f, 1));
    enfileira(fila, criaCliente("Bruno",  2,  80.50f, 2));
    enfileira(fila, criaCliente("Carla",  3, 320.00f, 3));
    enfileira(fila, criaCliente("Diego",  1,  45.90f, 4));
    enfileira(fila, criaCliente("Elisa",  2, 500.00f, 5));
    enfileira(fila, criaCliente("Fabio",  3,  99.99f, 6));
    enfileira(fila, criaCliente("Gabi",   1,  10.00f, 7));
 
    mostraFila(fila, "Fila original");
 
    primeiroParaFim(fila);
    mostraFila(fila, "1) Primeiro foi para o fim");
 
    ultimoParaInicio(fila);
    mostraFila(fila, "2) Ultimo foi para o inicio");
 
    Fila *copia = copiaFila(fila);
    mostraFila(fila,  "3) Fila principal (apos copiar)");
    mostraFila(copia, "3) Copia da fila");
 
    quintoParaFim(fila);
    mostraFila(fila, "4) Quinto foi para o fim");
 
    invertaFila(fila);
    mostraFila(fila, "5) Fila invertida");
 
    // A cópia continua intacta, pois é independente da original
    mostraFila(copia, "Copia (nao foi afetada)");
 
    apagaFila(fila);
    apagaFila(copia);
    return 0;
}
