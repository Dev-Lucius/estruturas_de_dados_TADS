/*
 * ============================================================
 * Trabalho 02 de Estruturas de Dados
 *
 * Desenvolva uma aplicação em linguagem C que contemple
 * todas as operações fundamentais de uma Lista Simplesmente
 * Encadeada (LSE), com alocação dinâmica e liberação de memória.
 *
 * ============================================================
 *
 * Geração e Inserção Ordenada:
 *
 * - Gerar 1000 números inteiros aleatórios no intervalo
 *   de 0 a 1000;
 *
 * - Utilizar as funções de inserção para armazenar os valores,
 *   mantendo a ordem crescente;
 *
 * - Elementos duplicados/repetidos devem ser mantidos.
 *
 * ============================================================
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

/*
 * ============================================================
 * 1) IMPLEMENTANDO A ESTRUTURA DE DADOS DA LSE
 *
 * Um campo para armazenar um inteiro e um ponteiro
 * para o proximo elemento.
 * ============================================================
 */
typedef struct no {
    int valor;
    struct no *proximo;
} No;

/*
 * ============================================================
 * 2) IMPLEMENTANDO A ESTRUTURA DE LISTA SIMPLESMENTE
 * ENCADEADA
 * - Armazena o primeiro elemento;
 * - Armazena a quantidade de elementos inseridos.
 * ============================================================
 */
typedef struct lse {
    No *primeiro;
    int n_elementos;
} LSE;


/*
 * ============================================================
 * 3) IMPLEMENTANDO AS FUNCOES DE INSERCAO E REMOCAO
 * DA LSE
 * ============================================================
 * ------------------------------------------------------------
 * 3.1) INSERIR NO INICIO
 * ------------------------------------------------------------
 */

void inserirNoInicio(LSE *lista, No *novoNo) {
    novoNo->proximo = lista->primeiro;
    lista->primeiro = novoNo;
    lista->n_elementos++;
}

/*
 * ------------------------------------------------------------
 * 3.2) INSERIR NO FIM
 * ------------------------------------------------------------
 */

void inserirNoFim(LSE *lista, No *novoNo) {
    novoNo->proximo = NULL;
    // Caso a lista esteja vazia
    if (lista->primeiro == NULL) {
        lista->primeiro = novoNo;

    } else {
        No *aux = lista->primeiro;
        /*
         * Percorremos a lista ate encontrar
         * o ultimo elemento.
         */
        while (aux->proximo != NULL) {

            aux = aux->proximo;
        }
        // O ultimo elemento passa a apontar
        // para o novo elemento.
        aux->proximo = novoNo;
    }
    lista->n_elementos++;
}


/*
 * ------------------------------------------------------------
 * 3.3) INSERIR ORDENADO
 * ------------------------------------------------------------
 */

void inserirOrdenado(LSE *lista, No *novoNo) {
    // Caso 1: Lista Vazia ou Novo vem Antes do Primeiro
    if((lista->primeiro == NULL) || (novoNo->valor < lista->primeiro->valor)){
        inserirNoInicio(lista, novoNo);
        return;
    }
    // Caso 2: Procurar a Posição Correta
    No *aux = lista->primeiro;

    while((aux->proximo != NULL) && (aux->proximo->valor < novoNo->valor)){
        aux = aux->proximo;
    }

    // Inserir Entre aux e aux->proximo
    novoNo->proximo = aux->proximo;
    aux->proximo = novoNo;
    lista->n_elementos++;
}


/*
 * ============================================================
 * 4) IMPLEMENTANDO AS FUNCOES DE REMOCAO
 * ============================================================
 * ------------------------------------------------------------
 * 4.1) REMOVER NO INICIO
 * ------------------------------------------------------------
*/

No *removerNoInicio(LSE *lista) {
    // Verifica se a lista esta vazia
    if (lista->primeiro == NULL) {
        return NULL;
    }
    /*
     * Guarda o primeiro elemento.
     */
    No *removido = lista->primeiro;

    // O segundo elemento passa a ser o primeiro.
    lista->primeiro = removido->proximo;
    // Desconecta o elemento removido.
    removido->proximo = NULL;

    // Atualiza a quantidade de elementos.
    lista->n_elementos--;
    return removido;
}


