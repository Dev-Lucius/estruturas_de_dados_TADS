#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa
{
    char descricao[30];
    int id, prioridade, concluida;
    struct tarefa *anterior;
    struct tarefa *proximo;
} Tarefa;

typedef struct LDE
{
    Tarefa *primeiro;
    Tarefa *ultimo; // facultativo
    char nome[30];
    int num;
} LDE;

static void limpaBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

Tarefa *criaTarefa(int id)
{
    // Cria e inicializa um nova tarefa para uma LDE
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    if (nova == NULL) // CORRIGIDO: verifica o malloc
        return NULL;

    printf("\nInforme a Tarefa:");
    if (scanf(" %29[^\n]", nova->descricao) != 1)
    {
        free(nova);
        return NULL;
    }
    limpaBuffer(); 

    nova->id = id;
    printf("Informe a Prioridade:");
    if (scanf("%d", &nova->prioridade) != 1) 
    {
        limpaBuffer();
        printf("\nPrioridade invalida! Tarefa descartada.");
        free(nova);
        return NULL;
    }
    nova->concluida = 0; // Zero não concluida e 1 concluida
    nova->anterior = NULL;
    nova->proximo = NULL;
    return nova;
}

LDE *criaListaLDE(char nome[])
{
    // Aloca memória e inicializa uma nova lista LDE
    LDE *nova = (LDE *)malloc(sizeof(LDE));
    if (nova == NULL) // CORRIGIDO
        return NULL;
    snprintf(nova->nome, sizeof(nova->nome), "%s", nome);
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->num = 0;
    return nova;
}

void insereInicio(LDE *lt, Tarefa *tf)
{
    // Insere um elemento no inicio da lista LDE
    printf("\nInserindo no Inicio");
    tf->anterior = NULL;
    if (lt->primeiro == NULL)
    {
        tf->proximo = NULL;
        lt->ultimo = tf;
    }
    else
    {
        tf->proximo = lt->primeiro;
        lt->primeiro->anterior = tf;
    }
    lt->primeiro = tf;
    lt->num++;
}

void insereFim(LDE *lt, Tarefa *tf)
{
    tf->proximo = NULL;

    printf("\nInserindo no Fim");
    if (lt->primeiro == NULL)
    {
        insereInicio(lt, tf);
    }
    else
    {
        tf->anterior = lt->ultimo;
        lt->ultimo->proximo = tf;
        lt->ultimo = tf;
        lt->num++;
    }
}

int inserePosicao(LDE *lt, Tarefa *tf, int pos)
{
    // Insere um elemento em uma posição determinada pelo usuário
    if (pos < 0 || pos > lt->num)
        return 0;

    if (pos == 0)
    {
        insereInicio(lt, tf);
        return 1;
    }

    if (pos == lt->num)
    {
        insereFim(lt, tf);
        return 1;
    }

    Tarefa *atual = lt->primeiro;
    for (int i = 0; i < pos; i++)
    {
        atual = atual->proximo;
    }

    tf->anterior = atual->anterior;
    tf->proximo = atual;
    atual->anterior->proximo = tf;
    atual->anterior = tf;
    lt->num++;
    return 1;
}

Tarefa *removeInicio(LDE *lt)
{
    // Função para remover o primeiro elemento da LDE
    if (lt->primeiro == NULL)
        return NULL;

    Tarefa *removido = lt->primeiro;
    lt->primeiro = removido->proximo;

    if (lt->primeiro == NULL)
    {
        lt->ultimo = NULL; 
    }
    else
    {
        lt->primeiro->anterior = NULL;
    }

    removido->proximo = NULL;
    lt->num--;
    return removido;
}

Tarefa *removeFim(LDE *lt)
{
    // Função para remover o último elemento da LDE
    if (lt->ultimo == NULL)
        return NULL;

    Tarefa *removido = lt->ultimo;
    lt->ultimo = removido->anterior;

    if (lt->ultimo == NULL)
    {
        lt->primeiro = NULL; "
    }
    else
    {
        lt->ultimo->proximo = NULL;
    }

    removido->anterior = NULL;
    lt->num--;
    return removido;
}

Tarefa *removePosicao(LDE *lt, int pos)
{
    // Remove um elemento em uma posição determinada pelo usuário
    if (pos < 0 || pos >= lt->num)
        return NULL;
    if (pos == 0)
        return removeInicio(lt);
    if (pos == lt->num - 1)
        return removeFim(lt);

    Tarefa *aux = lt->primeiro;
    for (int i = 0; i < pos; i++)
    {
        aux = aux->proximo;
    }

    aux->anterior->proximo = aux->proximo;
    aux->proximo->anterior = aux->anterior;

    aux->anterior = NULL;
    aux->proximo = NULL;

    lt->num--;
    return aux;
}

void mostraTarefa(Tarefa tf)
{
    // Mostra dados de uma tarefa recebida por valor
    printf("\n\t Tarefa N° %d", tf.id); 
    printf("\n\t Descricao: %s", tf.descricao);
    printf("\n\t Prioridade: %d", tf.prioridade);
    if (tf.concluida)
        printf("\n\t Tarefa já concluída.");
    else
        printf("\n\t Tarefa Não concluída.");
}

void mostraTarefaPosicao(LDE *lt, int pos)
{
    if (pos < 0 || pos >= lt->num)
    {
        printf("\n Posicao invalida!");
        return;
    }
    Tarefa *aux = lt->primeiro;
    for (int i = 0; i < pos; i++)
    {
        aux = aux->proximo;
    }
    mostraTarefa(*aux);
}

