/*
 * ============================================================
 * LISTA DUPLAMENTE ENCADEADA (LDE) EM C - PROGRAMA DE ESTUDO
 * Conteudo:
 *   - Estruturas Tarefa (no) e LDE (lista)
 *   - Insercao: inicio, fim, posicao, por prioridade
 *   - Remocao : inicio, fim, posicao, por id
 *   - Busca, inversao, exibicao (ED, DE e desenho da lista)
 *   - menu()  : menu completo para brincar com a lista
 *   - main()  : menu principal com demos guiadas e autoteste
 *
 * Compilar : gcc -Wall -Wextra -o lde_estudo lde_estudo_completo.c
 * Executar : ./lde_estudo
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/* ============================================================
 * 1) ESTRUTURAS DE DADOS
 * ============================================================ */

/* No da lista: dados + ponteiros para o anterior e o proximo.
 * (struct tarefa * e necessario aqui dentro porque o nome
 *  "Tarefa" do typedef ainda nao existe neste ponto.) */
typedef struct tarefa {
    char descricao[30];
    int id, prioridade, concluida;
    struct tarefa *anterior;
    struct tarefa *proximo;
} Tarefa;

/* Lista: primeiro, ultimo (facultativo, mas Theta(1) no fim) e n */
typedef struct LDE {
    Tarefa *primeiro;
    Tarefa *ultimo;
    char nome[30];
    int num;
} LDE;


/* ============================================================
 * 2) UTILITARIOS DE ENTRADA
 * ============================================================ */

static int entradaEncerrada = 0;   /* vira 1 se o teclado/arquivo acabar */

/* Descarta o resto da linha (no lugar de fflush(stdin), que tem
 * comportamento indefinido em C padrao). */
static void limpaBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

/* Le um inteiro. Retorna 1 se leu, 0 se invalido ou fim da entrada. */
static int leInteiro(const char *msg, int *valor) {
    printf("%s", msg);
    int r = scanf("%d", valor);

    if (r == EOF) {
        entradaEncerrada = 1;
        return 0;
    }
    limpaBuffer();
    if (r != 1) {
        printf("Entrada invalida.\n");
        return 0;
    }
    return 1;
}

/* Espera ENTER (usada nas demos passo a passo) */
static void pausa(void) {
    if (entradaEncerrada) return;

    printf("\n[ENTER para continuar]");
    fflush(stdout);

    int c;
    while ((c = getchar()) != '\n') {
        if (c == EOF) {
            entradaEncerrada = 1;
            break;
        }
    }
}


/* ============================================================
 * 3) PROTOTIPOS
 * ============================================================ */

/* criacao */
LDE    *criaListaLDE(const char nome[]);
Tarefa *criaTarefa(int id, const char descricao[], int prioridade);
Tarefa *criaTarefaInterativa(int id);

/* insercao */
void insereNoInicio(LDE *l, Tarefa *tf);
void insereNoFim(LDE *l, Tarefa *tf);
int  insereNaPosicao(LDE *l, Tarefa *tf, int p);
void inserePorPrioridade(LDE *l, Tarefa *tf);

/* remocao (retornam o no removido; quem chama da o free) */
Tarefa *removeNoInicio(LDE *l);
Tarefa *removeNoFim(LDE *l);
Tarefa *removeNaPosicao(LDE *l, int p);
Tarefa *removePorId(LDE *l, int id);

/* busca e transformacao */
Tarefa *buscaPorId(const LDE *l, int id);
void    inverteLista(LDE *l);

/* exibicao */
void mostraTarefa(const Tarefa *t);
void mostraListaED(const LDE *l);
void mostraListaDE(const LDE *l);
void mostraTarefaPosicao(LDE *l, int posicao);
void desenhaLista(const LDE *l);

/* memoria e verificacao */
void apagaElemento(Tarefa *tf);
void apagaLDE(LDE *l);
int  verificaLista(const LDE *l);

/* programa */
void menu(LDE *l);
static void demoPassoAPasso(void);
static void demoPlaylist(void);
static void demoFilaPrioridade(void);
static void demoInversao(void);
static void autoteste(void);
static void mostraDesafios(void);


/* ============================================================
 * 4) CRIACAO
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

/* Cria uma tarefa a partir de parametros */
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

