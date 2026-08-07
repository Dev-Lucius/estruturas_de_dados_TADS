# 📚 Estrutura de Dados

> Repositório de estudos e implementações da disciplina de **Estrutura de Dados**, cobrindo Tipos Abstratos de Dados, algoritmos de ordenação e pesquisa, árvores, grafos e análise de complexidade.

[![C](https://img.shields.io/badge/C-11-blue.svg)](https://en.wikipedia.org/wiki/C11_(C_standard_revision))
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

---

## 📋 Índice

- [Sobre a Disciplina](#-sobre-a-disciplina)
- [Estrutura do Repositório](#-estrutura-do-repositório)
- [Tipos Abstratos de Dados (TADs)](#-tipos-abstratos-de-dados-tads)
  - [Arranjos (Arrays)](#arranjos-arrays)
  - [Pilhas (Stacks)](#pilhas-stacks)
  - [Filas (Queues)](#filas-queues)
  - [Listas Encadeadas](#listas-encadeadas)
  - [Tabelas de Dispersão (Hash Tables)](#tabelas-de-dispersão-hash-tables)
- [Ordenação e Pesquisa](#-ordenação-e-pesquisa)
  - [Métodos de Ordenação](#métodos-de-ordenação)
  - [Métodos de Pesquisa](#métodos-de-pesquisa)
- [Árvores](#-árvores)
- [Grafos](#-grafos)
- [Complexidade de Algoritmos](#-complexidade-de-algoritmos)
- [Como Compilar e Executar](#-como-compilar-e-executar)
- [Referências](#-referências)

---

## 🎓 Sobre a Disciplina

Esta disciplina tem como objetivo apresentar as estruturas de dados fundamentais para a organização e manipulação eficiente de informações em memória, bem como os algoritmos clássicos de ordenação, pesquisa e travessia. O foco está na compreensão da complexidade computacional e na escolha adequada de estruturas para cada problema.

**Ementa:**
> Tipos Abstratos de Dados: arranjos, pilhas, filas, listas e tabelas de dispersão. Métodos de ordenação e pesquisa. Noções de árvores, grafos e de complexidade de algoritmos.

---

## 📁 Estrutura do Repositório

```
estrutura-de-dados/
├── README.md
├── LICENSE
├── Makefile
├── docs/
│   └── notas-de-aula.md
├── src/
│   ├── tad/
│   │   ├── arranjo.c / arranjo.h
│   │   ├── pilha.c / pilha.h
│   │   ├── fila.c / fila.h
│   │   ├── lista_encadeada.c / lista_encadeada.h
│   │   └── tabela_dispersao.c / tabela_dispersao.h
│   ├── ordenacao/
│   │   ├── bubble_sort.c
│   │   ├── selection_sort.c
│   │   ├── insertion_sort.c
│   │   ├── merge_sort.c
│   │   ├── quick_sort.c
│   │   └── heap_sort.c
│   ├── pesquisa/
│   │   ├── busca_linear.c
│   │   └── busca_binaria.c
│   ├── arvores/
│   │   ├── arvore_binaria.c / arvore_binaria.h
│   │   ├── arvore_binaria_busca.c / arvore_binaria_busca.h
│   │   ├── arvore_avl.c / arvore_avl.h
│   │   └── heap.c / heap.h
│   └── grafos/
│       ├── grafo_matriz.c / grafo_matriz.h
│       ├── grafo_lista.c / grafo_lista.h
│       └── algoritmos_grafo.c
├── tests/
│   └── testes_unitarios.c
└── main.c
```

---

## 🧱 Tipos Abstratos de Dados (TADs)

Um **Tipo Abstrato de Dado (TAD)** define um modelo matemático junto com as operações que podem ser realizadas sobre ele, sem especificar a implementação interna. A interface é exposta via arquivo de cabeçalho (`.h`) e a implementação fica no arquivo fonte (`.c`).

### Arranjos (Arrays)

Estrutura linear de tamanho fixo onde os elementos são armazenados em posições contíguas de memória.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Acesso por índice | **O(1)** | Acesso direto via offset |
| Busca linear | **O(n)** | Percorre sequencialmente |
| Inserção no fim | **O(1)** | Se houver espaço |
| Inserção no início/meio | **O(n)** | Requer deslocamento dos elementos |
| Remoção | **O(n)** | Requer deslocamento |

**Conceitos-chave:**
- Índices iniciam em `0`
- Aritmética de ponteiros: `arr[i] ≡ *(arr + i)`
- Arrays multidimensionais: `matriz[i][j] ≡ *(*(matriz + i) + j)`
- Alocação dinâmica de arrays: `malloc(n * sizeof(tipo))`

---

### Pilhas (Stacks)

Estrutura **LIFO** (*Last In, First Out*). O último elemento inserido é o primeiro a ser removido.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| `push` (empilhar) | **O(1)** | Adiciona no topo |
| `pop` (desempilhar) | **O(1)** | Remove do topo |
| `peek` (topo) | **O(1)** | Consulta o topo sem remover |
| `isEmpty` | **O(1)** | Verifica se está vazia |

**Implementações:**
- **Array estático:** tamanho fixo, índice `topo`
- **Lista encadeada:** nó cabeça como topo, sem limite de tamanho

**Aplicações:**
- Avaliação de expressões (notação polonesa reversa)
- Gerenciamento de chamadas de função (call stack)
- Desfazer/refazer (*undo/redo*)
- Backtracking em algoritmos

---

### Filas (Queues)

Estrutura **FIFO** (*First In, First Out*). O primeiro elemento inserido é o primeiro a ser removido.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| `enqueue` (enfileirar) | **O(1)** | Adiciona no final |
| `dequeue` (desenfileirar) | **O(1)** | Remove do início |
| `front` (frente) | **O(1)** | Consulta o primeiro |
| `isEmpty` | **O(1)** | Verifica se está vazia |

**Variantes:**
- **Fila circular:** reaproveita espaços liberados no início do array
- **Fila de prioridade:** elementos possuem prioridade, não ordem de chegada
- **Deque** (*Double-Ended Queue*): inserção e remoção em ambas as extremidades

**Aplicações:**
- Escalonamento de processos (CPU scheduling)
- Buffer de impressão
- BFS (*Breadth-First Search*) em grafos
- Sistemas de atendimento

---

### Listas Encadeadas

Coleção de nós onde cada nó contém um dado e um ponteiro para o próximo nó. Não exige memória contígua.

| Operação | Lista Simples | Lista Dupla | Descrição |
|----------|--------------|-------------|-----------|
| Inserção no início | **O(1)** | **O(1)** | Atualiza o ponteiro cabeça |
| Inserção no fim | **O(n)**¹ | **O(1)** | ¹O(1) se houver ponteiro cauda |
| Inserção no meio | **O(n)** | **O(n)** | Requer busca pela posição |
| Remoção no início | **O(1)** | **O(1)** | |
| Remoção no fim | **O(n)** | **O(1)** | |
| Busca | **O(n)** | **O(n)** | Percorrimento sequencial |
| Acesso por índice | **O(n)** | **O(n)** | Não há acesso direto |

**Tipos:**
- **Simplesmente encadeada:** cada nó aponta apenas para o próximo
- **Duplamente encadeada:** cada nó aponta para o anterior e o próximo
- **Circular:** o último nó aponta para o primeiro (ou o anterior, na dupla)

**Vantagens sobre arrays:**
- Tamanho dinâmico
- Inserção/remoção eficiente sem deslocamento

**Desvantagens:**
- Acesso sequencial (sem índice direto)
- Overhead de memória para ponteiros

---

### Tabelas de Dispersão (Hash Tables)

Estrutura que mapeia chaves para valores usando uma **função hash** para determinar o índice de armazenamento.

| Operação | Caso Médio | Pior Caso | Descrição |
|----------|-----------|-----------|-----------|
| Inserção | **O(1)** | **O(n)** | Colisões degradam para O(n) |
| Busca | **O(1)** | **O(n)** | |
| Remoção | **O(1)** | **O(n)** | |

**Conceitos-chave:**
- **Função hash:** converte a chave em um índice do array (`hash(key) % tamanho`)
- **Colisão:** quando duas chaves geram o mesmo índice
- **Fator de carga (α):** `n / m` (n = elementos, m = slots). Recomenda-se α < 0.75

**Tratamento de colisões:**
- **Encadeamento separado (*Separate Chaining*):** cada slot é uma lista encadeada de colisões
- **Endereçamento aberto (*Open Addressing*):**
  - *Linear Probing:* `h(k, i) = (h'(k) + i) % m`
  - *Quadratic Probing:* `h(k, i) = (h'(k) + c₁i + c₂i²) % m`
  - *Double Hashing:* `h(k, i) = (h₁(k) + i·h₂(k)) % m`

**Funções hash comuns:**
- Divisão: `h(k) = k % m` (m deve ser primo)
- Multiplicação: `h(k) = ⌊m · (kA mod 1)⌋`
- DJB2, FNV-1a (para strings)

---

## 🔀 Ordenação e Pesquisa

### Métodos de Ordenação

| Algoritmo | Melhor | Médio | Pior | Estável? | Espaço | Descrição |
|-----------|--------|-------|------|----------|--------|-----------|
| **Bubble Sort** | O(n) | O(n²) | O(n²) | ✅ Sim | O(1) | Compara adjacentes, "borbulha" o maior para o fim |
| **Selection Sort** | O(n²) | O(n²) | O(n²) | ❌ Não | O(1) | Seleciona o menor e troca com a posição atual |
| **Insertion Sort** | O(n) | O(n²) | O(n²) | ✅ Sim | O(1) | Insere cada elemento na posição correta |
| **Merge Sort** | O(n log n) | O(n log n) | O(n log n) | ✅ Sim | O(n) | Divisão e conquista; merge de subarrays ordenados |
| **Quick Sort** | O(n log n) | O(n log n) | O(n²) | ❌ Não | O(log n) | Particiona em torno de um pivô; recursão |
| **Heap Sort** | O(n log n) | O(n log n) | O(n log n) | ❌ Não | O(1) | Usa heap máxima; extrai o maior repetidamente |
| **Counting Sort** | O(n+k) | O(n+k) | O(n+k) | ✅ Sim | O(k) | Contagem de frequências (inteiros pequenos) |
| **Radix Sort** | O(d·(n+k)) | O(d·(n+k)) | O(d·(n+k)) | ✅ Sim | O(n+k) | Ordenação dígito a dígito (LSD/MSD) |

**Notas:**
- **Estável:** mantém a ordem relativa de elementos iguais
- **In-place:** não requer memória extra significativa
- **Quick Sort** é geralmente o mais rápido na prática, apesar do pior caso O(n²)
- **Merge Sort** é preferido para listas encadeadas e dados externos

---

### Métodos de Pesquisa

| Algoritmo | Complexidade | Pré-requisito | Descrição |
|-----------|-------------|---------------|-----------|
| **Busca Linear** | O(n) | Nenhum | Percorre sequencialmente |
| **Busca Linear Ordenada** | O(n) | Ordenado | Para ao encontrar valor maior que o alvo |
| **Busca Binária** | O(log n) | Ordenado | Divide o espaço de busca pela metade |
| **Busca por Interpolação** | O(log log n) | Ordenado + distribuição uniforme | Estima a posição via interpolação |
| **Busca em Árvore BST** | O(h) | Árvore balanceada: O(log n) | Percorre a árvore de busca |
| **Busca em Hash** | O(1) médio | Tabela hash | Acesso direto via função hash |

**Busca Binária — Implementação iterativa:**
```c
int busca_binaria(int arr[], int n, int alvo) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;  // evita overflow
        if (arr[meio] == alvo) return meio;
        if (arr[meio] < alvo) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;  // não encontrado
}
```

---

## 🌳 Árvores

Estruturas hierárquicas onde cada nó possui zero ou mais filhos, com exatamente um nó raiz.

### Árvore Binária

Cada nó possui no máximo dois filhos: **esquerdo** e **direito**.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Travessia (qualquer) | **O(n)** | Visita todos os nós |
| Altura | **O(n)** | Caminho mais longo raiz-folha |

**Travessias:**
- **Pré-ordem (Pre-order):** Raiz → Esquerda → Direita
- **Em-ordem (In-order):** Esquerda → Raiz → Direita *(resultado ordenado em BST)*
- **Pós-ordem (Post-order):** Esquerda → Direita → Raiz
- **Nível (Level-order):** BFS usando fila

### Árvore Binária de Busca (BST)

Propriedade: para todo nó, os valores da subárvore esquerda são menores e da direita são maiores.

| Operação | Médio | Pior Caso | Descrição |
|----------|-------|-----------|-----------|
| Inserção | O(log n) | O(n) | Desbalanceada vira lista |
| Busca | O(log n) | O(n) | |
| Remoção | O(log n) | O(n) | 3 casos: folha, 1 filho, 2 filhos |

### Árvore AVL

BST **auto-balanceada**. Para todo nó, a diferença de altura entre subárvores (fator de balanceamento) é no máximo 1.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Inserção | **O(log n)** | Requer rotações para rebalancear |
| Busca | **O(log n)** | |
| Remoção | **O(log n)** | |

**Rotações:**
- Rotação simples à direita (LL)
- Rotação simples à esquerda (RR)
- Rotação dupla esquerda-direita (LR)
- Rotação dupla direita-esquerda (RL)

### Heap (Fila de Prioridade)

Árvore binária completa armazenada em array.

| Operação | Complexidade | Descrição |
|----------|-------------|-----------|
| Inserção | **O(log n)** | Sobe o elemento (*sift up*) |
| Remoção do topo | **O(log n)** | Remove raiz, desce último (*sift down*) |
| Consulta do topo | **O(1)** | Raiz do heap |
| Construção (heapify) | **O(n)** | Bottom-up |

**Tipos:**
- **Max-Heap:** pai ≥ filhos (raiz é o maior)
- **Min-Heap:** pai ≤ filhos (raiz é o menor)

**Relações em array (índice i):**
- Pai: `(i - 1) / 2`
- Filho esquerdo: `2i + 1`
- Filho direito: `2i + 2`

---

## 🕸️ Grafos

Conjunto de **vértices (nós)** e **arestas** que os conectam. Podem ser **direcionados** ou **não-direcionados**, **ponderados** ou **não-ponderados**.

### Representações

| Representação | Espaço | Verificar adjacência | Listar adjacentes |
|---------------|--------|---------------------|-------------------|
| **Matriz de Adjacência** | O(V²) | O(1) | O(V) |
| **Lista de Adjacência** | O(V + E) | O(degree(v)) | O(degree(v)) |
| **Matriz de Incidência** | O(V·E) | O(E) | O(E) |

**Recomendação:**
- Matriz: grafos densos (E ≈ V²)
- Lista: grafos esparsos (E << V²)

### Algoritmos de Travessia

| Algoritmo | Complexidade | Estrutura Auxiliar | Descrição |
|-----------|-------------|-------------------|-----------|
| **BFS** | O(V + E) | Fila | Explora nível por nível a partir da fonte |
| **DFS** | O(V + E) | Pilha (ou recursão) | Explora o mais fundo possível antes de retroceder |

**Aplicações:**
- BFS: menor caminho em grafos não ponderados, conectividade
- DFS: detecção de ciclos, ordenação topológica, componentes fortemente conexas

### Algoritmos de Caminho Mínimo

| Algoritmo | Complexidade | Tipo de Grafo | Descrição |
|-----------|-------------|---------------|-----------|
| **Dijkstra** | O((V+E) log V) com heap | Ponderado, arestas ≥ 0 | Relaxação greedy a partir da fonte |
| **Bellman-Ford** | O(V·E) | Ponderado (permite negativos) | Relaxação V-1 vezes; detecta ciclos negativos |
| **Floyd-Warshall** | O(V³) | Ponderado (todos os pares) | Programação dinâmica; matriz de distâncias |

### Algoritmos de Árvore Geradora Mínima (MST)

| Algoritmo | Complexidade | Descrição |
|-----------|-------------|-----------|
| **Kruskal** | O(E log E) | Ordena arestas por peso; Union-Find para evitar ciclos |
| **Prim** | O((V+E) log V) com heap | Expande a MST a partir de um vértice inicial |

### Outros Conceitos

- **Grau de um vértice:** número de arestas incidentes
- **Caminho:** sequência de vértices conectados por arestas
- **Ciclo:** caminho que começa e termina no mesmo vértice
- **Grafo conexo:** existe caminho entre quaisquer dois vértices
- **Componente conexa:** subgrafo maximal conexo
- **Ordenação topológica:** ordenação linear de vértices em DAG (grafo acíclico direcionado)

---

## ⏱️ Complexidade de Algoritmos

A **análise de complexidade** mede como o tempo de execução ou o espaço em memória de um algoritmo cresce em relação ao tamanho da entrada `n`.

### Notação Assintótica

| Notação | Nome | Significado |
|---------|------|-------------|
| **O(f(n))** | Big-O | Limite superior (pior caso) |
| **Ω(f(n))** | Big-Omega | Limite inferior (melhor caso) |
| **Θ(f(n))** | Big-Theta | Limite apertado (médio e pior coincidem) |

### Classes de Complexidade Comuns

| Complexidade | Nome | Exemplo |
|-------------|------|---------|
| O(1) | Constante | Acesso a array por índice |
| O(log n) | Logarítmica | Busca binária, operações em BST balanceada |
| O(n) | Linear | Busca linear, travessia de array |
| O(n log n) | Linearítmica | Merge Sort, Quick Sort médio, Heap Sort |
| O(n²) | Quadrática | Bubble Sort, Selection Sort, Insertion Sort |
| O(n³) | Cúbica | Floyd-Warshall |
| O(2ⁿ) | Exponencial | Subconjuntos (força bruta) |
| O(n!) | Fatorial | Permutações (caixeiro viajante força bruta) |

### Regras de Simplificação

1. **Descarte constantes:** O(2n) = **O(n)**
2. **Descarte termos de menor ordem:** O(n² + n) = **O(n²)**
3. **Multiplicação de loops aninhados:** loop O(n) dentro de loop O(n) = **O(n²)**

### Análise de Recorrências

**Método Mestre (Master Theorem):**

Para recorrências da forma `T(n) = a·T(n/b) + f(n)`:

| Caso | Condição | Resultado |
|------|----------|-----------|
| 1 | f(n) = O(n^(log_b(a) - ε)) | T(n) = Θ(n^(log_b(a))) |
| 2 | f(n) = Θ(n^(log_b(a))) | T(n) = Θ(n^(log_b(a)) · log n) |
| 3 | f(n) = Ω(n^(log_b(a) + ε)) e af(n/b) ≤ cf(n) | T(n) = Θ(f(n)) |

**Exemplo:** Merge Sort → `T(n) = 2T(n/2) + O(n)` → Caso 2 → **Θ(n log n)**

---

## 🛠️ Como Compilar e Executar

### Requisitos
- GCC (GNU Compiler Collection) ou Clang
- Make (opcional, para usar o Makefile)

### Compilação Manual

```bash
# Compilar um arquivo específico
gcc src/tad/pilha.c -o bin/pilha -Wall -Wextra -std=c11

# Compilar o projeto completo
gcc src/**/*.c main.c -o bin/main -Wall -Wextra -std=c11

# Compilar com suporte a matemática (math.h)
gcc programa.c -o programa -lm

# Compilar com símbolos de debug
gcc programa.c -o programa -g

# Compilar otimizado
gcc programa.c -o programa -O2
```

### Usando Make

```bash
make all      # compila todo o projeto
make clean    # remove arquivos objeto e binários
make test     # executa testes unitários
make run      # compila e executa
```

### Executar

```bash
./bin/main
```

### Flags Recomendadas

| Flag | Descrição |
|------|-----------|
| `-Wall` | Ativa avisos comuns |
| `-Wextra` | Ativa avisos extras |
| `-Werror` | Trata avisos como erros |
| `-std=c11` | Padrão C11 |
| `-g` | Símbolos de debug (para gdb/valgrind) |
| `-O2` | Otimização nível 2 |
| `-lm` | Linka a biblioteca matemática |

### Debug e Análise

```bash
# Valgrind - detecta vazamentos de memória
valgrind --leak-check=full ./bin/main

# GDB - debugger
gdb ./bin/main

# Análise estática (cppcheck)
cppcheck --enable=all src/
```

---

## 📖 Referências

### Livros
- **Cormen, T. H.** et al. *Introduction to Algorithms* (CLRS). 4ª ed. MIT Press, 2022.
- **Sedgewick, R.** & Wayne, K. *Algorithms*. 4ª ed. Addison-Wesley, 2011.
- **Tenenbaum, A. M.** et al. *Estruturas de Dados Usando C*. Pearson, 1995.
- **Celes, W.** et al. *Introdução a Estruturas de Dados*. Elsevier, 2004.
- **Kernighan, B. W.** & Ritchie, D. M. *The C Programming Language*. 2ª ed. Prentice Hall, 1988.

### Recursos Online
- [VisuAlgo](https://visualgo.net/) — Visualização interativa de algoritmos
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/) — Tabela de complexidades
- [GeeksforGeeks - Data Structures](https://www.geeksforgeeks.org/data-structures/)
- [MIT OpenCourseWare - Introduction to Algorithms](https://ocw.mit.edu/courses/6-006-introduction-to-algorithms-fall-2011/)

---

## 📝 Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

---

> 💡 **Dica:** Use este repositório como referência prática. Implemente cada estrutura do zero pelo menos uma vez — é a melhor forma de fixar o conteúdo para provas e projetos!