void mostraListaED(LDE lt)
{
    // Mostrar Lista da Esquerda para Direita - do primeiro ao último elemento
    printf("\n ---------- Lista de %s ------------------\n", lt.nome);
    Tarefa *aux = lt.primeiro;
    int ct = 0;
    if (aux == NULL)
        printf("\n LISTA VAZIA!");
    else
    {
        printf("\n Início da Lista!");
        while (aux != NULL)
        {
            printf("\n Elemento N° %d", ct++);
            mostraTarefa(*aux);
            aux = aux->proximo;
        }
        printf("\n Fim da Lista ED!");
    }
}

void mostraListaDE(LDE lt)
{
    // Mostrar Lista da Direita para Esquerda - do elemento último ao primeiro elemento
    printf("\n ---------- Lista de %s ------------------\n", lt.nome);
    Tarefa *aux = lt.ultimo;
    int ct = lt.num - 1;
    if (aux == NULL)
        printf("\n LISTA VAZIA!");
    else
    {
        printf("\n Início da Lista!");
        while (aux != NULL)
        {
            printf("\n Elemento N° %d", ct--); 
            mostraTarefa(*aux);
            aux = aux->anterior;
        }
        printf("\n Fim da Lista DE!");
    }
}

void apagaElemento(Tarefa *tf)
{
    // apaga um elemento
    if (tf != NULL)
    {
        free(tf);
    }
}

void apagaLista(LDE *lt)
{
    Tarefa *atual = lt->primeiro;

    while (atual != NULL)
    {
        Tarefa *proximo = atual->proximo;
        apagaElemento(atual);
        atual = proximo;
    }

    lt->primeiro = NULL;
    lt->ultimo = NULL; // CORRIGIDO: faltava zerar o ultimo
    lt->num = 0;
}

static int lePosicao(const char *msg, int max, int *pos)
{
    printf("%s", msg);
    if (scanf("%d", pos) != 1)
    {
        limpaBuffer();
        printf("\n Entrada invalida!");
        return 0;
    }
    if (*pos < 0 || *pos > max)
    {
        printf("\n Posicao invalida!");
        return 0;
    }
    return 1;
}

void menu(LDE *lt)
{
    int opcao = 0, posicao, id = 1;
    Tarefa *aux = NULL;
    do
    {
        printf("\n\n 1 - Insere no Inicio");
        printf("\n 2 - Insere no Fim");
        printf("\n 3 - Insere na Posição");
        printf("\n 4 - Remove no Inicio");
        printf("\n 5 - Remove no Fim");
        printf("\n 6 - Remove na Posicao");
        printf("\n 7 - Mostrar uma Tarefa Posicao");
        printf("\n 8 - Mostra Lista ED");
        printf("\n 9 - Mostra Lista DE");
        printf("\n 10 - Apaga Lista");
        printf("\n 0 - Sair");
        printf("\n Informe uma Opcao:");

        int r = scanf("%d", &opcao);
        if (r == EOF)
        {
            opcao = 0;
        }
        else if (r != 1)
        {
            limpaBuffer();
            printf("\n Entrada invalida!");
            opcao = -1;
            continue;
        }

        switch (opcao)
        {
        case 1:
            aux = criaTarefa(id);
            if (aux != NULL) 
            {
                insereInicio(lt, aux);
                id++;
            }
            break;
        case 2:
            aux = criaTarefa(id);
            if (aux != NULL)
            {
                insereFim(lt, aux);
                id++;
            }
            break;
        case 3:
            if (lePosicao("\n Informe a Posicao: ", lt->num, &posicao))
            {
                aux = criaTarefa(id);
                if (aux != NULL)
                {
                    inserePosicao(lt, aux, posicao);
                    id++;
                }
            }
            break;
        case 4:
            aux = removeInicio(lt);
            if (aux != NULL)
            {
                printf("\n Tarefa removida:");
                mostraTarefa(*aux);
                apagaElemento(aux);
            }
            else
                printf("\n Lista vazia!");
            break;
        case 5:
            aux = removeFim(lt);
            if (aux != NULL)
            {
                printf("\n Tarefa removida:");
                mostraTarefa(*aux);
                apagaElemento(aux);
            }
            else
                printf("\n Lista vazia!");
            break;
        case 6:
            if (lePosicao("\n Remove na Informe a Posicao: ", lt->num - 1, &posicao))
            {
                aux = removePosicao(lt, posicao);
                if (aux != NULL)
                {
                    printf("\n Tarefa removida:");
                    mostraTarefa(*aux);
                    apagaElemento(aux);
                }
                else
                    printf("\n Lista vazia!");
            }
            break;
        case 7:
            if (lePosicao("\n Informe a Posicao: ", lt->num - 1, &posicao))
                mostraTarefaPosicao(lt, posicao);
            break;
        case 8:
            mostraListaED(*lt);
            break;
        case 9:
            mostraListaDE(*lt);
            break;
        case 10:
            apagaLista(lt);
            printf("\n Lista apagada.");
            break;
        case 0: 
            printf("\n Saindo...");
            break;
        default:
            printf("\n Opção Invalida!!");
        }
    } while (opcao != 0);
}

int main()
{
    LDE *mLista;
    mLista = criaListaLDE("MINHAS TAREFAS");
    if (mLista == NULL)
        return 1;

    menu(mLista);
    apagaLista(mLista);
    free(mLista);
    printf("\n Memoria liberada. Fim do programa.\n");
    return 0;
}