/* Cria uma tarefa lendo os dados do teclado */
Tarefa *criaTarefaInterativa(int id) {
    int prioridade;
    char descricao[30];

    if (!leInteiro("Informe sua Prioridade (1 = mais urgente): ", &prioridade)) {
        return NULL;
    }

    printf("Informe a Descricao: ");
    int r = scanf("%29[^\n]", descricao);
    if (r == EOF) {
        entradaEncerrada = 1;
        return NULL;
    }
    limpaBuffer();
    if (r != 1) {
        printf("Descricao invalida.\n");
        return NULL;
    }

    Tarefa *nova = criaTarefa(id, descricao, prioridade);
    if (nova != NULL) {
        printf("Tarefa criada com sucesso\n");
    }
    return nova;
}


/* ============================================================
 * 5) AUXILIARES INTERNAS (o "coracao" da LDE)
 * ============================================================ */

/*
 * Retorna o no da posicao p (0 a num-1) ou NULL se invalida.
 * VANTAGEM DA LISTA DUPLA: se p esta na primeira metade, parte do
 * primeiro; senao, parte do ultimo e VOLTA. No pior caso, anda
 * num/2 nos (numa LSE seriam sempre ate num-1).
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

/*
 * Insere tf imediatamente ANTES de 'atual' (que deve estar na lista).
 * Quatro ponteiros a acertar:
 *    tf->anterior, tf->proximo, vizinho->proximo, atual->anterior
 */
static void insereAntesDe(LDE *l, Tarefa *tf, Tarefa *atual) {
    tf->anterior = atual->anterior;
    tf->proximo = atual;

    if (atual->anterior != NULL) {
        atual->anterior->proximo = tf;      /* vizinho da esquerda */
    } else {
        l->primeiro = tf;                   /* atual era o primeiro */
    }

    atual->anterior = tf;
    l->num++;
}

/*
 * Desconecta 'no' da lista (que deve estar nela) e o devolve.
 * A LDE nao precisa de ponteiro "anterior" auxiliar: o proprio no
 * ja sabe quem sao os vizinhos. Casos:
 *    - tem anterior?  vizinho->proximo pula o no; senao era o primeiro
 *    - tem proximo?   vizinho->anterior pula o no; senao era o ultimo
 */
static Tarefa *desconecta(LDE *l, Tarefa *no) {
    if (no->anterior != NULL) {
        no->anterior->proximo = no->proximo;
    } else {
        l->primeiro = no->proximo;
    }

    if (no->proximo != NULL) {
        no->proximo->anterior = no->anterior;
    } else {
        l->ultimo = no->anterior;
    }

    no->anterior = NULL;
    no->proximo = NULL;
    l->num--;

    return no;
}


/* ============================================================
 * 6) INSERCAO
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
    } else {                                /* Theta(1) graças ao *ultimo */
        tf->anterior = l->ultimo;
        l->ultimo->proximo = tf;
        l->ultimo = tf;
        l->num++;
    }
}

/* Insere tf na posicao p (0 a num). Retorna 1 se inseriu, 0 se invalida. */
int insereNaPosicao(LDE *l, Tarefa *tf, int p) {
    if (p < 0 || p > l->num) {
        return 0;
    }

    if (p == 0) {
        insereNoInicio(l, tf);
    } else if (p == l->num) {
        insereNoFim(l, tf);
    } else {
        insereAntesDe(l, tf, buscaPosicao(l, p));
    }

    return 1;
}

/*
 * Insercao ORDENADA por prioridade (menor numero = mais urgente).
 * Para prioridades iguais, o novo fica DEPOIS dos existentes
 * (ordem de chegada preservada - insercao estavel).
 */
void inserePorPrioridade(LDE *l, Tarefa *tf) {
    Tarefa *atual = l->primeiro;

    while (atual != NULL && atual->prioridade <= tf->prioridade) {
        atual = atual->proximo;
    }

    if (atual == NULL) {
        insereNoFim(l, tf);                 /* nenhum e maior: vai pro fim */
    } else {
        insereAntesDe(l, tf, atual);        /* entra antes do 1o maior */
    }
}


/* ============================================================
 * 7) REMOCAO
 * ============================================================ */

Tarefa *removeNoInicio(LDE *l) {
    return (l->primeiro == NULL) ? NULL : desconecta(l, l->primeiro);
}

Tarefa *removeNoFim(LDE *l) {
    return (l->ultimo == NULL) ? NULL : desconecta(l, l->ultimo);
}

