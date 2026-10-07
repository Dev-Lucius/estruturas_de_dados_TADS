# Prova de Estruturas de Dados

## Questão 1 - Passagem por Valor e Passagem por Referência

Dentro da Linguagem C, todos os argumentos de uma função são passados por **valor**. Isso se deve ao fato de não existir um mecanismo nativo de "passagem por referência" como em outras linguagems (```C++```, ```Java```, ```Python```).

O que definimos como "passagem por referência" em C é, na verdade, a passagem do **valor de um ponteiro*** - isto é, passamos por valor o endereço de memória da variável original.

Sendo assim, podemos resumir ambos os conceitos da seguinte maneira:

- **Passagem por Valor** -> A função recebe uma "cópia" do valor da variável. Logo, qualquer alteração feita dentro da função afeta apenas essa cópia local deixando a variável original inalterada.

- Exemplo de Uso:

```c
void dobrar(int x) {
    x = x * 2;          // Modifica apenas a cópia local
    printf("Dentro da funcao: x = %d", x);
}

int main(void) {
    int a = 10;
    dobrar(a);
    printf("Fora da funcao: a = %d", a);   // a continua 10
    return 0;
}
```

```txt
Dentro da funcao: x = 20
Fora da funcao: a = 10
```

- **Passagem por Referência** -> Por sua vez, na passagem por referência, a função recebe o chamado **endereço de memória** da variável original (um **Ponteiro**). Ao dereferenciar o ponteiro, a função acessa e modifica diretamente a variável do escopo chamador.

- Exemplo de Uso (Com Tipo Primitivo):

```c
void dobrar(int *px) {
    if (px == NULL) {
        fprintf(stderr, "Erro: ponteiro nulo");
        return;
    }
    *px = *px * 2;        // Modifica a variável original via dereferenciação
}

int main(void) {
    int a = 10;
    dobrar(&a);           // Passa o endereço de 'a'
    printf("a = %d", a);  // a agora vale 20
    return 0;
}
```

- **a) O que Acontece com a Variável Original no Método Chamador (main) quando alteramos: Um Parâmetro de tipo primitivo (Ex: int, double) dentro da função chamada?**
> A variável original permanece inalterada

- **b) O que Acontece com a Variável Original no Método Chamador (main) quando alteramos: Os Elementos de um vetor passados por parâmetro**
> A variável original seria alterada, pois estamos acessando o endereço de memória da variável através do Vetor.
---

## Questão 2 - Operadores Ponto (.) e Seta (->)

Ambos os operadores são usados dentro do Contexto de **Struct**. Porém, ambos possuem suas próprias especficações;

- **Operador Ponto (.)** -> Este operador é usado para acessar os membros de um **Struct**. Isto é, nas variáveis diretas de uma **Struct** utiliza-se o operador ponto para acessar os membros 

- **Exemplo**:

```c
struct pessoa {
    int cod;
    char nome[15];
    char sobrenome[20];
    int idade;
    char telefone[10];
};

int main() {

    // DECLARAÇÃO E ATRIBUIÇÃO POSTERIOR
    struct pessoa joao;
    joao.cod = 1;
    joao.idade = 30;

    // Para strings, utiliza-se a função strcpy(destino, origem)
    // Porém, ainda é preciso usar o Operador Ponto (.)
    strcpy(joao.nome, "Joao Carlos");
    strcpy(joao.sobrenome, "Farias");
    strcpy(joao.telefone, "1212454533");

    // SAÍDA DA STRUCT JOAO
    printf("Pessoa: %s %s \n", joao.nome, joao.sobrenome);
    printf("\tCodigo: %d e idade %d \n", joao.cod, joao.idade);
    printf("\tTelefone: %s \n\n", joao.telefone);
    return 0;
}
```

- **Operador Seta (->)** -> Por sua vez, quando estamos trabalhando com ponteiros apontando para **Struct** utiliza-se o operador seta (->). Nesse caso:

```c
// Variável Direta
maria.idade = 20;
// Ponteiro
ps_maria -> idade = 20;
```

