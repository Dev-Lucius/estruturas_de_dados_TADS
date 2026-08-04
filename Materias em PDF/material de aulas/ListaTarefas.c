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

Tarefa *criaTarefa(int id)
{
    // Cria e inicializa um nova tarefa para uma LDE
    Tarefa *nova = (Tarefa *)malloc(sizeof(Tarefa));
    printf("\nInforme a Tarefa:");
    scanf(" %[^\n]", nova->descricao);
    nova->id = id;
    printf("Informe a Prioridade:");
    scanf("%d", &nova->prioridade);
    nova->concluida = 0; // Zero não concluida e 1 concluida
    nova->anterior = NULL;
    nova->proximo = NULL;
    return nova;
}

LDE *criaListaLDE(char nome[])
{
    // Aloca memória e inicializa uma nova lista LDE
    LDE *nova = (LDE *)malloc(sizeof(LDE));
    strcpy(nova->nome, nome);
    nova->primeiro = NULL;
    nova->ultimo = NULL;
    nova->num = 0;
    return nova;
}

void mostraTarefa(Tarefa tf)
{
    // Mostra dados de uma tarefa recebida por valor
    printf("\n Tafera N° %d", tf.id);
    printf("\n\t Descricao: %s", tf.descricao);
    printf("\n\t Prioridade: %d", tf.prioridade);
    if (tf.concluida)
        printf("\n\t Tarefa já concluída.");
    else
        printf("\n\t Tarefa Não concluída.");
}

void insereInicio(LDE *lt, Tarefa *tf)
{
    // Insere um elemento no inicio da lista LDE
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
    // Insere um elemento no Fim da lista LDE
    tf->proximo = NULL;
    if (lt->primeiro == NULL)
        insereInicio(lt, tf);
    else
    {
        tf->anterior = lt->ultimo;
        lt->ultimo->proximo = tf;
        lt->ultimo = tf;
        lt->num++;
    }
}

void inserePosicao(LDE *lt, Tarefa *tf, int pos);
// Insere um elemento em uma posição determinada pelo usuário

Tarefa *removeInicio(LDE *lt)
{
    // Função para remover o primeiro elemento da LDE
    Tarefa *aux = lt->primeiro;
    if (aux != NULL)
    {
        if (aux->proximo != NULL)
        {
            lt->primeiro = aux->proximo;
            aux->proximo->anterior = NULL;
        }
        else
        {
            lt->primeiro = NULL;
            lt->ultimo = NULL;
        }
        lt->num--;
        aux->proximo = NULL;
        aux->anterior = NULL;
    }
    else
    {
        printf("\n **** Lista Vazia!!! *** \n");
    }
    return aux;
}

Tarefa *removeFim(LDE *lt);
// Função para remover o último elemento da LDE

Tarefa *removePosicao(LDE *lt, int pos);
// Remove um elemento em uma posição determinada pelo usuário

void mostraListaED(LDE lt)
{
    // Mostrar Lista da Esquerda para Direita - do primeiro ao último elemento
    printf("\n ---------- Lista de %s ------------------\n", lt.nome);
    Tarefa *aux = lt.primeiro;
    if (aux == NULL)
        printf("\n LISTA VAZIA!");
    else
    {
        printf("\n Início da Lista!");
        while (aux != NULL)
        {
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
    if (aux == NULL)
        printf("\n LISTA VAZIA!");
    else
    {
        printf("\n Início da Lista!");
        while (aux != NULL)
        {
            mostraTarefa(*aux);
            aux = aux->anterior;
        }
        printf("\n Fim da Lista DE!");
    }
}

void apagaLista(LDE *lt);
// apaga todos os elementos da lista "FREE"

void apagaElemento(Tarefa *tf);
// apaga um elemento

void menu(LDE *lt)
{
    int opcao = 0, posicao, id = 1;
    Tarefa *aux = NULL;
    do
    {
        printf("\n 1 - Insere no Inicio");
        printf("\n 2 - Insere no Fim");
        printf("\n 3 - Insere na Posição");
        printf("\n 4 - Remove no Inicio");
        printf("\n 5 - Remove no Fim");
        printf("\n 6 - Remove na Posicao");
        printf("\n 7 - Mostrar uma Tarefa Posicao");
        printf("\n 8 - Mostra Lista ED");
        printf("\n 9 - Mostra Lista DE");
        printf("\n 10 - Apaga Lista");
        printf("\n Informe uma Opcao:");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            insereInicio(lt, criaTarefa(id++));
            break;
        case 2:
            insereFim(lt, criaTarefa(id++));
            break;
        case 3:
            printf("\n Insere na Informe a Posica: ");
            // scanf("%d", &posicao);
            // inserePosicao(lt, criaTarefa(id++), posicao);
            break;
        case 4:
            aux = removeInicio(lt);
            (aux != NULL) ? mostraTarefa(*aux) : printf(" ");
            // free(aux);
            break;
        case 5:
            // aux = removeFim(lt);
            // free(aux);
            break;
        case 6:
            printf("\n Remove na Informe a Posicao: ");
            // scanf("%d", &posicao);
            //  aux = removePosicao(lt,posicao);
            // free(aux);
            break;
        case 7:
            printf("\n Informe a Posicao");
            // scanf("%d", &posicao);
            //  navegar/ a ate a posição e mostrar
            break;
        case 8:
            mostraListaED(*lt);
            break;
        case 9:
            mostraListaDE(*lt);
            break;
        case 10:
            // apagaLista(lt);
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
    menu(mLista);
}