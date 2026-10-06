# Questão 1

- Código Original

```c
Aluno* novo = (Aluno*) malloc(sizeof(Aluno));
strcpy(novo->nome, "Juca da silva!");
// O que falta aqui para garantir que o nó não aponte para um lixo?
```

## Resolução

- Neste código, falta uma linha específica, no caso:

```c
novo->proximo = NULL;
```

> **malloc** não zera a Memória. Nesse caso, o campo "proximo" nasce com lixo (endereço aleatorio). 
> Assim ao percorrer a lista o laço tentaria seguir esse endereço inválido o que casa Segmentation Fault

### Problemas Extras:

* a) não verificar se malloc retornou NULL;
* b) strcpy sem limite -> prefira snprintf/strncpy;
* c) se "nome" fosse char* (e não vetor), strcpy escreveria em ponteiro 
* d) não inicializado -> também precisaria de malloc para o texto.

---

# Questão 2

- Código Original

```c
lista->proximo = novo;
novo->proximo = lista->primeiro; // Agora primeiro == novo
```

## Resolução

- Neste codigo, o problema está na Ordem das Instruções

> Na 1° linha, a única referencia para a lista antiga é sobrescrita
> Na 2° linha, o nó aponta para si mesmo (ciclo) e TODA a lista original fica inacessível (vazamento de memoria)

- **Lembre-se**: primeiro "pendure" o novo nó no resto da lista, só depois mude a cabeça

```c
void insereInicio(LSE *lista, Aluno *novo) {
    novo->proximo   = lista->primeiro;   /* 1º: novo agarra a lista antiga */
    lista->primeiro = novo;              /* 2º: cabeça passa a apontar p/ novo */
}
```

---

# Questão 3

- Código Original

```c
while (strcmp(atual->matricula, mat)) { atual = atual->proximo; }
```

## Resolução

- Aqui, o laço não verifica se "atual" chegou ao fim (NULL)

> se a matrícula NÃO existe (ou se a lista está vazia), "atual" vira NULL
> Além disso, strcmp vai tentar ler NULL->matricula o que causa segmentation fault

- **Lembre-se**: a ORDEM da condição importa: "atual != NULL" vem primeiro, pois o && faz curto-circuito e evita o acesso inválido.

```c
Aluno *buscaMatricula(LSE *lista, const char *mat) {
    Aluno *atual = lista->primeiro;
    while (atual != NULL && strcmp(atual->matricula, mat) != 0) {
        atual = atual->proximo;
    }
    return atual;   /* achou -> endereço do nó; não achou -> NULL */
}
```

---

# Questão 4

- Código Original

```c
aux->proximo = novoAluno;
```

## Resolução

- Neste Código, falta a Linha: 

```c
novoAluno->proximo = NULL
```

> Se essa linha, o último nó fica com "proximo" = lixo de memória.
> Assim, ao imprimir, o laço passa do último aluno e segue um endereço aleatorio
> **Imprime Lixo**, **Segmentation Fault** ou **Entra em um Loop Infinito**

```c
void insereFim(LSE *lista, Aluno *novo) {
    novo->proximo = NULL;                /* o novo nó é o último: fecha a lista */
 
    if (lista->primeiro == NULL) {       /* caso de borda: lista vazia */
        lista->primeiro = novo;
        return;
    }
    Aluno *aux = lista->primeiro;
    while (aux->proximo != NULL) {       /* para NO último nó (não depois) */
        aux = aux->proximo;
    }
    aux->proximo = novo;
}
```

---

# Questão 5

- Código Original

```c
Aluno* aux = lista->primeiro;
lista->primeiro = aux->proximo; // <-- Aqui
free(aux);
```

- O cenário em questão é: **lista VAZIA ```(primeiro == NULL)```**

> Isso se deve ao fato de que ``` aux = NULL ``` e ``` aux->proximo ``` desreferencial ```NULL``` o que gera um SEGMENTATION FAULT
> Porém, isso funciona com 1 Elemento -> Primeiro passa a ser NULL, que é o certo

```c
int removeInicio(LSE *lista) {
    if (lista->primeiro == NULL) {
        return 0;                        /* nada a remover */
    }
    Aluno *aux = lista->primeiro;        /* guarda o nó que vai sair */
    lista->primeiro = aux->proximo;      /* cabeça "pula" o primeiro */
    free(aux);                           /* só agora libera */
    return 1;
}
```

--- 

# Questão 6

- Código Original

```c
while (atual->proximo != NULL) { cont++; atual = atual->proximo; }
```

- Neste código, a condição testa ``` atual->proximo ```, então o laço PARA no último nó sem contá-lo -> **Sempre 1 a Menos** (5 Alunos Retorna 4)
- Além disso, com lista vazia ( ``` atual == NULL ```) quebra ao acessar ```atual->proximo```;

> Uma boa ideia de Correção seria testar o PRÓPRIO nó atual: (```atual != NULL ```)
> Desse modo, contamos o último nó e funciona com lista vazia (retorna 0)

```c
int contaAlunos(const LSE *lista) {
    int cont = 0;
    const Aluno *atual = lista->primeiro;
    while (atual != NULL) {
        cont++;
        atual = atual->proximo;
    }
    return cont;
}
```

---

# Questão 7

- Código Original

```c
novo->proximo      = anterior->proximo;   // 1º: novo aponta p/ o resto
anterior->proximo  = novo;                // 2º: anterior aponta p/ novo
```

- Aqui, **a ORDEM é obrigatória**
- Se fizessemos ```anterior->proximo = novo``` primeiro, perderíamos o endereço do "resto da lista" **(Mesmo Erro do Exercício 2)**