Tarefa *removeNaPosicao(LDE *l, int p) {
    Tarefa *no = buscaPosicao(l, p);
    return (no == NULL) ? NULL : desconecta(l, no);
}

Tarefa *removePorId(LDE *l, int id) {
    Tarefa *no = buscaPorId(l, id);
    return (no == NULL) ? NULL : desconecta(l, no);
}


/* ============================================================
 * 8) BUSCA E INVERSAO
 * ============================================================ */

/* Busca linear pelo id. Retorna o no ou NULL. */
Tarefa *buscaPorId(const LDE *l, int id) {
    for (Tarefa *t = l->primeiro; t != NULL; t = t->proximo) {
        if (t->id == id) {
            return t;
        }
    }
    return NULL;
}

/*
 * Inverte a lista IN-LOCO, sem alocar nada: em cada no troca
 * anterior <-> proximo; no fim troca primeiro <-> ultimo.
 * Classico de entrevistas - so e simples assim numa LDE.
 */
void inverteLista(LDE *l) {
    Tarefa *aux = l->primeiro;

    while (aux != NULL) {
        Tarefa *prox = aux->proximo;        /* guarda antes de trocar */
        aux->proximo = aux->anterior;
        aux->anterior = prox;
        aux = prox;
    }

    Tarefa *tmp = l->primeiro;
    l->primeiro = l->ultimo;
    l->ultimo = tmp;
}


/* ============================================================
 * 9) EXIBICAO
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
        printf("Posicao %d invalida (lista tem %d elemento(s)).\n",
               posicao, l->num);
    } else {
        mostraTarefa(t);
    }
}

/*
 * Desenho em ASCII da estrutura, ideal para acompanhar os ponteiros:
 *
 *   NULL <- [E0| 1:Acordar] <-> [E1| 2:Cafe] -> NULL
 *   primeiro = 1 | ultimo = 2 | num = 2
 */
void desenhaLista(const LDE *l) {
    printf("\n  ");

    if (l->primeiro == NULL) {
        printf("NULL   (lista vazia)\n");
    } else {
        printf("NULL <- ");
        int i = 0;
        for (const Tarefa *t = l->primeiro; t != NULL; t = t->proximo, i++) {
            printf("[E%d| %d:%s]", i, t->id, t->descricao);
            if (t->proximo != NULL) printf(" <-> ");
        }
        printf(" -> NULL\n");
    }

    printf("  primeiro = ");
    if (l->primeiro) printf("%d", l->primeiro->id); else printf("NULL");
    printf(" | ultimo = ");
    if (l->ultimo) printf("%d", l->ultimo->id); else printf("NULL");
    printf(" | num = %d | consistencia: %s\n",
           l->num, verificaLista(l) ? "OK" : "ERRO");
}


/* ============================================================
 * 10) LIBERACAO DE MEMORIA E VERIFICACAO
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

/*
 * Confere os invariantes da LDE: primeiro/ultimo, elos nos dois
 * sentidos e contador. Retorna 1 se tudo esta correto.
 */
int verificaLista(const LDE *l) {
    if (l->num == 0) {
        return l->primeiro == NULL && l->ultimo == NULL;
    }

    if (l->primeiro == NULL || l->ultimo == NULL) return 0;
    if (l->primeiro->anterior != NULL)            return 0;
    if (l->ultimo->proximo != NULL)               return 0;

    int cont = 0;
    const Tarefa *ant = NULL;
    for (const Tarefa *t = l->primeiro; t != NULL; t = t->proximo) {
        if (t->anterior != ant) return 0;
        ant = t;
        if (++cont > l->num)    return 0;   /* protege de laco infinito */
    }
    if (cont != l->num || ant != l->ultimo) return 0;

    cont = 0;
    for (const Tarefa *t = l->ultimo; t != NULL; t = t->anterior) {
        if (++cont > l->num) return 0;
    }

    return cont == l->num;
}


/* ============================================================
 * 11) MENU DA LISTA (modo livre)
 * ============================================================ */