Assim, ao passar uma **Struct** como parâmetro para uma função por referência, utiliza-se um ponteiro para ela ( ```Pessoa *ps``` ).

A sua principal vantagem é permitir que as alterações feitas nos campos da **Struct** dentro da função fiquem gravadas na variável original (fora do escopo da função).

- **Exemplo**:

```c
#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int id;
    float nota;
} Aluno;

int main() {

    // 1. Alocação com malloc
    Aluno *aluno1 = (Aluno*) malloc(sizeof(Aluno));

    // Verificação de segurança
    if (aluno1 == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Atribuição de valores via ponteiro
    aluno1->id = 101;
    aluno1->nota = 9.5;
    printf("Aluno ID: %d, Nota: %.1f\n", aluno1->id, aluno1->nota);

    // 2. Liberação com free
    free(aluno1);

    // Boa prática: anular o ponteiro para evitar dangling pointer
    aluno1 = NULL;
    return 0;
}
```

---

## Questão 3 - 10 Valores de um Vetor

```c
// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

void imprimeVetor(int vt[], int n){
    for (int i=0; i<n; i++){
        printf("v[%d] = %d \n", i, vt[i]);
    }
}

// O menor Valor de um Vetor
int* menorVetorPonteiro(int *vt, int n){
    if (n <= 0) {
        return NULL;
    }

    int *pMenor = vt;

    for (int i = 1; i < n; i++) {
        if (*(vt + i) < *pMenor) {
            pMenor = vt + i;
        }
    }
    return pMenor;
}

// O maior valor de um vetor
int* maiorVetorPonteiro(int *vt, int n){
    if (n <= 0){
        return NULL;
    }

    int *pMaior = vt;

    for(int i = 1; i < n; i++){
        if(*(vt + i) > *pMaior){
            pMaior = vt + i;
        }
    }
    return pMaior;
}

// Repetidos
int* VetorRepetidos(int *vt, int n){
    if(n <= 0){
        return NULL;
    }

    int *repetidos;

    for(int i = 1; i < n; i++){
        if(*vt == *(vt + i)){
            repetidos == vt;
        }
    }
    return repetidos;
}

int main(){

    int v[10] = {1, 1, 2, 2, 5, 6, 7, 8, 9, 10};
    int n = 10;

    int *pMaiorValor = maiorVetorPonteiro(v, n);
    int *pMenorValor = menorVetorPonteiro(v, n);
    int *pRepetidos = VetorRepetidos(v, n);

    if(pMaiorValor != NULL){
        printf("Maior elemento = %d\n", *pMaiorValor);
        printf("Endereco do Maior = %p\n", (int*)pMaiorValor);
    }

    printf("\n");

    if(pMenorValor != NULL){
        printf("Menor elemento = %d\n", *pMenorValor);
        printf("Endereco do Menor = %p\n", (int*)pMenorValor);
    }

    printf("\n");

    if(pRepetidos != NULL){
        printf("Vetor Repetidos = %d\n", *pRepetidos);
    }

    return 0;
}
```

---

## Questão 4 - Carro, Motor, Rodas

