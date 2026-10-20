# Prova de Estruturas de Dados

> Questões Disertativas 

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