void menu(LDE *l) {
    static int id = 1;              /* persiste entre chamadas do menu */
    int op = -1, posicao;
    Tarefa *tf;

    do {
        printf("\n\n===== %s (%d tarefa(s)) =====", l->nome, l->num);
        printf("\nInforme uma Opcao:");
        printf("\n -- 1  - Inserir Tarefa no Inicio");
        printf("\n -- 2  - Inserir Tarefa no Fim");
        printf("\n -- 3  - Inserir Tarefa na Posicao");
        printf("\n -- 4  - Remover Tarefa no Inicio");
        printf("\n -- 5  - Remover Tarefa no Fim");
        printf("\n -- 6  - Remover Tarefa na Posicao");
        printf("\n -- 7  - Mostrar uma Tarefa da Posicao");
        printf("\n -- 8  - Mostrar a Lista ED (esquerda -> direita)");
        printf("\n -- 9  - Mostrar a Lista DE (direita -> esquerda)");
        printf("\n -- 10 - Apagar Lista");
        printf("\n -- 11 - Desenhar a Lista (ponteiros)");
        printf("\n -- 12 - Inverter a Lista");
        printf("\n -- 13 - Buscar Tarefa por id");
        printf("\n -- 14 - Inserir Tarefa por Prioridade (ordenado)");
        printf("\n -- 15 - Marcar Tarefa como concluida (por id)");
        printf("\n -- 0  - Voltar\n");

        if (!leInteiro("\nInforme sua Opcao: ", &op)) {
            op = -1;
            continue;               /* volta ao teste do while */
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
            if (tf != NULL) { insereNaPosicao(l, tf, posicao); id++; }
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

        case 11: desenhaLista(l);   break;

        case 12:
            inverteLista(l);
            printf("Lista invertida.\n");
            desenhaLista(l);
            break;

        case 13: {
            int busca;
            if (!leInteiro("id procurado: ", &busca)) break;
            tf = buscaPorId(l, busca);
            if (tf == NULL) printf("id %d nao encontrado.\n", busca);
            else mostraTarefa(tf);
            break;
        }

        case 14:
            tf = criaTarefaInterativa(id);
            if (tf != NULL) { inserePorPrioridade(l, tf); id++; }
            break;

        case 15: {
            int busca;
            if (!leInteiro("id da tarefa concluida: ", &busca)) break;
            tf = buscaPorId(l, busca);
            if (tf == NULL) printf("id %d nao encontrado.\n", busca);
            else { tf->concluida = 1; printf("Tarefa %d concluida.\n", busca); }
            break;
        }

        case 0:
            break;

        default:
            printf("Opcao invalida.\n");
        }
    } while (op != 0 && !entradaEncerrada);
}


/* ============================================================
 * 12) DEMO 1: OPERACOES PASSO A PASSO (com desenho)
 * ============================================================ */

static void passo(const char *texto, LDE *l) {
    printf("\n>>> %s", texto);
    desenhaLista(l);
    pausa();
}

static void demoPassoAPasso(void) {
    printf("\n########## DEMO 1: OPERACOES PASSO A PASSO ##########\n");
    printf("Acompanhe como primeiro, ultimo e os elos mudam a cada operacao.\n");

    LDE *l = criaListaLDE("DEMO 1");
    Tarefa *t;
    if (l == NULL) return;

    passo("Lista recem-criada (vazia): primeiro = ultimo = NULL", l);

    insereNoInicio(l, criaTarefa(1, "Acordar", 1));
    passo("insereNoInicio(Acordar): lista vazia, o no vira primeiro E ultimo", l);

    insereNoFim(l, criaTarefa(3, "Ir_trabalho", 3));
    passo("insereNoFim(Ir_trabalho): Theta(1) usando *ultimo", l);

    insereNaPosicao(l, criaTarefa(2, "Cafe", 2), 1);
    passo("insereNaPosicao(Cafe, 1): entra ENTRE os dois, 4 ponteiros acertados", l);

    insereNoInicio(l, criaTarefa(0, "Despertador", 1));
    passo("insereNoInicio(Despertador): novo primeiro; o antigo aponta de volta", l);

    t = removeNaPosicao(l, 2);
    printf("\n(removido: %s)", t->descricao);
    apagaElemento(t);
    passo("removeNaPosicao(2): vizinhos se religam pulando o no removido", l);

    t = removeNoInicio(l);
    printf("\n(removido: %s)", t->descricao);
    apagaElemento(t);
    passo("removeNoInicio(): o segundo vira primeiro e seu anterior = NULL", l);

    t = removeNoFim(l);
    printf("\n(removido: %s)", t->descricao);
    apagaElemento(t);
    passo("removeNoFim(): o penultimo vira ultimo e seu proximo = NULL", l);

    t = removeNoFim(l);
    printf("\n(removido: %s)", t->descricao);
    apagaElemento(t);
    passo("removeNoFim() no unico elemento: a lista volta a ficar vazia", l);

    apagaLDE(l);
    free(l);
}


