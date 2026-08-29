# Guia Completo: Passagem por Valor e Passagem por Referência em C

## 1. Introdução

Em C, todos os argumentos de função são passados por valor. Não existe um mecanismo nativo de "passagem por referência" como em outras linguagens (C++, Java, Python). O que chamamos de "passagem por referência" em C é, na verdade, a passagem do **valor de um ponteiro** — ou seja, passamos por valor o endereço de memória da variável original.

Compreender essa distinção é fundamental para manipular corretamente structs, arrays e qualquer dado cujo estado precise ser modificado fora do escopo da função chamada.

---

## 2. Passagem por Valor

### 2.1 Definição

A função recebe uma **cópia** do valor da variável. Qualquer modificação feita dentro da função afeta apenas essa cópia local. A variável original permanece inalterada.

### 2.2 Quando Usar

- Exibição de dados (funções de `print`, `dump`, `show`).
- Cálculos que não precisam alterar os operandos.
- Tipos primitivos pequenos (`int`, `char`, `float`, `double`) onde a cópia é barata.
- Quando a imutabilidade dos dados de entrada é desejável.

### 2.3 Exemplo

```c
#include <stdio.h>

void dobrar(int x) {
    x = x * 2;          // Modifica apenas a cópia local
    printf("Dentro da funcao: x = %d
", x);
}

int main(void) {
    int a = 10;
    dobrar(a);
    printf("Fora da funcao: a = %d
", a);   // a continua 10
    return 0;
}
```

**Saída:**
```
Dentro da funcao: x = 20
Fora da funcao: a = 10
```

### 2.4 Com Structs

```c
#include <stdio.h>

typedef struct {
    int dia, mes, ano;
} Data;

void mostrarData(Data d) {      // Recebe cópia da struct
    printf("%02d/%02d/%d
", d.dia, d.mes, d.ano);
}

int main(void) {
    Data hoje = {29, 8, 2026};
    mostrarData(hoje);          // hoje não é alterada
    return 0;
}
```

### 2.5 Custo

Para structs grandes, a cópia por valor pode ser custosa em memória e tempo de execução. Nesses casos, prefira passar um ponteiro para a struct (passagem por referência simulada), mesmo que a função não vá modificá-la. Para indicar que o ponteiro não será modificado, use o qualificador `const`:

```c
void mostrarData(const Data *d) {
    printf("%02d/%02d/%d
", d->dia, d->mes, d->ano);
}
```

---

## 3. Passagem por Referência (via Ponteiro)

### 3.1 Definição

A função recebe o **endereço de memória** da variável original (um ponteiro). Ao dereferenciar o ponteiro, a função acessa e pode modificar diretamente a variável do escopo chamador.

### 3.2 Quando Usar

- Modificação do estado de variáveis do chamador.
- Retorno de múltiplos valores de uma função.
- Manipulação de structs grandes (evita cópia desnecessária).
- Alocação dinâmica de memória (`malloc`, `calloc`, `realloc`).
- Implementação de estruturas de dados encadeadas (listas, árvores, grafos).

### 3.3 Exemplo com Tipo Primitivo

```c
#include <stdio.h>

void dobrar(int *px) {
    if (px == NULL) {
        fprintf(stderr, "Erro: ponteiro nulo
");
        return;
    }
    *px = *px * 2;        // Modifica a variável original via dereferenciação
}

int main(void) {
    int a = 10;
    dobrar(&a);           // Passa o endereço de 'a'
    printf("a = %d
", a); // a agora vale 20
    return 0;
}
```

### 3.4 Exemplo com Struct

```c
#include <stdio.h>

typedef struct {
    int num;
    char fileira;
    int livre;
} Poltrona;

void ocuparPoltrona(Poltrona *p) {
    if (p == NULL) {
        fprintf(stderr, "Erro: ponteiro nulo
");
        return;
    }
    p->livre = 0;         // Modifica o campo da struct original
}

int main(void) {
    Poltrona p1 = {1, 'A', 1};
    ocuparPoltrona(&p1);
    printf("Status: %s
", p1.livre ? "Livre" : "Ocupada");
    return 0;
}
```

### 3.5 Arrays e Ponteiros

Em C, o nome de um array é convertido implicitamente para um ponteiro para seu primeiro elemento quando passado como argumento. Portanto, arrays são sempre passados "por referência" (na prática, passa-se o endereço do primeiro elemento):

```c
#include <stdio.h>

void preencher(int vetor[], int tamanho, int valor) {
    // 'vetor' é na verdade um 'int *vetor'
    for (int i = 0; i < tamanho; i++) {
        vetor[i] = valor;     // Modifica o array original
    }
}

int main(void) {
    int nums[5];
    preencher(nums, 5, 42);   // 'nums' decai para 'int *'
    for (int i = 0; i < 5; i++) {
        printf("%d ", nums[i]);
    }
    return 0;
}
```

**Nota:** A notação `int vetor[]` nos parâmetros é equivalente a `int *vetor`. O compilador ignora o tamanho entre colchetes.

---

## 4. Tabela Comparativa

| Aspecto | Passagem por Valor | Passagem por Referência (Ponteiro) |
|---------|-------------------|-----------------------------------|
| O que é passado | Cópia do valor | Endereço de memória (ponteiro) |
| Modifica o original | Não | Sim (se dereferenciado) |
| Custo de memória | Alto para structs grandes | Baixo (apenas o tamanho do ponteiro) |
| Segurança | Alta (imutável) | Requer cuidado com NULL e aliasing |
| Uso típico | Exibição, cálculos | Modificação, alocação, estruturas grandes |
| Sintaxe na chamada | `funcao(x)` | `funcao(&x)` |
| Sintaxe no parâmetro | `Tipo param` | `Tipo *param` |
| Acesso aos campos | `param.campo` | `param->campo` ou `(*param).campo` |

