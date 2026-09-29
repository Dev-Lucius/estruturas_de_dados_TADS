/*
 * ============================================================
 * Aula 5 - Lista Duplamente Encadeada (LDE) em C
 *
 * Exercicios:
 *   1) Implementar as funcoes em branco:
 *        insereNaPosicao, removeNoInicio, removeNoFim,
 *        removeNaPosicao
 *   2) Testar a criacao de uma lista com varias tarefas,
 *      realizando varias insercoes e remocoes
 *   3) Mostrar as atividades cadastradas e encerrar o programa
 *
 * Convencao: posicoes contadas a partir de 0 (E0, E1, ...).
 *
 * Compilar:  gcc -Wall -Wextra -o lde lista_duplamente_encadeada.c
 * Executar:  ./lde         -> teste automatico (exercicios 2 e 3)
 *            ./lde menu    -> menu interativo
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ============================================================
 * 1) ESTRUTURAS DE DADOS
 * ============================================================ */

/* Elemento (no) da lista: dados + ponteiros anterior e proximo */
typedef struct tarefa {
    char descricao[30];
    int id, prioridade, concluida;
    struct tarefa *anterior;
    struct tarefa *proximo;
} Tarefa;

/* Lista: primeiro, ultimo (facultativo) e contador de elementos */
typedef struct LDE {
    Tarefa *primeiro;
    Tarefa *ultimo;
    char nome[30];
    int num;
} LDE;


/* ============================================================
 * 2) PROTOTIPOS
 * ============================================================ */

LDE    *criaListaLDE(const char nome[]);
Tarefa *criaTarefa(int id, const char descricao[], int prioridade);
Tarefa *criaTarefaInterativa(int id);

void insereNoInicio(LDE *l, Tarefa *tf);
void insereNoFim(LDE *l, Tarefa *tf);
int  insereNaPosicao(LDE *l, Tarefa *tf, int p);

Tarefa *removeNoInicio(LDE *l);
Tarefa *removeNoFim(LDE *l);
Tarefa *removeNaPosicao(LDE *l, int p);

void mostraTarefa(const Tarefa *t);
void mostraListaED(const LDE *l);
void mostraListaDE(const LDE *l);
void mostraTarefaPosicao(LDE *l, int posicao);

void apagaElemento(Tarefa *tf);
void apagaLDE(LDE *l);

int  verificaLista(const LDE *l);
void testeAutomatico(void);
void menu(LDE *l);


/* ============================================================
 * 3) CRIACAO
 * ============================================================ */

/* Cria e inicializa uma lista vazia */
LDE *criaListaLDE(const char nome[]) {
    LDE *nova = (LDE *) malloc(sizeof(LDE));

    if (nova == NULL) {
        return NULL;
    }

    strncpy(nova->nome, nome, sizeof(nova->nome) - 1);
    nova->nome[sizeof(nova->nome) - 1] = '\0';
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->num = 0;

    return nova;
}

/* Cria uma tarefa a partir de parametros (usada no teste automatico) */
Tarefa *criaTarefa(int id, const char descricao[], int prioridade) {
    Tarefa *nova = (Tarefa *) malloc(sizeof(Tarefa));

    if (nova == NULL) {
        return NULL;
    }

    nova->id = id;
    nova->prioridade = prioridade;
    nova->concluida = 0;
    strncpy(nova->descricao, descricao, sizeof(nova->descricao) - 1);
    nova->descricao[sizeof(nova->descricao) - 1] = '\0';
    nova->anterior = NULL;
    nova->proximo = NULL;

    return nova;
}

/* Descarta o que sobrou na linha de entrada (substitui fflush(stdin),
 * que tem comportamento indefinido em C padrao) */
