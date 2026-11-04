#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct livro{ 
    // dados do elemento livro
    char autor[20];
    char titulo[20];
    int ano;
    int id;
    struct livro *proximo;
} Livro;

typedef struct pilha{ 
    // atributos de pilha
    Livro *topo;
    int qtd;
} Pilha;

Pilha *criaPilha(){
    // cria estrutura para pilha
    Pilha *p = (Pilha *)malloc(sizeof(Pilha));
    p->topo = NULL;
    p->qtd = 0;
    return p;
}

Livro *criaElementoPilhaLivro(int id, int ano, char at[], char tit[]){
    // cria um elemento de pilha
    Livro *lv = (Livro *)malloc(sizeof(Livro));
    lv->proximo = NULL;
    lv->ano = ano;
    strcpy(lv->autor, at);
    strcpy(lv->titulo, tit);
    lv->id = id;
    return lv;
}

void push(Pilha *p, Livro *lv){
    // empura um elemento na pilha
    if (lv != NULL)
    {
        lv->proximo = p->topo;
        p->topo = lv;
        p->qtd++;
    }
    else
    {
        printf("\n ---  PUSH não Realizado - Elemento Inválido!!");
    }
}

Livro *pop(Pilha *p){
    // salta um elemento da pilha
    Livro *aux = p->topo;
    if (aux == NULL)
    {
        printf("\n -- Nao pode realizar POP - Pilha Vazia\n");
    }
    else
    {
        p->topo = p->topo->proximo;
        p->qtd--;
        aux->proximo = NULL;
    }
    return aux;
}

void mostraLivro(Livro lv){
    printf("\n\t %d - Titulo: %s \n\t Autor: %s \n\t Ano: %d \n", lv.id, lv.titulo, lv.autor, lv.ano);
}

void mostraTopo(Pilha *p){
    if (p->topo != NULL)
    {
        printf("\n Mostra TOPO - Pilha");
        mostraLivro(*p->topo);
    }
    else
    {
        printf("\n TOPO NULO - Pilha Vazia \n");
    }
}

void apagaPilha(Pilha *p){
    // apaga os elementos da pilha
    while (p->topo != NULL)
    {
        free(pop(p));
    }
}

void mostraPilha(Pilha *p){
    Livro *aux = p->topo;
    if (aux == NULL)
        printf("\n  -- Pilha Vazia!!\n");
    else
        while (aux != NULL)
        {
            mostraLivro(*aux);
            aux = aux->proximo;
        }
}

// Exercicios de C
// 1) Implemente a Função inverte Pilha P1 – Cópia de P1 invertida
//   - Função recebe um pilha P1 e retorna um nova pilha (cópia P1) invertida
Pilha *copiaInvertida(Pilha *p){
    Pilha *paux = criaPilha();
    Pilha *novaCopia = criaPilha();
    Livro *laux = pop(p);

    while(laux != NULL){
        push(novaCopia, criaElementoPilhaLivro(laux->id, laux->ano, laux->autor, laux->titulo));
        push(paux, laux);
        laux = pop(p);
    }

    laux = pop(paux);
    return novaCopia;
}

// 2) Implemente a Função inverte Pilha P1 – Própria Pilha P1 fica invertida
//    - Recebe um pilha P1 e inverte a própria pilha P1 (invertida)
Pilha *pilhaInvertida(Pilha *p) {
    if (p == NULL || p->qtd < 2) {
        return p;
    }

    Pilha *paux1 = criaPilha();
    Pilha *paux2 = criaPilha();

    if (paux1 == NULL || paux2 == NULL) {
        free(paux1);
        free(paux2);
        return p;
    }

    Livro *laux;

    // 1 - Original para paux1
    while (p->topo != NULL) {
        laux = pop(p);
        push(paux1, laux);
    }

    // 2 - paux1 para paux2
    while (paux1->topo != NULL) {
        laux = pop(paux1);
        push(paux2, laux);
    }

    // 3 - paux2 para original
    while (paux2->topo != NULL) {
        laux = pop(paux2);
        push(p, laux);
    }

    free(paux1);
    free(paux2);

    return p;
}

// 3) Implemente uma função que troque o topo com o primeiro elemento da Pilha, sem alterar a ordem dos demais;
//    - Função recebe um pilha e troca o último elemento pelo primeiro elemento inserido na pilha
Pilha *inverterTopoComInicio(Pilha *p) {

    if (p == NULL || p->qtd < 2) {
        return p;
    }

    Pilha *paux = criaPilha();

    if (paux == NULL) {
        return p;
    }

    int qtd = p->qtd;

    Livro *topo;
    Livro *base;
    Livro *laux;

    // 1 - Retira o topo da pilha original
    topo = pop(p);

    // 2 - Transfere os elementos intermediarios
    // para a pilha auxiliar

    for (int i = 0; i < qtd - 2; i++) {
        laux = pop(p);
        push(paux, laux);
    }

    // 3 - Retira o ultimo elemento (base)
    base = pop(p);

    // 4 - Insere o antigo topo na pilha original
    push(p, topo);

    // 5 - Retorna os elementos intermediarios
    while (paux->topo != NULL) {
        laux = pop(paux);
        push(p, laux);
    }

    // 6 - Insere a antiga base no topo
    push(p, base);
    free(paux);

    return p;
}

