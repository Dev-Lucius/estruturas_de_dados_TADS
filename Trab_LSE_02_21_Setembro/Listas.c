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
 *
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
 */


/*
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
 *
 * ATENCAO:
 *
 * Esta funcao e uma das partes que voce devera adaptar.
 *
 * Diferentemente da versao anterior, agora nao teremos
 * uma "posicao".
 *
 * O novo elemento deve ser inserido de acordo com o
 * seu valor, mantendo a lista em ordem crescente.
 *
 * Os valores repetidos devem continuar existindo.
 *
 * Exemplo:
 *
 * Lista:
 *
 * 10 -> 20 -> 20 -> 40
 *
 * Inserindo:
 *
 * 30
 *
 * Resultado:
 *
 * 10 -> 20 -> 20 -> 30 -> 40
 *
 * ------------------------------------------------------------
 */

void inserirOrdenado(LSE *lista, No *novoNo) {

    /*
     * IMPLEMENTE ESTA FUNCAO
     *
     * Dica:
     *
     * 1) Verifique se a lista esta vazia;
     *
     * 2) Verifique se o novo elemento deve ficar
     *    antes do primeiro;
     *
     * 3) Caso contrario, percorra a lista utilizando
     *    um ponteiro auxiliar;
     *
     * 4) Encontre a posicao correta;
     *
     * 5) Conecte o novo elemento;
     *
     * 6) Atualize n_elementos.
     */
}


/*
 * ============================================================
 * 4) IMPLEMENTANDO AS FUNCOES DE REMOCAO
 * ============================================================
 */


/*
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
 *
 * Esta funcao tambem devera ser implementada por voce.
 *
 * A ideia sera procurar um elemento pelo seu valor
 * e remove-lo da lista.
 *
 * Exemplo:
 *
 * Lista:
 *
 * 10 -> 20 -> 30 -> 40
 *
 * removerValor(&lista, 30)
 *
 * Resultado:
 *
 * 10 -> 20 -> 40
 *
 * ------------------------------------------------------------
 */

No *removerValor(LSE *lista, int valor) {

    /*
     * IMPLEMENTE ESTA FUNCAO
     *
     * Dica:
     *
     * 1) Verifique se a lista esta vazia;
     *
     * 2) Verifique se o primeiro elemento possui
     *    o valor procurado;
     *
     * 3) Caso contrario, utilize dois ponteiros:
     *
     *    anterior
     *    atual
     *
     * 4) Percorra a lista procurando o valor;
     *
     * 5) Desconecte o elemento encontrado;
     *
     * 6) Atualize n_elementos;
     *
     * 7) Retorne o elemento removido;
     *
     * 8) Caso o valor nao seja encontrado, retorne NULL.
     */
}


/*
 * ============================================================
 * 5) FUNCOES PARA ANALISE ESTATISTICA
 * ============================================================
 *
 * ESTAS FUNCOES SERAO IMPLEMENTADAS POR VOCE.
 *
 * O objetivo e praticar a percorrida da LSE.
 *
 * ------------------------------------------------------------
 */


/*
 * ------------------------------------------------------------
 * 5.1) MENOR VALOR
 * ------------------------------------------------------------
 */

int obterMenor(LSE *lista) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * Como a lista estara ordenada, pense em qual
     * elemento ja representa o menor valor.
     */
}


/*
 * ------------------------------------------------------------
 * 5.2) MAIOR VALOR
 * ------------------------------------------------------------
 */

int obterMaior(LSE *lista) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * A lista esta ordenada.
     * Percorra ate encontrar o ultimo elemento.
     */
}


/*
 * ------------------------------------------------------------
 * 5.3) MEDIA ARITMETICA
 * ------------------------------------------------------------
 */

double calcularMedia(LSE *lista) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * - Percorra todos os elementos;
     * - Some os valores;
     * - Divida pela quantidade de elementos.
     */
}


/*
 * ------------------------------------------------------------
 * 5.4) DESVIO PADRAO
 * ------------------------------------------------------------
 */

double calcularDesvioPadrao(LSE *lista, double media) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * Utilize a media calculada anteriormente.
     *
     * Para cada elemento:
     *
     * diferenca = valor - media
     *
     * Depois:
     *
     * diferenca * diferenca
     *
     * Some todos os resultados e aplique a formula
     * do desvio padrao.
     */
}


/*
 * ------------------------------------------------------------
 * 5.5) QUANTIDADE TOTAL DE VALORES REPETIDOS
 * ------------------------------------------------------------
 */

int contarRepetidos(LSE *lista) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * Como a lista esta ordenada, elementos repetidos
     * estarao lado a lado.
     *
     * Exemplo:
     *
     * 10 -> 20 -> 20 -> 30
     *
     * A comparacao entre um elemento e seu proximo
     * pode ajudar.
     */
}


/*
 * ============================================================
 * 6) EXIBICAO FORMATADA
 * ============================================================
 *
 * Imprimir a lista no formato:
 *
 * 50 linhas x 20 colunas
 *
 * Total:
 *
 * 50 * 20 = 1000 elementos
 *
 * ------------------------------------------------------------
 */

void exibirMatriz(LSE *lista) {

    /*
     * IMPLEMENTE
     *
     * Dica:
     *
     * Utilize dois loops:
     *
     * for das linhas
     * for das colunas
     *
     * Para cada posicao, avance o ponteiro
     * para o proximo elemento.
     */
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

}