static void limpaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Cria uma tarefa lendo os dados do teclado (usada no menu) */
Tarefa *criaTarefaInterativa(int id) {
    int prioridade;
    char descricao[30];

    printf("Informe sua Prioridade: ");
    if (scanf("%d", &prioridade) != 1) {
        limpaBuffer();
        printf("Prioridade invalida.\n");
        return NULL;
    }
    limpaBuffer();

    printf("Informe a Descricao: ");
    if (scanf("%29[^\n]", descricao) != 1) {
        limpaBuffer();
        printf("Descricao invalida.\n");
        return NULL;
    }
    limpaBuffer();

    Tarefa *nova = criaTarefa(id, descricao, prioridade);
    if (nova != NULL) {
        printf("Tarefa criada com sucesso\n");
    }
    return nova;
}


/* ============================================================
 * 4) BUSCA AUXILIAR
 * ============================================================ */

/*
 * Retorna o no na posicao p (0 a num-1), ou NULL se invalida.
 * Aproveita a lista ser DUPLA: se p esta na primeira metade,
 * parte do primeiro; senao, parte do ultimo e volta.
 */
static Tarefa *buscaPosicao(const LDE *l, int p) {
    if (p < 0 || p >= l->num) {
        return NULL;
    }

    Tarefa *aux;

    if (p <= l->num / 2) {
        aux = l->primeiro;
        for (int i = 0; i < p; i++) {
            aux = aux->proximo;
        }
    } else {
        aux = l->ultimo;
        for (int i = l->num - 1; i > p; i--) {
            aux = aux->anterior;
        }
    }

    return aux;
}


/* ============================================================
 * 5) INSERCAO
 * ============================================================ */

void insereNoInicio(LDE *l, Tarefa *tf) {
    tf->anterior = NULL;

    if (l->primeiro == NULL) {              /* lista vazia */
        tf->proximo = NULL;
        l->ultimo = tf;
    } else {                                /* lista com elementos */
        tf->proximo = l->primeiro;
        l->primeiro->anterior = tf;
    }

    l->primeiro = tf;
    l->num++;
}

void insereNoFim(LDE *l, Tarefa *tf) {
    tf->proximo = NULL;

    if (l->primeiro == NULL) {              /* lista vazia */
        insereNoInicio(l, tf);              /* ja faz o num++ */
    } else {                                /* Theta(1) com *ultimo */
        tf->anterior = l->ultimo;
        l->ultimo->proximo = tf;
        l->ultimo = tf;
        l->num++;
    }
}

/*
 * EXERCICIO 1: insere tf na posicao p (o novo elemento passa a
 * ocupar a posicao p). Posicoes validas: 0 a num.
 * Retorna 1 se inseriu, 0 se a posicao e invalida.
 */
int insereNaPosicao(LDE *l, Tarefa *tf, int p) {
    if (p < 0 || p > l->num) {
        return 0;
    }

    if (p == 0) {                           /* inicio (inclui lista vazia) */
        insereNoInicio(l, tf);
        return 1;
    }

    if (p == l->num) {                      /* fim */
        insereNoFim(l, tf);
        return 1;
    }

    /* Meio: 'atual' e quem ocupa hoje a posicao p.
     * O novo no entra entre atual->anterior e atual. */
    Tarefa *atual = buscaPosicao(l, p);

    tf->anterior = atual->anterior;
    tf->proximo = atual;
    atual->anterior->proximo = tf;
    atual->anterior = tf;
    l->num++;

    return 1;
}


/* ============================================================
 * 6) REMOCAO (retornam o no removido; o chamador da o free)
 * ============================================================ */

/* EXERCICIO 1: remove e retorna o primeiro elemento */
Tarefa *removeNoInicio(LDE *l) {
    if (l->primeiro == NULL) {
        return NULL;
    }

    Tarefa *removido = l->primeiro;

    l->primeiro = removido->proximo;

    if (l->primeiro == NULL) {              /* a lista ficou vazia */
        l->ultimo = NULL;
    } else {
        l->primeiro->anterior = NULL;
    }

    removido->proximo = NULL;
    l->num--;

    return removido;
}

/* EXERCICIO 1: remove e retorna o ultimo elemento (Theta(1)) */
Tarefa *removeNoFim(LDE *l) {
    if (l->ultimo == NULL) {
        return NULL;
    }

    Tarefa *removido = l->ultimo;

    l->ultimo = removido->anterior;

    if (l->ultimo == NULL) {                /* a lista ficou vazia */
        l->primeiro = NULL;
    } else {
        l->ultimo->proximo = NULL;
    }

    removido->anterior = NULL;
    l->num--;

    return removido;
}