```c
// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

typedef struct Motor{
    int nrmMotor;
    int potencia;
    char combustivel[10];
} Motor;

typedef struct Rodas{
    int diametro;
    char nrmRoda[10];
} Rodas;

typedef struct Carro{
    int nrmChassi;
    char modelo[30];
    char cor[10];
    Motor mt;
    Rodas rd[4];
} Carro;


// Registrar Motor
void registrarMotor(Motor *mtr, int numMotor, int pot, char combust[10]){
    if(mtr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    mtr->nrmMotor = numMotor;
    mtr->potencia = pot;
    strcpy(mtr->combustivel, combust);
}

// Registrar Roda
void registrarRoda(Rodas *rod, int diam, char numRoda[10]){
    if(rod == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    rod->diametro=diam;
    strcpy(rod->nrmRoda, numRoda);
}

// Registrar Carro
void registrarCarro(Carro *cr, int numChassi, char modCarro[30], char corCarro[10], Motor motCarro, Rodas rodCarro){
    
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    cr->nrmChassi = numChassi;
    strcpy(cr->modelo, modCarro);
    strcpy(cr->cor, corCarro);
    cr->mt = motCarro;
    cr->rd[0] = rodCarro;
    cr->rd[1] = rodCarro;
    cr->rd[2] = rodCarro;
    cr->rd[3] = rodCarro;
}

// Instalar Motor no Carro
void instalarMotorCarro(Carro *cr, Motor mtr){
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }
    cr->mt = mtr;
}

// Instalar Roda no Carro
void instalarRodaCarro(Carro *cr, Rodas rods){
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    if(sizeof(cr->rd) < 4){
        printf("Carro Não Possui 4 Rodas");
    }

    cr->rd[0] = rods;
    cr->rd[1] = rods;
    cr->rd[2] = rods;
    cr->rd[3] = rods;
}

// Mostrar Carro
void mostrarCarro(Carro carro){
    printf("Número do Chassi: %d\n", carro.nrmChassi);
    printf("Modelo do Carro: %s\n", carro.modelo);
    printf("Cor do Carro: %s\n", carro.cor);
    printf("Potencia do Motor do Carro: %d\n", carro.mt.potencia);
    printf("Numero das Rodas do Carro: %s\n", carro.rd->nrmRoda);
}

int main(){

    struct Rodas roda;
    roda.diametro = 10;
    strcpy(roda.nrmRoda, "R13");

    struct Motor m1;
    m1.nrmMotor = 17;
    m1.potencia = 750;
    strcpy(m1.combustivel, "Gasolina");

    struct Carro c1;
    c1.nrmChassi = 25;
    strcpy(c1.modelo, "Hilux");
    strcpy(c1.cor, "Preto");
    c1.mt = m1;
    c1.rd[0] = roda;
    c1.rd[1] = roda;
    c1.rd[2] = roda;
    c1.rd[3] = roda;

    struct Carro c2;
    c2.nrmChassi = 25;
    strcpy(c2.modelo, "Civic");
    strcpy(c2.cor, "Branco");
    c2.mt = m1;
    c2.rd[0] = roda;
    c2.rd[1] = roda;
    c2.rd[2] = roda;
    c2.rd[3] = roda;

    struct Carro c3;
    registrarCarro(c3, 25, "Ferrari", "Vermelha", m1, roda);

    mostrarCarro(c1);
    mostrarCarro(c2);
    mostrarCarro(c3);

    return 0;
}
```

---

## Questão 5 - Lista Simplesmente Encadeada

```c
// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

// Estruturas
typedef struct musica{
    int id;
    char titulos[30];
    char artista[30];
    int duracao;
} Musica;

typedef struct no{
    Musica dado;
    struct no *anterior;
    struct no *proximo;
} No;

typedef struct lista{
    No *primeiro;
    No *ultimo;
    No *musicaAtual;
    char nome[30];
    int num;
} LSE;

// Funções
// 1. InserirNovaMusicaInicio
void inserirNovaMusicaInicio(LSE *ls, No *novo){
    novo->proximo = ls->primeiro;
    ls->primeiro = novo;
    ls->num++;
}

// 2. InserirNovaMusicaFim
void inserirNovaMusicaFim(LSE *ls, No *novo){
    novo->proximo = NULL;

    if(ls->primeiro == NULL){
        ls->primeiro = novo;
    } else {
        No *aux = ls->primeiro;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = novo;
    }
    ls->num++;
}

// 3. AvancarMusica
void avancarMusica(LSE *ls){
}

// 4. RetrocederMusica


// 5. MostrarPlaylist
void mostrarPlaylist(LSE *ls, Musica *ms){
    
}
```

--- 

## Questão 6

- 1. (V) 

- 2. (F) - O Ponteiro Auxiliar deve apontar para o Primeiro Elemento da Fila

- 3. (V)

- 4. (V)

- 5. (F) - Se Caso ambas as Lihas forem trocadas, o ponteiro auxiliar ganhará um outro valor distinto do que ele possui originalmente, o que afetará a o resultado final da função

- 6. (V)