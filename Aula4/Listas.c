// Exercício 1 e 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ---------- Estruturas ----------

typedef struct aluno {
    int matricula;
    char nome[50];
    struct aluno *proximo;
} Aluno;

typedef struct lse {
    Aluno *primeiro;
    int n_elementos;
} LSE;

// ---------- Funções de apoio ----------

void mostraAluno(Aluno *a) {
    printf("Matricula: %d | Nome: %s\n", a->matricula, a->nome);
}

Aluno* criaAluno(int matricula, const char *nome) {
    Aluno *novo = (Aluno *) malloc(sizeof(Aluno));
    novo->matricula = matricula;
    strcpy(novo->nome, nome);
    novo->proximo = NULL;
    return novo;
}

void apagaAluno(Aluno *a) {
    free(a);
}

int retornaQuantidade(LSE *ls) {
    return ls->n_elementos;
}

// ---------- Inserção ----------

void inserirNoInicio(LSE *ls, Aluno *novo) {
    novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->n_elementos++;
}

void inserirNoFim(LSE *ls, Aluno *novo) {
    novo->proximo = NULL;

    if (ls->primeiro == NULL) {
        ls->primeiro = novo;
    } else {
        Aluno *aux = ls->primeiro;
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    ls->n_elementos++;
}

void inserirNaPosicao(LSE *ls, Aluno *novo, int pos) {
    if (pos < 0 || pos > ls->n_elementos) return;  // posição inválida

    if (pos == 0) {
        inserirNoInicio(ls, novo);
        return;
    }
    if (pos == ls->n_elementos) {
        inserirNoFim(ls, novo);
        return;
    }

    // chegar até o nó da posição pos-1
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    novo->proximo = aux->proximo;  // salva primeiro
    aux->proximo = novo;           // liga depois
    ls->n_elementos++;
}

// ---------- Remoção ----------

Aluno* removerNoInicio(LSE *ls) {
    Aluno *aux = ls->primeiro;
    if (aux != NULL) {
        ls->primeiro = aux->proximo;
        aux->proximo = NULL;
        ls->n_elementos--;
    }
    return aux;  // pode ser NULL (lista vazia)
}

Aluno* removerNoFim(LSE *ls) {
    // Caso 1: lista vazia
    if (ls->primeiro == NULL) {
        return NULL;
    }

    // Caso 2: só um elemento
    if (ls->primeiro->proximo == NULL) {
        Aluno *removido = ls->primeiro;
        ls->primeiro = NULL;
        ls->n_elementos--;
        return removido;
    }

    // Caso 3: dois ou mais elementos
    Aluno *anterior = NULL;
    Aluno *atual = ls->primeiro;

    while (atual->proximo != NULL) {
        anterior = atual;
        atual = atual->proximo;
    }

    anterior->proximo = NULL;   // penúltimo vira o fim
    ls->n_elementos--;
    return atual;
}

Aluno* removerNaPosicao(LSE *ls, int pos) {
    if (ls->primeiro == NULL || pos < 0 || pos >= ls->n_elementos) {
        return NULL;  // lista vazia ou posição inválida
    }

    if (pos == 0) {
        return removerNoInicio(ls);
    }

    // chegar até o nó da posição pos-1
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    Aluno *removido = aux->proximo;
    aux->proximo = removido->proximo;  // "pula" o nó removido
    removido->proximo = NULL;
    ls->n_elementos--;
    return removido;  // quem chama deve dar apagaAluno() depois
}

// ---------- Exibição ----------

void mostraLista(LSE *ls) {
    Aluno *aux = ls->primeiro;
    while (aux != NULL) {
        mostraAluno(aux);
        aux = aux->proximo;
    }
    printf("Fim da Lista!\n");
}

void mostraAlunoNaPosicao(LSE *ls, int pos) {
    if (pos < 0 || pos >= ls->n_elementos) {
        printf("Posicao invalida!\n");
        return;
    }
    Aluno *aux = ls->primeiro;
    for (int i = 0; i < pos; i++) {
        aux = aux->proximo;
    }
    mostraAluno(aux);
}

// ---------- Limpeza ----------

void apagaLista(LSE *ls) {
    Aluno *aux = ls->primeiro;
    while (aux != NULL) {
        Aluno *prox = aux->proximo;  // salva antes de liberar!
        apagaAluno(aux);
        aux = prox;
    }
    ls->primeiro = NULL;
    ls->n_elementos = 0;
}

// ---------- Funções Auxiliares ----------
Aluno* lerDadosAluno() {
    Aluno *novo = (Aluno *) malloc(sizeof(Aluno));

    printf("Matricula: ");
    scanf("%d", &novo->matricula);
    printf("Nome: ");
    scanf(" %49[^\n]", novo->nome);  // lê nome com espaços

    novo->proximo = NULL;
    return novo;
}

void removeEExibe(Aluno *removido) {
    if (removido == NULL) {
        printf("Remocao falhou (lista vazia ou posicao invalida)!\n");
        return;
    }
    printf("Aluno removido: ");
    mostraAluno(removido);
    apagaAluno(removido);   // libera a memoria!
}

void inserirOrdenado(LSE *ls, Aluno *novo) {
    // caso 1: lista vazia ou novo vem antes do primeiro
    if (ls->primeiro == NULL ||
        novo->matricula < ls->primeiro->matricula) {
        inserirNoInicio(ls, novo);
        return;
    }

    // caso 2: procurar a posicao correta
    Aluno *aux = ls->primeiro;
    while (aux->proximo != NULL &&
           aux->proximo->matricula < novo->matricula) {
        aux = aux->proximo;
    }

    // inserir entre aux e aux->proximo (que pode ser NULL = fim)
    novo->proximo = aux->proximo;
    aux->proximo = novo;
    ls->n_elementos++;
}

// 3. Mostrar a turma de português em ordem invertida
// Como a LSE só tem ponteiro para frente, a forma mais simples de exibir invertido sem modificar a lista é usar recursão:
void mostraListaInvertida(Aluno *aux) {
    if (aux == NULL) return; // caso base: fim da lista
    mostraListaInvertida(aux->proximo); // vai até o fim primeiro
    mostraAluno(aux); // imprime na "volta" da recursão
}

// ---------- Função Menu ----------
int menu(LSE *ls) {
    int op, pos;

    printf("\n======= MENU =======\n");
    printf("1 - Inserir No Inicio\n");
    printf("2 - Inserir no Fim\n");
    printf("3 - Inserir na Posicao\n");
    printf("4 - Remover no Inicio\n");
    printf("5 - Remover no Fim\n");
    printf("6 - Remover na Posicao\n");
    printf("7 - Mostrar Lista\n");
    printf("8 - Inserir Ordenado\n");
    printf("0 - Sair do Programa\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &op);

    switch (op) {
        case 1:
            inserirNoInicio(ls, lerDadosAluno());
            break;
        case 2:
            inserirNoFim(ls, lerDadosAluno());
            break;
        case 3:
            printf("Informe a Posicao: ");
            scanf("%d", &pos);
            inserirNaPosicao(ls, lerDadosAluno(), pos);
            break;
        case 4:
            removeEExibe(removerNoInicio(ls));
            break;
        case 5:
            removeEExibe(removerNoFim(ls));
            break;
        case 6:
            printf("Informe a Posicao: ");
            scanf("%d", &pos);
            removeEExibe(removerNaPosicao(ls, pos));
            break;
        case 7:
            mostraLista(ls);
            break;
        case 8:
            inserirOrdenado(ls, lerDadosAluno());
            break;
        case 0:
            printf("\nFim da Execucao!\n");
            break;
        default:
            printf("Opcao invalida!\n");
    }

    return op;
}

// ---------- Main ----------
int main() {
    // 1. Turma de matemática com 10 alunos =====
    LSE matematica = {NULL, 0};
    LSE portugues  = {NULL, 0};

    for (int i = 1; i <= 10; i++) {
        char nome[20];
        sprintf(nome, "Aluno%d", i);            // gera "Aluno1", "Aluno2"...
        inserirNoFim(&matematica, criaAluno(i, nome));
    }

    printf("=== TURMA DE MATEMATICA ===\n");
    mostraLista(&matematica);

    // 2. Copia profunda para português =====
    Aluno *aux = matematica.primeiro;
    while (aux != NULL) {
        inserirNoFim(&portugues, criaAluno(aux->matricula, aux->nome));
        aux = aux->proximo;
    }

    printf("\n=== AS DUAS TURMAS ===\n");
    printf("--- Matematica ---\n");
    mostraLista(&matematica);
    printf("--- Portugues ---\n");
    mostraLista(&portugues);

    // 3. português invertido 
    printf("\n=== PORTUGUES INVERTIDO ===\n");
    mostraListaInvertida(portugues.primeiro);
    printf("Fim da Lista!\n");

    // 4. inserir nas posições 5 e 15 
    printf("\n=== INSERINDO NA POSICAO 5 E 15 ===\n");
    inserirNaPosicao(&matematica, criaAluno(99, "NovoAluno5"), 5);
    inserirNaPosicao(&matematica, criaAluno(100, "NovoAluno15"), 15);
    // pos 15 é inválida (turma tem 10 alunos), então não será inserido

    mostraLista(&matematica);

    // liberar as turmas do exercício
    apagaLista(&matematica);
    apagaLista(&portugues);

    // MENU INTERATIVO 
    printf("\n--- Agora o menu interativo (lista nova) ---\n");
    LSE ls = {NULL, 0};
    int op;
    do {
        op = menu(&ls);
    } while (op != 0);

    apagaLista(&ls);
    return 0;
}