/* EXERCICIO 1: remove e retorna o elemento da posicao p (0 a num-1).
 * Retorna NULL se a posicao e invalida. */
Tarefa *removeNaPosicao(LDE *l, int p) {
    if (p < 0 || p >= l->num) {
        return NULL;
    }

    if (p == 0) {
        return removeNoInicio(l);
    }

    if (p == l->num - 1) {
        return removeNoFim(l);
    }

    /* Meio: o no tem vizinhos dos dois lados */
    Tarefa *removido = buscaPosicao(l, p);

    removido->anterior->proximo = removido->proximo;
    removido->proximo->anterior = removido->anterior;

    removido->anterior = NULL;
    removido->proximo = NULL;
    l->num--;

    return removido;
}


/* ============================================================
 * 7) EXIBICAO
 * ============================================================ */

void mostraTarefa(const Tarefa *t) {
    printf("Tarefa N %d\n", t->id);
    printf("\tDescricao : %s\n", t->descricao);
    printf("\tPrioridade: %d\n", t->prioridade);
    printf("\tTarefa %s.\n", t->concluida ? "concluida" : "nao concluida");
}

/* Esquerda -> direita, navegando por *proximo */
void mostraListaED(const LDE *l) {
    printf("\n---------- Lista de %s (ED) ----------\n", l->nome);

    if (l->primeiro == NULL) {
        printf("LISTA VAZIA!\n");
        return;
    }

    printf("Inicio da Lista!\n");
    for (const Tarefa *aux = l->primeiro; aux != NULL; aux = aux->proximo) {
        mostraTarefa(aux);
    }
    printf("Fim da Lista ED! (%d tarefa(s))\n", l->num);
}

/* Direita -> esquerda, navegando por *anterior */
void mostraListaDE(const LDE *l) {
    printf("\n---------- Lista de %s (DE) ----------\n", l->nome);

    if (l->ultimo == NULL) {
        printf("LISTA VAZIA!\n");
        return;
    }

    printf("Inicio da Lista!\n");
    for (const Tarefa *aux = l->ultimo; aux != NULL; aux = aux->anterior) {
        mostraTarefa(aux);
    }
    printf("Fim da Lista DE! (%d tarefa(s))\n", l->num);
}

void mostraTarefaPosicao(LDE *l, int posicao) {
    Tarefa *t = buscaPosicao(l, posicao);

    if (t == NULL) {
        printf("Posicao %d invalida (validas: 0 a %d).\n", posicao, l->num - 1);
    } else {
        mostraTarefa(t);
    }
}


/* ============================================================
 * 8) LIBERACAO DE MEMORIA
 * ============================================================ */

void apagaElemento(Tarefa *tf) {
    free(tf);
}

/* Libera todos os nos e deixa a lista vazia e reutilizavel */
void apagaLDE(LDE *l) {
    Tarefa *atual = l->primeiro;

    while (atual != NULL) {
        Tarefa *prox = atual->proximo;      /* guarda ANTES do free */
        apagaElemento(atual);
        atual = prox;
    }

    l->primeiro = NULL;
    l->ultimo = NULL;
    l->num = 0;
}


/* ============================================================
 * 9) VERIFICACAO DE CONSISTENCIA (apoio aos testes)
 *
 * Confere: primeiro/ultimo, ligacoes nos dois sentidos e num.
 * Retorna 1 se tudo esta correto, 0 caso contrario.
 * ============================================================ */