/* ============================================================
 * 13) DEMO 2: PLAYLIST (navegacao nos dois sentidos)
 * ============================================================ */
 
static void demoPlaylist(void) {
    printf("\n########## DEMO 2: PLAYLIST ##########\n");
    printf("Ir para a proxima E voltar para a anterior em Theta(1):\n");
    printf("e exatamente para isso que a LDE serve. (Numa LSE, voltar\n");
    printf("exigiria percorrer a lista desde o inicio.)\n");

    const char *musicas[] = {"Manha_de_Sol", "Cafe_Forte", "Estrada_Longa",
                             "Noite_Estrelada", "Chuva_de_Verao"};
    const int n = (int) (sizeof(musicas) / sizeof(musicas[0]));

    LDE *pl = criaListaLDE("PLAYLIST");
    if (pl == NULL) return;

    for (int i = 0; i < n; i++) {
        insereNoFim(pl, criaTarefa(i + 1, musicas[i], 3 + i % 3));
    }

    desenhaLista(pl);

    Tarefa *atual = pl->primeiro;      /* "cursor" que anda pela lista */
    char cmd;

    while (!entradaEncerrada) {
        printf("\n>> Tocando: [%d] %s (%d min)\n",
               atual->id, atual->descricao, atual->prioridade);
        printf("   anterior: %s | proxima: %s\n",
               atual->anterior ? atual->anterior->descricao : "(inicio)",
               atual->proximo  ? atual->proximo->descricao  : "(fim)");
        printf("Comando: (n) proxima  (p) anterior  (q) sair: ");

        if (scanf(" %c", &cmd) != 1) {
            entradaEncerrada = 1;
            break;
        }
        limpaBuffer();

        if (cmd == 'n') {
            if (atual->proximo != NULL) atual = atual->proximo;
            else printf("   Ja e a ultima faixa!\n");
        } else if (cmd == 'p') {
            if (atual->anterior != NULL) atual = atual->anterior;
            else printf("   Ja e a primeira faixa!\n");
        } else if (cmd == 'q') {
            break;
        } else {
            printf("   Comando invalido.\n");
        }
    }

    apagaLDE(pl);
    free(pl);
}


/* ============================================================
 * 14) DEMO 3: FILA DE ATENDIMENTO POR PRIORIDADE
 * ============================================================ */

static void demoFilaPrioridade(void) {
    printf("\n########## DEMO 3: FILA POR PRIORIDADE ##########\n");
    printf("Chegam tarefas fora de ordem; inserePorPrioridade mantem a lista\n");
    printf("ordenada (1 = mais urgente). Igualdade: ordem de chegada.\n");

    struct { const char *desc; int prio; } chegadas[] = {
        {"Reuniao", 3}, {"Servidor_caiu", 1}, {"Relatorio", 4},
        {"Email", 5},   {"Bug_critico", 1},   {"Code_review", 3}
    };
    const int n = (int) (sizeof(chegadas) / sizeof(chegadas[0]));

    LDE *fila = criaListaLDE("FILA");
    if (fila == NULL) return;

    for (int i = 0; i < n; i++) {
        printf("\nChegou: %-14s (prioridade %d)", chegadas[i].desc, chegadas[i].prio);
        inserePorPrioridade(fila, criaTarefa(i + 1, chegadas[i].desc, chegadas[i].prio));
        desenhaLista(fila);
    }
    pausa();

    Tarefa *t = removeNoFim(fila);
    printf("\nDescartando a MENOS urgente (removeNoFim): %s\n", t->descricao);
    apagaElemento(t);

    printf("\nAtendendo em ordem de urgencia (removeNoInicio):\n");
    int ordem = 1;
    while ((t = removeNoInicio(fila)) != NULL) {
        printf("  %d. %-14s (prioridade %d)\n", ordem++, t->descricao, t->prioridade);
        apagaElemento(t);
    }

    printf("\nFila vazia? %s\n", fila->num == 0 ? "sim" : "nao");
    apagaLDE(fila);
    free(fila);
}