void *inverterTopoComInicio2(Pilha *p){
    if (p == NULL || p->qtd < 2) {
        return p;
    }

    Livro *topo = p->topo;
    Livro *ultimo = p->topo;
    Livro *anteriorUltimo = NULL;

    // Localizando o último elemento da Pilha
    while(ultimo->proximo != NULL){
        anteriorUltimo = ultimo;
        ultimo = ultimo->proximo;
    }

    // Se a Pilha tem dois Elementos
    if(anteriorUltimo == topo){
        ultimo->proximo = topo;
        topo->proximo = NULL;
    } else {
        // Caso geral
        // tres ou mais ...
        Livro *segundo = topo->proximo;
        anteriorUltimo->proximo = topo;
        ultimo->proximo = segundo;
        topo->proximo;
    }

    // Atualizando o Topo da Pilha
    p->topo = ultimo;
    printf("\nTroca dos extremos realizada com sucesso!");
}


void menu(Pilha *p1, int ct){
    int op;
    Livro *lv;
    char ch;
    int ano;
    char titulo[20], autor[20];
    do
    {
        printf("\n\nInforme uma Opção:");
        printf("\n -- 1 - PUSH - Inserir novo Livro:");
        printf("\n -- 2 - POP - Remover um Livro:");
        printf("\n -- 3 - Mostra TOPO:");
        printf("\n -- 4 - Apagar Pilha:");
        printf("\n -- 5 - Mostrar Pilha:");
        printf("\n -- 6 - Inverte uma nova Pilha ");
        printf("\n -- 7 - Inverte Propria Pilha ");
        printf("\n -- 8 - Troca extremidas da pilha!");
        printf("\n -- 0 - para Sair do Programa:\n");
        printf("\nInforme sua Opçao:");
        scanf("%d", &op);
        fflush(stdin);

        switch (op)
        {
        case 1:
            printf("\n Função PUSH. \n");
            printf("Informe o Titulo do Livro:");
            scanf("%s", titulo);
            printf("Informe o Autor:");
            scanf("%s", autor);
            printf("Informe o Ano:");
            scanf("%d", &ano);
            push(p1, criaElementoPilhaLivro(ct++, ano, autor, titulo));
            printf("\n Inserção Realizada com Sucesso");
            break;
        case 2:
            printf("\n Função POP. \n");
            lv = pop(p1);
            if (lv != NULL)
            {
                mostraLivro(*lv);
                printf("\n --- Remoção Realizada com Sucesso!!");
                free(lv);
            }
            else
            {
                printf("\n --- ERRO - Remoção inválida!!");
            }
            break;
        case 3:
            printf("Mostra TOPO Pilha P1:");
            mostraTopo(p1);
            break;
        case 4:
            printf("\n Apagar a Pilha !! \n");
            apagaPilha(p1);
            break;
        case 5:
            printf("\nMostra Pilha P1:");
            mostraPilha(p1);
            break;
        case 6:
            printf("\n Cria uma Pilha Invertida sem alterar Pilha 1");
            printf("Pilha Original \n");
            mostraPilha(p1);

            printf("Cópia Invertida \n");
            Pilha *p2 = copiaInvertida(p1);
            mostraPilha(p2);
            break;

        case 7:
            printf("\n Inverte a Pilha 1");
            printf("\n Inverte a Pilha Modificando a Piha Original ");
            printf(" \n Pilha Inicial \n");
            mostraPilha(p1);

            printf("Invertendo a Pilha Original \n");
            pilhaInvertida(p1);
            // mostraPilha(p1);
            break;
        case 8:
            printf("\n Inverte Extremos da Pilha 1");
            break;

        default:
            printf("\nFim do programa!!\n");
        }

    } while (op > 0);
}

int main(){

    Pilha *p1;
    Livro *l1, *l2, *l3, *aux;

    p1 = criaPilha(); // pilha end X

    int ct = 1;

    l1 = criaElementoPilhaLivro(ct++, 2016, "Paul Deitel and  Harvey Deitel", "Java: Como Programar");
    l2 = criaElementoPilhaLivro(ct++, 2006, "H. M. Deitel", "C++: Como Programar 5°Ed.");
    l3 = criaElementoPilhaLivro(ct++, 2016, "Allen B. Downey", "Pense em Python:");

    push(p1, l1);
    push(p1, l2);
    push(p1, l3);

    menu(p1, ct);

    exit(0);
}