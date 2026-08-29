# 📋 Resumo: Inserir na Posição e Remover na Posição (LSE)
> Baseado no material do Prof. Luciano Vargas Gonçalves — IFRS

---

## 🎯 Conceito Geral

Diferente das operações de **início** e **fim**, inserir/remover em uma **posição específica** exige:

1. **Percorrer** a lista até a posição desejada
2. Manter um ponteiro para o **nó anterior** (para "costurar" a lista)
3. Ajustar os ponteiros `proximo` do nó anterior e do novo nó

> **Atenção:** A posição `0` é o **início** da lista. A última posição válida é `n-1` (onde `n` é o número de elementos).

---

## ➕ Inserir na Posição

### Protótipo
```c
void insereNaPosicao(LSE *lista, Aluno *novo, int pos);
```

### Situações a avaliar

| Situação | Condição | O que fazer |
|----------|----------|-------------|
| **Posição inválida** | `pos < 0` ou `pos > n` | Não insere (erro) |
| **Inserir no início** | `pos == 0` | Chama `insereNoInicio()` |
| **Inserir no fim** | `pos == n` | Chama `insereNoFim()` |
| **Inserir no meio** | `0 < pos < n` | Percorre até pos-1 e encaixa |

### Passo a passo visual — Inserir na posição 2

```
ANTES (n=4, inserir na pos 2):

*primeiro
    │
    ▼
┌───┐    ┌───┐    ┌───┐    ┌───┐
│ E0│───→│ E1│───→│ E2│───→│ E3│───→ NULL
└───┘    └───┘    └───┘    └───┘
 0        1        2        3
                    ↑
                 posição alvo

PASSO 1: Percorrer até pos-1 (posição 1)
         aux aponta para E1

PASSO 2: novo->proximo = aux->proximo
         (novo aponta para E2)

         ┌───┐
         │Novo│───→┌───┐
         └───┘    │ E2│
                   └───┘

PASSO 3: aux->proximo = novo
         (E1 agora aponta para Novo)

DEPOIS (n=5):

*primeiro
    │
    ▼
┌───┐    ┌───┐    ┌───┐    ┌───┐    ┌───┐
│ E0│───→│ E1│───→│Novo│───→│ E2│───→│ E3│───→ NULL
└───┘    └───┘    └───┘    └───┘    └───┘
 0        1        2        3        4
```

### Código completo

```c
void insereNaPosicao(LSE *lista, Aluno *novo, int pos) {
    // 1. Validação da posição
    if (pos < 0 || pos > lista->n_elementos) {
        printf("Posicao invalida!\n");
        return;
    }

    // 2. Casos especiais: início ou fim
    if (pos == 0) {
        insereNoInicio(lista, novo);
        return;
    }
    if (pos == lista->n_elementos) {
        insereNoFim(lista, novo);
        return;
    }

    // 3. Inserir no meio: percorre até pos-1
    Aluno *aux = lista->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    // 4. Encaixa o novo nó
    novo->proximo = aux->proximo;   // novo aponta para quem estava na pos
    aux->proximo = novo;             // anterior aponta para o novo

    lista->n_elementos++;
}
```

### Ordem CRÍTICA dos ponteiros

```c
// ✅ CORRETO: primeiro liga o novo, depois o anterior
novo->proximo = aux->proximo;   // salva a referência antes de perder!
aux->proximo = novo;

// ❌ ERRADO: se inverter, perde o resto da lista!
aux->proximo = novo;            // E2 some! Lista "corta" aqui
novo->proximo = aux->proximo;   // novo->proximo aponta para ele mesmo!
```

---

## ➖ Remover na Posição

### Protótipo
```c
Aluno* removeNaPosicao(LSE *lista, int pos);
```

### Situações a avaliar

| Situação | Condição | O que fazer |
|----------|----------|-------------|
| **Lista vazia** | `n == 0` | Retorna `NULL` |
| **Posição inválida** | `pos < 0` ou `pos >= n` | Retorna `NULL` |
| **Remover do início** | `pos == 0` | Chama `removeNoInicio()` |
| **Remover do meio/fim** | `0 < pos < n` | Percorre até pos-1 e "pula" o nó |

