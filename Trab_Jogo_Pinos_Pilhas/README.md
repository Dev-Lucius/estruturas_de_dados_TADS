# Jogo de Pinos com Pilhas
## Trabalho de Estruturas de Dados

- **Linguagem:** C
- **Estrutura de dados:** Pilhas Dinâmicas Encadeadas
- **Disciplina:** Estruturas de Dados
- **Data:** 17/11/2026

---

# 1. Introdução

## 1.1 Objetivo do projeto

Desenvolver um jogo de organização de pinos utilizando
a estrutura de dados Pilha, implementada por meio de
listas simplesmente encadeadas.

O jogador deverá movimentar os pinos entre as pilhas
até organizar todas as cores corretamente.

## 1.2 Objetivos de aprendizagem

- Aplicar o conceito de pilha (LIFO).
- Trabalhar com ponteiros e alocação dinâmica.
- Implementar operações de inserção e remoção.
- Desenvolver funções de validação.
- Aplicar modularização em linguagem C.

---

# 2. Regras do jogo

## 2.1 Componentes

- 12 pinos.
- 4 cores diferentes.
- 3 pinos de cada cor.
- 4 pilhas principais.
- 2 pilhas temporárias.
- Capacidade de 4 elementos nas pilhas principais.
- Capacidade de 1 elemento nas temporárias.

## 2.2 Objetivo

Organizar os pinos de maneira que cada pilha principal
contenha exclusivamente pinos de uma mesma cor.

As pilhas temporárias devem estar vazias ao final.

## 2.3 Níveis de dificuldade

| Nível | Pilhas temporárias disponíveis |
|---|---:|
| Fácil | 2 |
| Médio | 1 |
| Difícil | 0 |

---

# 3. Estrutura de dados

## 3.1 Conceito de pilha

Uma pilha segue o princípio LIFO:

**Last In, First Out**
(Último a entrar, primeiro a sair).

As principais operações são:

- `push()`: insere um elemento.
- `pop()`: remove o elemento do topo.
- `vazia()`: verifica se a pilha está vazia.
- `cheia()`: verifica se a pilha atingiu sua capacidade.

## 3.2 Implementação com lista encadeada

Explicar as estruturas:

- `Cor`: enumeração das cores.
- `Pino`: representa cada nó da lista.
- `Pilha`: controla o topo, tamanho e capacidade.
- `Jogo`: mantém as pilhas e os dados da partida.

**Demonstração no código:** estruturas `Cor`, `Pino`, `Pilha` e `Jogo`.

---

# 4. Organização e implementação

## 4.1 Criação e inicialização

Funções:

- `criarPino()`
- `criarPilha()`
- `inicializarJogo()`

**Demonstração no código:** alocação dinâmica com `malloc()`,
inicialização dos ponteiros e configuração das capacidades.

## 4.2 Distribuição dos pinos

Funções:

- `embaralhar()`
- `distribuirPinos()`

**Demonstração no código:** vetor de cores, algoritmo
Fisher-Yates e distribuição dos pinos entre as pilhas.

## 4.3 Operações com pilhas

Funções:

- `push()`
- `pop()`
- `vazia()`
- `cheia()`

**Demonstração no código:** inserção e remoção de nós,
atualização do topo e controle do tamanho.

## 4.4 Movimentação dos pinos

Funções:

- `pilhaDisponivel()`
- `validarMovimento()`
- `moverPino()`

**Demonstração no código:** validação da origem e destino,
remoção do pino, inserção na nova pilha e atualização
do contador de movimentos.

## 4.5 Condição de vitória

Funções:

- `pilha_uma_cor()`
- `validarVitoria()`

**Demonstração no código:** verificação das cores,
quantidade de elementos e estado das pilhas temporárias.

---

# 5. Fluxo de execução

## 5.1 Inicialização da partida

1. Inicialização do gerador aleatório.
2. Escolha da dificuldade.
3. Criação das pilhas.
4. Criação e embaralhamento dos pinos.
5. Distribuição inicial.

## 5.2 Execução da partida

1. Exibição do tabuleiro.
2. Apresentação do menu.
3. Recebimento da escolha do jogador.
4. Validação do movimento.
5. Execução da movimentação.
6. Atualização do contador.
7. Verificação da vitória.

**Demonstração no código:** função `executarJogo()`.

## 5.3 Controle da partida

- Contagem de movimentos.
- Medição do tempo com `time()`.
- Exibição das estatísticas finais.

---

# 6. Gerenciamento de memória

## 6.1 Alocação dinâmica

Utilização de `malloc()` para criar pilhas e pinos
durante a execução.

## 6.2 Liberação de memória

- Remoção e liberação dos nós.
- Esvaziamento das pilhas.
- Liberação das estruturas.
- Prevenção de vazamentos de memória.

**Demonstração no código:** `liberarPilha()` e limpeza final.

---

# 7. Demonstração prática

Executar o programa no terminal:

1. Escolher a dificuldade.
2. Observar a distribuição aleatória.
3. Realizar movimentações.
4. Demonstrar uma movimentação inválida.
5. Demonstrar a atualização do contador.
6. Demonstrar a condição de vitória.

---

# 8. Conclusão

O desenvolvimento do projeto permitiu aplicar conceitos
fundamentais de estruturas de dados e programação em C.

Principais conhecimentos aplicados:

- Pilhas dinâmicas encadeadas.
- Ponteiros e listas simplesmente encadeadas.
- Alocação e liberação dinâmica de memória.
- Modularização.
- Validação de operações.
- Controle de fluxo e lógica de jogo.