- Versão Completa:
    * ```N == 1``` -> equivale a inserir no início (não existe "anterior");
    * ```N  > 1``` -> caminha até o nó N-1 (para N=2, o próprio primeiro);
    * Se a posição é maior que tamanho+1 -> inválida, retorna 0.

> Em caso de falha, quem chamou continua dono do Nó **(deve ser free)**

```c
int inserePosicao(LSE *lista, int N, Aluno *novo) {
    if (N < 1) {
        return 0;
    }
    if (N == 1) {
        insereInicio(lista, novo);
        return 1;
    }
    Aluno *anterior = lista->primeiro;
    for (int i = 1; i < N - 1 && anterior != NULL; i++) {
        anterior = anterior->proximo;    /* para no nó de posição N-1 */
    }
    if (anterior == NULL) {
        return 0;                        /* posição além do fim da lista */
    }
    novo->proximo     = anterior->proximo;   /* lacuna 1 */
    anterior->proximo = novo;                /* lacuna 2 */
    return 1;
}
```

--- 

# Questão 8

- Código Original

```c
lista->primeiro = NULL;
printf("Lista Apagada com Sucesso");
```

- Aqui, nós não apagamos nada, apenas "esquece" o endereço do primeiro Nó
- Além disso, nenhum  ```free()``` foi feito de fato

> Mas o que acontece Com os Nós?
> Eles apenas continuam alocados no heap (ocupando RAM), mas ficam inalcançaveis.
> Pois ninguem guarda os seus endereços de memória. O que resulta em Memory Leak
> Uma solução seria percorrer a Lista liberando cada Nó!

```c
void apagaLista(LSE *lista) {
    Aluno *atual = lista->primeiro;
    while (atual != NULL) {
        Aluno *proximo = atual->proximo;  /* 1º: salva o próximo */
        free(atual);                      /* 2º: libera o atual */
        atual = proximo;                  /* 3º: avança */
    }
    lista->primeiro = NULL;               /* lista consistente: vazia */
}
```

- **Lembre-se**: guarde o ```proximo``` antes do ```free()```

---

# Questão 9

- Código Original

```c
// Esquece dentro do do-while
aux = aux->proximo;
```

- Sem o avanço, ```aux``` nunca muda
- Logo, a condição é sempre verdadeira e o primeiro Nome é impresso para sempre

> O "if (aux != NULL)" externo é necessário: o do-while executa o corpo ao menos UMA vez, então sem ele a lista vazia causaria aux->nome em NULL.

```c
void imprimeLista(const LSE *lista) {
    const Aluno *aux = lista->primeiro;
    if (aux != NULL) {
        do {
            printf("   Nome: %s (mat. %s)\n", aux->nome, aux->matricula);
            aux = aux->proximo;           /* <- o avanço que faltava */
        } while (aux != NULL);
    } else {
        printf("   (lista vazia)\n");
    }
}
```

---

# Questão 10

- Proposta do Aluno
    * Proposta do aluno: inverter o ponteiro "proximo" de cada nó durante a Leitura

- Riscos:
    - 1. DESTRUTIVO: a lista original é modificada. Só queríamos EXIBIR, mas passamos a ter outra lista (invertida) na memória.

    - 2. Perda da lista: ao inverter atual->proximo sem guardar o antigo, perde-se o resto da lista. São necessários 3 ponteiros (anterior, atual, proximo).

    - 3. Esquecer de atualizar lista->primeiro: a cabeça passa a apontar para o ANTIGO primeiro, que agora é o último -> a lista "some" (só aparece 1 elemento).

    - 4. Interrupção no meio (erro, sinal, outra thread) deixa a estrutura inconsistente: metade invertida, metade não.

    - 5. Outros ponteiros/iteradores que guardavam endereços de nós passam a enxergar vizinhos diferentes.

- Alterantivas Seguras
    - a) recursão: desce até o fim e imprime na volta;

    - b) vetor auxiliar de ponteiros, preenchido e lido de trás para frente.

```c
static void imprimeInvertidaRec(const Aluno *no) {
    if (no == NULL) {
        return;                           /* caso base: passou do último */
    }
    imprimeInvertidaRec(no->proximo);     /* desce até o fim... */
    printf("   Nome: %s\n", no->nome);    /* ...e imprime na VOLTA */
}
 
void imprimeInvertida(const LSE *lista) {          /* alternativa (a) */
    imprimeInvertidaRec(lista->primeiro);
}
 
void imprimeInvertidaVetor(const LSE *lista) {     /* alternativa (b) */
    int n = contaAlunos(lista);
    if (n == 0) {
        printf("   (lista vazia)\n");
        return;
    }
    const Aluno **vet = (const Aluno **) malloc(n * sizeof(Aluno *));
    if (vet == NULL) {
        return;
    }
    int i = 0;
    for (const Aluno *p = lista->primeiro; p != NULL; p = p->proximo) {
        vet[i++] = p;
    }
    for (i = n - 1; i >= 0; i--) {        /* leitura de trás para frente */
        printf("   Nome: %s\n", vet[i]->nome);
    }
    free(vet);
}
```

---

```c
void inverteLista(LSE *lista) {                    /* versão in-place correta */
    Aluno *anterior = NULL;
    Aluno *atual    = lista->primeiro;
    Aluno *proximo  = NULL;
    while (atual != NULL) {
        proximo         = atual->proximo;  /* 1º: guarda o resto da lista */
        atual->proximo  = anterior;        /* 2º: inverte o elo */
        anterior        = atual;           /* 3º: avança "anterior" */
        atual           = proximo;         /* 4º: avança "atual" */
    }
    lista->primeiro = anterior;            /* cabeça = antigo último nó */
}
```