/* ============================================================
 * 15) DEMO 4: INVERSAO DA LISTA
 * ============================================================ */

static void demoInversao(void) {
    printf("\n########## DEMO 4: INVERTER A LISTA ##########\n");
    printf("Sem alocar memoria: em cada no troca anterior <-> proximo.\n");

    LDE *l = criaListaLDE("INVERSAO");
    if (l == NULL) return;

    const char *nomes[] = {"A", "B", "C", "D", "E"};
    for (int i = 0; i < 5; i++) {
        insereNoFim(l, criaTarefa(i + 1, nomes[i], 1));
    }

    printf("\nOriginal:");
    desenhaLista(l);

    inverteLista(l);
    printf("\nApos inverteLista():");
    desenhaLista(l);

    mostraListaED(l);

    inverteLista(l);
    printf("\nInvertendo de novo, voltamos ao original:");
    desenhaLista(l);

    apagaLDE(l);
    free(l);
}


/* ============================================================
 * 16) AUTOTESTE
 * ============================================================ */

static int testesTotal = 0, testesOk = 0;

#define CHECK(cond) do {                                             \
    testesTotal++;                                                   \
    if (cond) testesOk++;                                            \
    else printf("  FALHOU: %s (linha %d)\n", #cond, __LINE__);       \
} while (0)

/* A lista tem exatamente estes ids, na ordem, e esta consistente? */
static int idsSao(const LDE *l, const int esperado[], int n) {
    if (l->num != n || !verificaLista(l)) return 0;

    const Tarefa *t = l->primeiro;
    for (int i = 0; i < n; i++, t = t->proximo) {
        if (t->id != esperado[i]) return 0;
    }
    return 1;
}

static void autoteste(void) {
    printf("\n########## AUTOTESTE ##########\n");
    testesTotal = testesOk = 0;

    LDE *l = criaListaLDE("TESTE");
    Tarefa *t;
    if (l == NULL) return;

    /* lista vazia */
    CHECK(idsSao(l, NULL, 0));
    CHECK(removeNoInicio(l) == NULL);
    CHECK(removeNoFim(l) == NULL);
    CHECK(removeNaPosicao(l, 0) == NULL);

    /* um unico elemento: primeiro == ultimo */
    insereNoFim(l, criaTarefa(1, "A", 1));
    CHECK(idsSao(l, (int[]){1}, 1));
    CHECK(l->primeiro == l->ultimo);

    /* inicio, fim e meio */
    insereNoInicio(l, criaTarefa(0, "B", 1));
    insereNoFim(l, criaTarefa(3, "C", 1));
    CHECK(idsSao(l, (int[]){0, 1, 3}, 3));
    CHECK(insereNaPosicao(l, criaTarefa(2, "D", 1), 2));
    CHECK(idsSao(l, (int[]){0, 1, 2, 3}, 4));

    /* posicoes invalidas */
    t = criaTarefa(9, "X", 1);
    CHECK(!insereNaPosicao(l, t, -1));
    CHECK(!insereNaPosicao(l, t, 99));
    apagaElemento(t);
    CHECK(removeNaPosicao(l, -1) == NULL);
    CHECK(removeNaPosicao(l, 4) == NULL);

    /* busca por id */
    CHECK(buscaPorId(l, 2) != NULL && buscaPorId(l, 2)->id == 2);
    CHECK(buscaPorId(l, 42) == NULL);

    /* inversao (duas vezes = identidade) */
    inverteLista(l);
    CHECK(idsSao(l, (int[]){3, 2, 1, 0}, 4));
    inverteLista(l);
    CHECK(idsSao(l, (int[]){0, 1, 2, 3}, 4));

    /* remocoes */
    t = removeNaPosicao(l, 1);
    CHECK(t != NULL && t->id == 1 && t->anterior == NULL && t->proximo == NULL);
    apagaElemento(t);
    CHECK(idsSao(l, (int[]){0, 2, 3}, 3));

    t = removeNoInicio(l);  CHECK(t->id == 0);  apagaElemento(t);
    t = removeNoFim(l);     CHECK(t->id == 3);  apagaElemento(t);
    CHECK(idsSao(l, (int[]){2}, 1));

    t = removePorId(l, 2);  CHECK(t != NULL && t->id == 2);  apagaElemento(t);
    CHECK(idsSao(l, NULL, 0));
    CHECK(removePorId(l, 2) == NULL);

    /* insercao por prioridade (estavel) */
    inserePorPrioridade(l, criaTarefa(1, "p3", 3));
    inserePorPrioridade(l, criaTarefa(2, "p1", 1));
    inserePorPrioridade(l, criaTarefa(3, "p5", 5));
    inserePorPrioridade(l, criaTarefa(4, "p3b", 3));
    inserePorPrioridade(l, criaTarefa(5, "p1b", 1));
    CHECK(idsSao(l, (int[]){2, 5, 1, 4, 3}, 5));

    /* apagar deixa a lista reutilizavel */
    apagaLDE(l);
    CHECK(idsSao(l, NULL, 0));
    insereNoFim(l, criaTarefa(1, "Z", 1));
    CHECK(idsSao(l, (int[]){1}, 1));

    apagaLDE(l);
    free(l);

    printf("Resultado: %d de %d verificacoes passaram %s\n",
           testesOk, testesTotal, testesOk == testesTotal ? "(tudo certo!)" : "(HA FALHAS)");
}