---

## 5. Operadores de Ponteiro

| Operador | Nome | Descrição |
|----------|------|-----------|
| `&` | Endereço | Obtém o endereço de memória de uma variável. Ex: `&x` |
| `*` | Dereferenciação | Acessa o valor apontado por um ponteiro. Ex: `*ptr` |
| `->` | Acesso a membro | Acessa campo de struct via ponteiro. Ex: `ptr->campo` |

---

## 6. Boas Práticas

### 6.1 Verificação de Ponteiro Nulo

Sempre verifique se o ponteiro recebido não é `NULL` antes de dereferenciá-lo. Isso evita segmentation faults:

```c
void inicializarSala(Sala *s, int numSala) {
    if (s == NULL) {
        fprintf(stderr, "Erro: ponteiro nulo em inicializarSala
");
        return;
    }
    s->num_sala = numSala;
    // ...
}
```

### 6.2 Uso de `const` para Ponteiros de Leitura

Se uma função recebe um ponteiro mas não deve modificar os dados, declare o parâmetro como `const`:

```c
void mostrarSessao(const Sessao *s) {
    // O compilador garante que 's' não será modificado aqui
    printf("Filme: %s
", s->nomeFilme);
}
```

Isso documenta a intenção e permite que o compilador detecte modificações acidentais.

### 6.3 Evite Retornar Ponteiros para Variáveis Locais

Nunca retorne o endereço de uma variável local de uma função, pois ela é destruída ao final do escopo:

```c
// ERRADO
int* criarValor(void) {
    int x = 42;
    return &x;   // x será destruída; ponteiro pendente (dangling pointer)
}

// CORRETO
int* criarValor(void) {
    int *x = malloc(sizeof(int));
    if (x != NULL) {
        *x = 42;
    }
    return x;    // Válido, mas o chamador deve liberar com free()
}
```

### 6.4 Documente a Semântica de Passagem

Use nomes de parâmetros e comentários para deixar claro se a função modifica ou apenas lê os dados:

```c
// Modifica a struct apontada por 's'
void cadastrarSessao(Sessao *s, const char *nome, Data d, int hora);

// Apenas lê a struct apontada por 's'
void mostrarSessao(const Sessao *s);
```

### 6.5 Preferência por Ponteiros para Structs Grandes

Para structs com muitos campos ou arrays internos, sempre passe por ponteiro para evitar cópias custosas:

```c
// Ruim: copia toda a struct (15 poltronas + metadados)
void mostrarMapaSala(Sala s);

// Melhor: passa apenas o endereço
void mostrarMapaSala(const Sala *s);
```

---

## 7. Casos Especiais

### 7.1 Ponteiro para Ponteiro

Usado quando a função precisa modificar o próprio ponteiro do chamador (ex: alocação dinâmica, inserção em lista encadeada):

```c
#include <stdio.h>
#include <stdlib.h>

void alocarInt(int **pp, int valor) {
    *pp = malloc(sizeof(int));
    if (*pp != NULL) {
        **pp = valor;
    }
}

int main(void) {
    int *ptr = NULL;
    alocarInt(&ptr, 100);
    if (ptr != NULL) {
        printf("Valor: %d
", *ptr);
        free(ptr);
    }
    return 0;
}
```

### 7.2 Ponteiro para Função

Em C, funções também podem ser passadas como argumentos via ponteiros, permitindo callbacks e estratégias polimórficas:

```c
#include <stdio.h>

int soma(int a, int b) { return a + b; }
int mult(int a, int b) { return a * b; }

int operar(int a, int b, int (*operacao)(int, int)) {
    return operacao(a, b);
}

int main(void) {
    printf("Soma: %d
", operar(3, 4, soma));
    printf("Mult: %d
", operar(3, 4, mult));
    return 0;
}
```

---

## 8. Erros Comuns

| Erro | Causa | Solução |
|------|-------|---------|
| Segmentation fault | Dereferenciar ponteiro NULL ou inválido | Verificar `if (p != NULL)` antes de usar |
| Dangling pointer | Retornar endereço de variável local | Usar `malloc` ou passar ponteiro do chamador |
| Memory leak | Alocar com `malloc` e não liberar com `free` | Sempre liberar memória alocada dinamicamente |
| Modificação inesperada | Passar por ponteiro sem necessidade | Usar passagem por valor ou `const` |
| Confusão `*` vs `&` | Não entender que `*` dereferencia e `&` pega endereço | Revisar operadores de ponteiro |

---

## 9. Resumo Rápido

- **Por valor**: `funcao(x)` — a função recebe uma cópia. Útil para exibição e cálculos. Seguro, mas pode ser custoso para structs grandes.
- **Por referência**: `funcao(&x)` — a função recebe o endereço. Útil para modificação, alocação e structs grandes. Requer cuidado com ponteiros nulos.
- **Regra prática**: se a função precisa alterar a variável original, use ponteiro. Se for apenas ler, use valor (ou `const Tipo *` para structs grandes).

---

## 10. Referências

- ISO/IEC 9899:2018 (C17 Standard) — Seção 6.3.2.1 (Lvalues, arrays, and function designators)
- ISO/IEC 9899:2018 — Seção 6.5.2.2 (Function calls)
- Kernighan, B. W.; Ritchie, D. M. *The C Programming Language*. 2nd ed. Prentice Hall, 1988.
- Harbison, S. P.; Steele, G. L. *C: A Reference Manual*. 5th ed. Prentice Hall, 2002.