int verificaLista(const LDE *l) {
    if (l->num == 0) {
        return l->primeiro == NULL && l->ultimo == NULL;
    }

    if (l->primeiro == NULL || l->ultimo == NULL) return 0;
    if (l->primeiro->anterior != NULL)            return 0;
    if (l->ultimo->proximo != NULL)               return 0;

    /* percurso direto, checando os elos de volta */
    int cont = 0;
    const Tarefa *ant = NULL;
    for (const Tarefa *t = l->primeiro; t != NULL; t = t->proximo) {
        if (t->anterior != ant) return 0;
        ant = t;
        cont++;
        if (cont > l->num) return 0;        /* evita laco infinito */
    }
    if (cont != l->num || ant != l->ultimo) return 0;

    /* percurso reverso */
    cont = 0;
    for (const Tarefa *t = l->ultimo; t != NULL; t = t->anterior) {
        cont++;
        if (cont > l->num) return 0;
    }

    return cont == l->num;
}

static void confere(const char *etapa, const LDE *l) {
    printf("[%s] num = %d | consistencia: %s\n",
           etapa, l->num, verificaLista(l) ? "OK" : "ERRO");
}


/* ============================================================
 * 10) TESTE AUTOMATICO (EXERCICIOS 2 e 3)
 * ============================================================ */

void testeAutomatico(void) {
    LDE *lista = criaListaLDE("MINHAS TAREFAS");
    Tarefa *t;

    if (lista == NULL) {
        printf("Erro: falha na alocacao de memoria!\n");
        return;
    }

    printf("=== EXERCICIO 2: INSERCOES ===\n");

    insereNoFim(lista, criaTarefa(1, "Acordar", 1));
    insereNoFim(lista, criaTarefa(4, "Ir_trabalho", 3));
    confere("2 insercoes no fim", lista);

    insereNaPosicao(lista, criaTarefa(2, "Escovar_Dentes", 2), 1);
    insereNaPosicao(lista, criaTarefa(3, "Tomar_Cafe", 3), 2);
    confere("2 insercoes na posicao (meio)", lista);

    insereNoInicio(lista, criaTarefa(5, "Desligar_Despertador", 1));
    insereNaPosicao(lista, criaTarefa(6, "Voltar_Para_Casa", 2), lista->num);
    confere("inicio + posicao == num (fim)", lista);

    /* Posicao invalida: a insercao falha e o no precisa ser liberado */
    t = criaTarefa(99, "Invalida", 1);
    if (!insereNaPosicao(lista, t, 50)) {
        printf("Insercao na posicao 50 recusada (invalida), como esperado.\n");
        apagaElemento(t);
    }

    mostraListaED(lista);
    mostraListaDE(lista);

    printf("\n=== EXERCICIO 2: REMOCOES ===\n");

    t = removeNoInicio(lista);
    printf("removeNoInicio   -> %s\n", t->descricao);
    apagaElemento(t);
    confere("apos removeNoInicio", lista);

    t = removeNoFim(lista);
    printf("removeNoFim      -> %s\n", t->descricao);
    apagaElemento(t);
    confere("apos removeNoFim", lista);

    t = removeNaPosicao(lista, 1);
    printf("removeNaPosicao1 -> %s\n", t->descricao);
    apagaElemento(t);
    confere("apos removeNaPosicao(1)", lista);

    if (removeNaPosicao(lista, 50) == NULL) {
        printf("removeNaPosicao(50) devolveu NULL (invalida), como esperado.\n");
    }

    printf("\n=== EXERCICIO 3: ATIVIDADES CADASTRADAS ===\n");
    mostraListaED(lista);
    mostraListaDE(lista);

    printf("\n=== CASOS DE BORDA: ESVAZIAR A LISTA ===\n");
    while ((t = removeNoFim(lista)) != NULL) {
        printf("removido do fim: %s\n", t->descricao);
        apagaElemento(t);
    }
    confere("lista esvaziada", lista);

    if (removeNoInicio(lista) == NULL && removeNoFim(lista) == NULL) {
        printf("Remocao em lista vazia devolveu NULL, como esperado.\n");
    }

    /* Lista com 1 unico elemento: primeiro == ultimo */
    insereNaPosicao(lista, criaTarefa(7, "Unica", 1), 0);
    confere("1 unico elemento", lista);
    t = removeNaPosicao(lista, 0);
    apagaElemento(t);
    confere("de volta a vazia", lista);

    /* Encerramento: libera tudo */
    insereNoFim(lista, criaTarefa(8, "Sera_liberada_no_final", 1));
    apagaLDE(lista);
    free(lista);
    printf("\nMemoria liberada. Fim do programa.\n");
}