### Passo a passo visual — Remover da posição 2

```
ANTES (n=5, remover da pos 2):

*primeiro
    │
    ▼
┌───┐    ┌───┐    ┌───┐    ┌───┐    ┌───┐
│ E0│───→│ E1│───→│ E2│───→│ E3│───→│ E4│───→ NULL
└───┘    └───┘    └───┘    └───┘    └───┘
 0        1        2        3        4
                    ↑
                 alvo da remoção

PASSO 1: Percorrer até pos-1 (posição 1)
         aux aponta para E1

PASSO 2: Salvar ponteiro para o nó a remover
         removido = aux->proximo  (E2)

PASSO 3: "Pular" o nó removido
         aux->proximo = removido->proximo
         (E1 agora aponta direto para E3)

         ┌───┐         ┌───┐
         │ E1│────────→│ E3│
         └───┘    X    └───┘
                   ↑
                E2 "desencadeado"

PASSO 4: n_elementos--
         Retornar removido

DEPOIS (n=4):

*primeiro
    │
    ▼
┌───┐    ┌───┐    ┌───┐    ┌───┐
│ E0│───→│ E1│───→│ E3│───→│ E4│───→ NULL
└───┘    └───┘    └───┘    └───┘
 0        1        2        3

⚠️  E2 ainda existe na memória! Precisa de free() para excluir.
```

### Código completo

```c
Aluno* removeNaPosicao(LSE *lista, int pos) {
    // 1. Validações
    if (lista->primeiro == NULL || pos < 0 || pos >= lista->n_elementos) {
        return NULL;   // lista vazia ou posição inválida
    }

    // 2. Caso especial: remover do início
    if (pos == 0) {
        return removeNoInicio(lista);
    }

    // 3. Percorre até o nó ANTERIOR à posição
    Aluno *aux = lista->primeiro;
    for (int i = 0; i < pos - 1; i++) {
        aux = aux->proximo;
    }

    // 4. aux está em pos-1, aux->proximo é o alvo
    Aluno *removido = aux->proximo;
    aux->proximo = removido->proximo;   // "pula" o nó removido

    lista->n_elementos--;
    return removido;   // quem chamou deve dar free() ou usar os dados
}
```

---

## ⚠️ Armadilhas que Todo Mundo Cai

| Armadilha | Por que acontece | Como evitar |
|-----------|-----------------|-------------|
| **Loop infinito** | `aux = aux` (esqueceu `->proximo`) | Sempre `aux = aux->proximo` |
| **Segmentation fault** | Acessa `aux->proximo` quando `aux == NULL` | Verifique `aux != NULL` no `while` |
| **Perde o resto da lista** | Inverte ordem dos ponteiros na inserção | Sempre: `novo->prox = aux->prox` **antes** de `aux->prox = novo` |
| **Posição off-by-one** | Confunde posição com índice | Posição `n` = após o último (novo fim) |
| **Não decrementa n** | Esquece `n_elementos--` | Sempre atualize o contador! |
| **Memory leak na remoção** | Retorna o nó mas nunca dá `free()` | Quem chama `removeNaPosicao` deve excluir depois |

---

## 📊 Complexidade

| Operação | Melhor caso | Pior caso | Observação |
|----------|-------------|-----------|------------|
| **Inserir na posição** | O(1) | O(n) | O(1) só se for posição 0 |
| **Remover na posição** | O(1) | O(n) | O(1) só se for posição 0 |

> Sempre precisa percorrer até `pos-1`, por isso é linear no pior caso.

---

## 🧠 Regra de Ouro

```
INSERIR:  novo->proximo = aux->proximo;   // SALVA primeiro
          aux->proximo = novo;             // LIGA depois

REMOVER:  removido = aux->proximo;         // SALVA quem vai sair
          aux->proximo = removido->proximo; // PULA o removido
```

**Sempre salve o ponteiro antes de sobrescrevê-lo!**