/*
 * ------------------------------------------------------------
 * 4.2) REMOVER NO FIM
 * ------------------------------------------------------------
 */

No *removerNoFim(LSE *lista) {
    // Caso 1 --> Lista vazia
    if (lista->primeiro == NULL) {

        return NULL;
    }
    // Caso 2 --> A lista possui apenas UM elemento
    if (lista->primeiro->proximo == NULL) {
        No *removido = lista->primeiro;
        lista->primeiro = NULL;
        lista->n_elementos--;
        return removido;
    }

    // Caso 3 --> A lista possui DOIS ou MAIS elementos
    No *anterior = NULL;
    No *atual = lista->primeiro;

    // Percorremos a lista ate chegar no ultimo elemento.
    while (atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }
    // O PENULTIMO elemento vira o ULTIMO.
    anterior->proximo = NULL;
    lista->n_elementos--;
    return atual;
}


/*
 * ------------------------------------------------------------
 * 4.3) REMOVER POR VALOR
 * ------------------------------------------------------------
 */

No *removerValor(LSE *lista, int valor) {
    // Caso 1: Lista Vazia
    if(lista->primeiro == NULL){
        return NULL;
    }

    // Caso 2: O primeiro possui o valor desejado
    if(lista->primeiro->valor == valor){
        return removerNoInicio(lista);
    }

    // Caso 3: O valor está em uma posição específica da Lista
    No *anterior = lista->primeiro;
    No *atual = lista->primeiro->proximo;

    while(atual != NULL){
        // Ao encontrar o valor desejado ...
        if(atual->valor == valor){
            // Primeiro "Pulamos" o elemento removido
            anterior->proximo = atual->proximo;

            // A seguir, removemos o elemento em questão;
            atual->proximo = NULL;
            lista->n_elementos--;
            return atual;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    return NULL;
}


/*
 * ============================================================
 * 5) FUNCOES PARA ANALISE ESTATISTICA
 * ============================================================
 */

/*
 * ------------------------------------------------------------
 * 5.1) MENOR VALOR
 * ------------------------------------------------------------
 */

int obterMenor(LSE *lista) {
    // Lista Vazia --> Não há menor Valor
    if(lista->primeiro == NULL){
        return -1;
    }

    return lista->primeiro->valor;
}

/*
 * ------------------------------------------------------------
 * 5.2) MAIOR VALOR
 * ------------------------------------------------------------
 */

int obterMaior(LSE *lista) {

    if(lista->primeiro == NULL){
        return -1;
    }

    No *aux = lista->primeiro;

    while(aux->proximo != NULL){
        aux = aux->proximo;
    }
    
    return aux->valor;
}


/*
 * ------------------------------------------------------------
 * 5.3) MEDIA ARITMETICA
 * ------------------------------------------------------------
 */

double calcularMedia(LSE *lista) {

    if(lista->n_elementos == 0){
        return 0.0;
    }

    double soma = 0.0;
    No *aux = lista->primeiro;
    while(aux != NULL){
        soma += aux->valor;
        aux = aux->proximo;
    }
    // Retorando a Média
    return soma / lista->n_elementos;
}


/*
 * ------------------------------------------------------------
 * 5.4) DESVIO PADRAO
 * ------------------------------------------------------------
 */

double calcularDesvioPadrao(LSE *lista, double media) {

    if(lista->n_elementos == 0){
        return 0.0;
    }

    double somaQuadrados = 0.0;
    No *aux = lista->primeiro;

    while(aux != NULL){
        double diferenca = (aux->valor) - media;
        somaQuadrados += diferenca * diferenca;
        aux = aux->proximo; 
    }

    return sqrt(somaQuadrados / lista->n_elementos);
}


/*
 * ------------------------------------------------------------
 * 5.5) QUANTIDADE TOTAL DE VALORES REPETIDOS
 * ------------------------------------------------------------
 */

int contarRepetidos(LSE *lista) {

    int repetidos;
    No *aux = lista->primeiro;

    while((aux != NULL) && (aux->proximo != NULL)){
        if(aux->valor == aux->proximo->valor){
            repetidos++;
        }
        aux = aux->proximo;
    }

    return repetidos;
}


/*
 * ============================================================
 * 6) EXIBICAO FORMATADA
 * ============================================================
 */

void exibirMatriz(LSE *lista) {
    const int LINHAS = 50;
    const int COLUNAS = 20;

    No *aux=lista->primeiro;

    for(int i = 0; i < LINHAS; i++){
        for(int j = 0; j < COLUNAS; j++){
            // Se a lista estiver com menos de 1000 Elementos
            // A impressão é interrompida
            if(aux == NULL){
                printf("\n");
                return;
            }
            printf("%4d ", aux->valor);
            // Avançamos para o Próx Elemento
            aux = aux->proximo;
        }
        // Fim da Linha
        printf("\n");
    }
}


/*
 * ============================================================
 * 7) LIBERACAO DA MEMORIA
 * ============================================================
 *
 * Ao final do programa todos os nos criados com malloc()
 * devem ser liberados utilizando free().
 *
 * ------------------------------------------------------------
 */

void liberarLista(LSE *lista) {
    No *atual = lista->primeiro;

    while(atual != NULL){
        No *proximo = atual->proximo; // Guarda o proximo ANTES do free
        free(atual); // Libera o Nó Atual
        atual = proximo; // Avança para o Próximo
    }

    // Deixa a lista em estado consistente (vazia)
    lista->primeiro = NULL;
    lista->n_elementos = 0;
}

int main(){

    /* 
      - Inicializando a Lista
    */
    LSE listinha;
    listinha.primeiro = NULL;
    listinha.n_elementos = 0;

    /*
      - Geração e Inserção ordenada de 1000 Numeros
    */
    srand(time(NULL)); // Para cada execução, vamos mudar a sequencia

    for(int i = 0; i < 1000; i++){

        No *novo = (No*) malloc(sizeof(No));
        if(novo == NULL){
            printf("Erro: falha na alocação de memoria! \n");
            liberarLista(&listinha);
            return 1;
        }

        novo->valor = rand() % 1001; // Gerando Valores de úl0 a 1000 (Incluindo 1000)
        novo->proximo = NULL;
        inserirOrdenado(&listinha, novo);
    }
    printf("Elementos Inseridos: %d \n", listinha.n_elementos);

    /*
      - Exibição da Lista (50 x 20)
    */
    printf("\n --- LISTA ORDENADA (50 x 20) --- \n");
    exibirMatriz(&listinha);

    /*
      - Analise Estatistica
    */
    int menor = obterMenor(&listinha);
    int maior = obterMaior(&listinha);
    double media = calcularMedia(&listinha);
    double desvio = calcularDesvioPadrao(&listinha, media);
    int repetidos = contarRepetidos(&listinha);

    printf("\n=== ANALISE ESTATISTICA ===\n");
    printf("Menor valor: %d\n", menor);
    printf("Maior valor: %d\n", maior);
    printf("Media: %.2f\n", media);
    printf("Desvio padrao: %.2f\n", desvio);
    printf("Repetidos: %d\n", repetidos);

    /*
      - Testes de Remoções
      - OBS: Todo nó removido precisa de free() por quem chamou
    */
    printf("\n=== TESTE DE REMOCOES ===\n");

    No *removido = removerNoInicio(&listinha);
    if (removido != NULL) {
        printf("Removido no inicio: %d\n", removido->valor);
        free(removido);
    }

    removido = removerNoFim(&listinha);
    if (removido != NULL) {
        printf("Removido no fim   : %d\n", removido->valor);
        free(removido);
    }

    int alvo = 500;
    removido = removerValor(&listinha, alvo);
    if (removido != NULL) {
        printf("Removido o valor %d\n", removido->valor);
        free(removido);
    } else {
        printf("Valor %d nao encontrado na lista\n", alvo);
    }

    printf("Elementos restantes: %d\n", listinha.n_elementos);
    printf("\n=== LISTA APOS REMOCOES ===\n");
    exibirMatriz(&listinha);

    /*
      - Liberação de Memória
    */
    liberarLista(&listinha);
    printf("\nMemória Liberada. Fim\n");

    return 0;
}