/* ============================================================
 * 11) MENU INTERATIVO
 * ============================================================ */

static int leInteiro(const char *msg, int *valor) {
    printf("%s", msg);
    if (scanf("%d", valor) != 1) {
        limpaBuffer();
        printf("Entrada invalida.\n");
        return 0;
    }
    limpaBuffer();
    return 1;
}

void menu(LDE *l) {
    int op, posicao, id = 1;
    Tarefa *tf;

    do {
        printf("\n\nInforme uma Opcao:");
        printf("\n -- 1  - Inserir Tarefa no Inicio");
        printf("\n -- 2  - Inserir Tarefa no Fim");
        printf("\n -- 3  - Inserir Tarefa na Posicao");
        printf("\n -- 4  - Remover Tarefa no Inicio");
        printf("\n -- 5  - Remover Tarefa no Fim");
        printf("\n -- 6  - Remover Tarefa na Posicao");
        printf("\n -- 7  - Mostrar uma Tarefa da Posicao");
        printf("\n -- 8  - Mostrar a Lista ED");
        printf("\n -- 9  - Mostrar a Lista DE");
        printf("\n -- 10 - Apagar Lista");
        printf("\n -- 0  - Sair do Programa\n");

        if (!leInteiro("\nInforme sua Opcao: ", &op)) {
            op = -1;
            continue;
        }

        switch (op) {
        case 1:
            tf = criaTarefaInterativa(id);
            if (tf != NULL) { insereNoInicio(l, tf); id++; }
            break;

        case 2:
            tf = criaTarefaInterativa(id);
            if (tf != NULL) { insereNoFim(l, tf); id++; }
            break;

        case 3:
            if (!leInteiro("Posicao (0 a num): ", &posicao)) break;
            if (posicao < 0 || posicao > l->num) {
                printf("Posicao invalida (validas: 0 a %d).\n", l->num);
                break;
            }
            tf = criaTarefaInterativa(id);
            if (tf != NULL) {
                insereNaPosicao(l, tf, posicao);
                id++;
            }
            break;

        case 4:
            tf = removeNoInicio(l);
            if (tf == NULL) printf("Lista vazia.\n");
            else { printf("Removida: %s\n", tf->descricao); apagaElemento(tf); }
            break;

        case 5:
            tf = removeNoFim(l);
            if (tf == NULL) printf("Lista vazia.\n");
            else { printf("Removida: %s\n", tf->descricao); apagaElemento(tf); }
            break;

        case 6:
            if (!leInteiro("Posicao (0 a num-1): ", &posicao)) break;
            tf = removeNaPosicao(l, posicao);
            if (tf == NULL) printf("Posicao invalida ou lista vazia.\n");
            else { printf("Removida: %s\n", tf->descricao); apagaElemento(tf); }
            break;

        case 7:
            if (!leInteiro("Posicao: ", &posicao)) break;
            mostraTarefaPosicao(l, posicao);
            break;

        case 8:  mostraListaED(l);  break;
        case 9:  mostraListaDE(l);  break;

        case 10:
            apagaLDE(l);
            printf("Lista apagada.\n");
            break;

        case 0:
            printf("Encerrando...\n");
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while (op != 0);
}


/* ============================================================
 * 12) PROGRAMA PRINCIPAL
 * ============================================================ */

int main(int argc, char *argv[]) {
    if (argc > 1 && strcmp(argv[1], "menu") == 0) {
        LDE *mLista = criaListaLDE("MINHAS TAREFAS");

        if (mLista == NULL) {
            printf("Erro: falha na alocacao de memoria!\n");
            return 1;
        }

        menu(mLista);

        apagaLDE(mLista);       /* libera os nos */
        free(mLista);           /* libera a estrutura da lista */
    } else {
        testeAutomatico();
    }

    return 0;
}