/**
 * Exercicios
 * Com base em uma Fila de Clientes Faça:
 *  - Função troca o primeiro da fila para o fim da fila;
 *  - Função troca o último da fila para a primeira posição;
 *  - Função copia fila (cria uma nova fila com os elementos iguais da fila principal)
 *  - Função troca o 5° elemento da fila para o fim da fila;
 *  - Função inverte fila, inverte todos elementos da fila;
 *  - Após cada função mostre a lista atualizada.
 * 
 * Compilar: gcc FilaExercicios.c -o FilaExercicios
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

Cliente *desenfileirar(Fila *fl){
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
 *  - Troca o elemento da posição n (1 = primeiro) para o fim da fila
*/
void trocaPosicaoParaFim(Fila *fl, int n) {
    if (fl == NULL || n < 1 || n > fl->qtd) {
        printf("\nPosicao %d invalida (a fila tem %d clientes).\n", n, fl->qtd);
        return;
    }
    if (n == 1) {
        PrimeiroParaFim(fl);
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

    // Obtém o cliente que será movido para o final da fila.
    // Ele está logo após o nó apontado por "anterior".
    Cliente *c = anterior->proximo;  

    // Retira o cliente da posição atual, ligando o nó anterior
    // diretamente ao próximo cliente.
    // Em seguida desconecta ele do resto da fila 
    anterior->proximo = c->proximo;     
    c->proximo = NULL;

    // o ultimo aponta para o cliente movido
    // atualiza o ponteiro "fim"
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

void inverterFilaAlternativo(Fila *fl) {
    if (fl == NULL || fl->qtd < 2) {
        return;                         // nada a inverter
    }
 
    Fila *copia = criaFila();
    if (copia == NULL) {
        return;                        
    }
 
    Cliente *aux = fl->inicio;
    while (aux != NULL) {
        // guarda o próximo ANTES de alterar aux->proximo
        Cliente *prox = aux->proximo;  
        // Insere aux no INÍCIO da copia (e não no fim, como faria o enfileira)
        aux->proximo = copia->inicio;
        copia->inicio = aux;
        if (copia->fim == NULL) {       // o primeiro cliente movido será o fim da copia
            copia->fim = aux;
        }
        copia->qtd++;
        aux = prox;                     // avança na fila original
    }
 
    // A copia agora está na ordem inversa: a fila original assume essa ordem
    fl->inicio = copia->inicio;
    fl->fim = copia->fim;
    fl->qtd = copia->qtd;
 
    free(copia);    // libera SÓ a estrutura Fila: os clientes agora pertencem a fl
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
 
    PrimeiroParaFim(fila);
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

    inverterFilaAlternativo(fila);
    mostraFila(fila, "6) Fila Invertida Alternativa");
 
    // A cópia continua intacta, pois é independente da original
    mostraFila(copia, "Copia (nao foi afetada)");
 
    apagaFila(fila);
    apagaFila(copia);
    return 0;
}