/* ============================================================
 * 17) DESAFIOS PARA PRATICAR
 * ============================================================ */

static void mostraDesafios(void) {
    printf("\n########## DESAFIOS PARA VOCE IMPLEMENTAR ##########\n");
    printf("Facil:\n");
    printf("  1. contaConcluidas(l): quantas tarefas tem concluida == 1?\n");
    printf("  2. mostraTarefaPosicao usando so *proximo (sem buscaPosicao).\n");
    printf("Medio:\n");
    printf("  3. removeDuplicados(l): tire nos com o mesmo id, mantendo o 1o.\n");
    printf("  4. moveParaInicio(l, id): desconecte e reinsira no inicio.\n");
    printf("  5. troca(l, i, j): troque de lugar as tarefas das posicoes i e j.\n");
    printf("Dificil:\n");
    printf("  6. concatena(a, b): anexe a lista b ao fim de a em Theta(1).\n");
    printf("  7. ordenaPorPrioridade(l): ordene uma lista ja existente\n");
    printf("     (dica: insertion sort reaproveitando desconecta/insereAntesDe).\n");
    printf("  8. Lista circular: faca ultimo->proximo = primeiro e\n");
    printf("     primeiro->anterior = ultimo. O que muda nas condicoes de parada?\n");
    printf("\nDica: apos cada desafio, use verificaLista() e o Valgrind/ASan.\n");
}


/* ============================================================
 * 18) PROGRAMA PRINCIPAL
 * ============================================================ */

int main(void) {
    LDE *mLista = criaListaLDE("MINHAS TAREFAS");
    int op = -1;

    if (mLista == NULL) {
        printf("Erro: falha na alocacao de memoria!\n");
        return 1;
    }

    do {
        printf("\n\n============ ESTUDO: LISTA DUPLAMENTE ENCADEADA ============");
        printf("\n -- 1 - Modo livre (menu completo da lista)");
        printf("\n -- 2 - Demo 1: operacoes passo a passo (com desenho)");
        printf("\n -- 3 - Demo 2: playlist (navegar nos dois sentidos)");
        printf("\n -- 4 - Demo 3: fila de atendimento por prioridade");
        printf("\n -- 5 - Demo 4: inverter a lista");
        printf("\n -- 6 - Autoteste (verifica se as funcoes estao corretas)");
        printf("\n -- 7 - Desafios para praticar");
        printf("\n -- 0 - Sair\n");

        if (!leInteiro("\nInforme sua Opcao: ", &op)) {
            op = -1;
            continue;
        }

        switch (op) {
        case 1: menu(mLista);         break;
        case 2: demoPassoAPasso();    break;
        case 3: demoPlaylist();       break;
        case 4: demoFilaPrioridade(); break;
        case 5: demoInversao();       break;
        case 6: autoteste();          break;
        case 7: mostraDesafios();     break;
        case 0: printf("Encerrando...\n"); break;
        default: printf("Opcao invalida.\n");
        }
    } while (op != 0 && !entradaEncerrada);

    /* Liberacao final: nos e depois a estrutura da lista */
    apagaLDE(mLista);
    free(mLista);
    printf("Memoria liberada. Fim do programa.\n");

    return 0;
}