# Jogo de Pinos com Pilhas

## Trabalho de Estruturas de Dados

**Linguagem:** C  
**Estrutura de dados:** Pilhas Dinâmicas Encadeadas  
**Disciplina:** Estruturas de Dados  
**Data da apresentação:** 17/11/2026

---

# 1. Introdução

## 1.1 Apresentação do projeto

O projeto consiste no desenvolvimento de um jogo de organização de pinos utilizando a linguagem de programação C e a estrutura de dados Pilha.

O jogador deverá movimentar pinos entre diferentes pilhas, respeitando as regras de movimentação e as limitações de capacidade, até alcançar a organização final de todas as cores.

A implementação utiliza pilhas dinâmicas encadeadas, permitindo trabalhar diretamente com ponteiros, alocação dinâmica de memória e manipulação de estruturas de dados.

## 1.2 Objetivos do projeto

O principal objetivo é aplicar, na prática, os conceitos estudados em Estruturas de Dados.

Durante o desenvolvimento, foram trabalhados:

- Implementação de pilhas utilizando listas simplesmente encadeadas.
- Manipulação de ponteiros e nós.
- Alocação e liberação dinâmica de memória.
- Implementação das operações de inserção e remoção.
- Validação de operações e regras do jogo.
- Modularização por meio de funções.
- Controle de execução e gerenciamento da partida.

---

# 2. Regras do jogo

## 2.1 Componentes

O jogo é composto por:

- **12 pinos:** divididos em quatro cores diferentes.
- **4 pilhas principais:** identificadas como P1, P2, P3 e P4.
- **2 pilhas temporárias:** identificadas como T1 e T2.

Cada cor possui exatamente três pinos.

| Elemento | Quantidade | Capacidade |
|---|---:|---:|
| Pinos | 12 | — |
| Pilhas principais | 4 | 4 pinos |
| Pilhas temporárias | 2 | 1 pino |

Inicialmente, cada pilha principal recebe três pinos em ordem aleatória, deixando um espaço disponível em cada uma.

As pilhas temporárias começam vazias.

## 2.2 Objetivo

O objetivo é organizar os 12 pinos de maneira que cada pilha principal contenha exclusivamente três pinos de uma mesma cor.

Ao final da partida:

- Cada pilha principal deverá conter três pinos.
- Os três pinos de cada pilha deverão possuir a mesma cor.
- Cada uma das quatro cores deverá estar representada em uma pilha diferente.
- As pilhas temporárias deverão estar vazias.

## 2.3 Níveis de dificuldade

O jogo possui três níveis de dificuldade, que determinam a quantidade de pilhas temporárias disponíveis.

| Dificuldade | Temporários disponíveis |
|---|---:|
| Fácil | 2 |
| Médio | 1 |
| Difícil | 0 |

A redução da quantidade de pilhas temporárias aumenta a dificuldade de organização, pois limita as possibilidades de movimentação dos pinos.

## 2.4 Regras de movimentação

Para realizar uma movimentação, o jogador deverá selecionar uma pilha de origem e uma pilha de destino.

As regras são:

1. A pilha de origem não pode estar vazia.
2. A pilha de destino não pode estar cheia.
3. A origem e o destino devem ser diferentes.
4. Somente um pino pode ser movimentado por vez.
5. As pilhas temporárias respeitam a capacidade de um único pino.
6. Não é permitido utilizar pilhas temporárias indisponíveis no nível escolhido.

O jogo também valida as movimentações antes de executá-las, impedindo operações inválidas.

---

# 3. Estrutura de dados utilizada

## 3.1 Conceito de pilha

Uma pilha é uma estrutura de dados linear que segue o princípio **LIFO (Last In, First Out)**, que significa "último a entrar, primeiro a sair".

Isso significa que o último elemento inserido será o primeiro elemento removido.

As operações acontecem em uma única extremidade da estrutura, chamada de topo.

As principais operações de uma pilha são:

- `push()`: insere um elemento no topo.
- `pop()`: remove o elemento que está no topo.
- `vazia()`: verifica se a pilha está vazia.
- `cheia()`: verifica se a pilha atingiu sua capacidade máxima.

No jogo, essa característica determina que somente o pino localizado no topo de cada pilha pode ser movimentado.

## 3.2 Implementação com lista simplesmente encadeada

Neste projeto, as pilhas foram implementadas utilizando listas simplesmente encadeadas.

Uma lista encadeada é formada por nós que armazenam informações e referências para outros nós.

Cada nó possui:

- Um campo com os dados do elemento.
- Um ponteiro que aponta para o próximo nó.

Diferentemente de um vetor convencional, os elementos não precisam ocupar posições consecutivas na memória.

Essa implementação permite alocar e liberar memória dinamicamente conforme a necessidade do programa.

## 3.3 Representação de um pino

A estrutura `Pino` representa cada elemento armazenado nas pilhas.

```c
typedef struct Pino {
    Cor cor;
    struct Pino *prox;
} Pino;
```

Seus atributos são:

- `cor`: armazena a cor do pino.
- `prox`: aponta para o próximo nó da pilha.

O campo `prox` permite conectar os pinos uns aos outros, formando uma lista encadeada.

**Demonstração no código:** apresentar a estrutura `Pino` e explicar o funcionamento do ponteiro `prox`.

## 3.4 Representação de uma pilha

A estrutura `Pilha` controla os elementos armazenados.

```c
typedef struct {
    Pino *topo;
    int tamanho;
    int capacidade;
} Pilha;
```

Seus atributos são:

- `topo`: aponta para o primeiro nó da pilha, ou seja, o elemento que será removido primeiro.
- `tamanho`: informa quantos pinos estão armazenados.
- `capacidade`: define a quantidade máxima de pinos permitida.

O ponteiro `topo` é fundamental para as operações de inserção e remoção.

O atributo `tamanho` permite acompanhar a ocupação atual da pilha, enquanto `capacidade` controla seu limite.

**Demonstração no código:** apresentar a estrutura `Pilha` e explicar a relação entre o topo, o tamanho e a capacidade.

## 3.5 Representação do jogo

A estrutura `Jogo` reúne as informações necessárias para controlar a partida.

```c
typedef struct {
    Pilha *slots[NUM_PILHAS + NUM_TEMPS];
    int temps_ativos;
    int movimentos;
    time_t inicio;
} Jogo;
```

Seus atributos são:

- `slots`: vetor que armazena os ponteiros para as quatro pilhas principais e as duas temporárias.
- `temps_ativos`: controla quantas pilhas temporárias estão disponíveis conforme a dificuldade.
- `movimentos`: contabiliza as movimentações realizadas.
- `inicio`: armazena o horário de início da partida.

O vetor `slots` centraliza o acesso às pilhas, permitindo identificar cada uma por meio de um índice.

As pilhas principais ocupam os índices de 0 a 3, enquanto as temporárias ocupam os índices 4 e 5.

**Demonstração no código:** apresentar a estrutura `Jogo` e explicar como ela reúne e controla as pilhas da partida.

## 3.6 Resumo da organização das estruturas

A organização da estrutura de dados pode ser compreendida da seguinte maneira:

```text
JOGO
 |
 +-- slots[0] --> PILHA P1
 |                  |
 |                  +--> Pino --> Pino --> Pino --> NULL
 |
 +-- slots[1] --> PILHA P2
 |                  |
 |                  +--> Pino --> Pino --> Pino --> NULL
 |
 +-- slots[2] --> PILHA P3
 |
 +-- slots[3] --> PILHA P4
 |
 +-- slots[4] --> PILHA T1
 |
 +-- slots[5] --> PILHA T2
```

Cada posição do vetor `slots` aponta para uma estrutura `Pilha`, que por sua vez controla uma sequência de nós `Pino`.

Essa organização permite que o jogo manipule diferentes pilhas de forma independente, mantendo todas elas centralizadas na estrutura `Jogo`.

---

# 4. Organização e implementação

A implementação foi dividida em funções, cada uma responsável por uma parte específica do funcionamento do jogo.

Essa organização facilita a manutenção do código, evita a repetição de lógica e permite separar as operações sobre as pilhas das regras da partida.

## 4.1 Criação e inicialização

A primeira etapa consiste em criar os elementos que serão utilizados durante a partida.

Para isso, foram desenvolvidas as funções:

- `criarPino()`
- `criarPilha()`
- `inicializarJogo()`

### `criarPino()`

Responsável por alocar dinamicamente um novo nó do tipo `Pino`.

O nó recebe uma cor e tem seu ponteiro `prox` inicializado adequadamente.

### `criarPilha()`

Responsável por criar uma estrutura do tipo `Pilha`.

A função inicializa o topo como `NULL`, define o tamanho inicial como zero e configura a capacidade máxima recebida.

### `inicializarJogo()`

Responsável por preparar as estruturas necessárias para uma nova partida.

Suas principais responsabilidades são:

- Configurar a quantidade de pilhas temporárias conforme a dificuldade.
- Criar as quatro pilhas principais.
- Criar as duas pilhas temporárias.
- Inicializar o contador de movimentos.
- Registrar o horário de início da partida.

**Demonstração no código:** apresentar `criarPino()`, `criarPilha()` e `inicializarJogo()`, destacando a utilização de `malloc()` e a inicialização dos atributos.

## 4.2 Embaralhamento e distribuição dos pinos

Depois da criação das estruturas, é necessário preparar a configuração inicial do tabuleiro.

Para isso, foram implementadas duas funções:

- `embaralhar()`
- `distribuirPinos()`

### `embaralhar()`

Responsável por alterar aleatoriamente a ordem dos pinos antes da distribuição.

A implementação utiliza o algoritmo **Fisher-Yates**, que realiza trocas entre posições do vetor para produzir uma permutação aleatória.

O objetivo é garantir que as configurações iniciais das partidas sejam diferentes.

### `distribuirPinos()`

Responsável por criar os nós dos pinos e inseri-los nas pilhas principais.

A distribuição é realizada de maneira que:

- Cada pilha principal receba três pinos.
- Os 12 pinos sejam distribuídos entre as quatro pilhas.
- As pilhas temporárias permaneçam vazias no início.

A função utiliza a operação de inserção da pilha para armazenar os elementos.

**Demonstração no código:** apresentar o vetor de cores, a função `embaralhar()` e o processo de distribuição em `distribuirPinos()`.

## 4.3 Operações fundamentais das pilhas

O funcionamento do jogo depende diretamente das operações de inserção e remoção de elementos.

As principais funções implementadas são:

- `vazia()`
- `cheia()`
- `push()`
- `pop()`

### `vazia()`

Verifica se a pilha não possui elementos.

Uma pilha é considerada vazia quando seu ponteiro `topo` é igual a `NULL`.

### `cheia()`

Verifica se a quantidade atual de elementos atingiu a capacidade máxima da pilha.

Essa validação impede que sejam armazenados mais pinos do que o permitido.

### `push()`

Responsável por inserir um novo nó no topo da pilha.

A operação atualiza o ponteiro `topo` e incrementa o atributo `tamanho`.

Antes da inserção, verifica se a pilha e o nó são válidos e se existe espaço disponível.

### `pop()`

Responsável por remover o nó que está no topo da pilha.

A operação atualiza o ponteiro `topo`, decrementa o atributo `tamanho` e retorna o nó removido.

O nó não é liberado automaticamente, pois poderá ser reutilizado em outra pilha durante uma movimentação.

**Demonstração no código:** apresentar `push()` e `pop()`, mostrando como os ponteiros são atualizados durante a inserção e a remoção.

## 4.4 Validação e movimentação dos pinos

A movimentação é uma das partes centrais do projeto.

Para garantir que as regras sejam respeitadas, foram desenvolvidas as funções:

- `validarMovimento()`
- `moverPino()`

### `validarMovimento()`

Responsável por verificar se uma movimentação pode ser realizada.

Entre as condições verificadas estão:

- Existência de uma partida válida.
- Índices de origem e destino dentro dos limites.
- Origem diferente do destino.
- Pilhas inicializadas e disponíveis.
- Origem não vazia.
- Destino com espaço disponível.

A função retorna um resultado que indica se a movimentação pode prosseguir.

### `moverPino()`

Responsável por executar efetivamente a movimentação.

O processo consiste em:

1. Validar a movimentação.
2. Remover o pino do topo da pilha de origem utilizando `pop()`.
3. Inserir o mesmo nó no topo da pilha de destino utilizando `push()`.
4. Incrementar o contador de movimentos somente após uma inserção bem-sucedida.

Caso a inserção no destino falhe depois da remoção, a função tenta devolver o nó à pilha de origem, restaurando o estado anterior.

Essa operação de restauração é conhecida como **rollback**.

**Demonstração no código:** apresentar a relação entre `pilhaDisponivel()`, `validarMovimento()` e `moverPino()`, destacando o uso de `pop()`, `push()` e o controle do contador.

## 4.5 Verificação da condição de vitória

Para identificar quando o jogador concluiu o objetivo, foram desenvolvidas as funções:

- `pilha_uma_cor()`
- `validarVitoria()`

### `pilha_uma_cor()`

Verifica se todos os pinos de uma pilha possuem a mesma cor.

A função percorre os elementos da pilha e compara suas cores.

### `validarVitoria()`

Verifica se o estado atual do jogo corresponde à condição de vitória.

Para isso, verifica:

- Se cada pilha principal contém exatamente três pinos.
- Se todos os pinos de cada pilha possuem a mesma cor.
- Se as pilhas temporárias estão vazias.

Quando todas as condições são satisfeitas, a função indica que o jogador venceu.

**Demonstração no código:** apresentar `pilha_uma_cor()` e `validarVitoria()`, explicando como o programa identifica uma configuração final válida.

## 4.6 Modularização do programa

A divisão das responsabilidades em funções permite que cada parte do jogo seja desenvolvida e testada separadamente.

Por exemplo:

- As funções `push()` e `pop()` cuidam das operações sobre as pilhas.
- `validarMovimento()` verifica as regras antes da movimentação.
- `moverPino()` coordena as operações necessárias para transferir um elemento.
- `validarVitoria()` verifica se o objetivo foi alcançado.
- `executarJogo()` controla a interação com o jogador.

Essa organização torna o programa mais legível, facilita a identificação de problemas e reduz a dependência entre as diferentes partes da implementação.

---

---

# 5. Fluxo de execução

Esta seção apresenta como as diferentes funções do programa trabalham em conjunto para controlar uma partida, desde sua inicialização até o encerramento.

## 5.1 Função principal (`main()`)

A função `main()` é o ponto de entrada do programa e coordena a preparação inicial do jogo.

Suas principais responsabilidades são:

1. Inicializar o gerador de números aleatórios utilizando `srand()`.
2. Exibir o menu de dificuldade.
3. Inicializar as estruturas do jogo.
4. Preparar o vetor com os 12 pinos.
5. Embaralhar a ordem dos pinos.
6. Distribuir os pinos entre as pilhas principais.
7. Iniciar a execução da partida.
8. Liberar a memória utilizada ao final.

**Demonstração no código:** apresentar a função `main()` e explicar como ela coordena as etapas de inicialização e encerramento.

## 5.2 Execução da partida (`executarJogo()`)

A função `executarJogo()` controla a interação entre o jogador e o programa durante toda a partida.

Seu funcionamento é baseado em um laço principal que permanece ativo enquanto o jogador não vencer ou encerrar o jogo.

As principais etapas são:

1. Verificar se a partida foi inicializada corretamente.
2. Verificar se o jogador alcançou a condição de vitória.
3. Exibir o estado atual do tabuleiro.
4. Apresentar o menu de ações.
5. Receber a opção escolhida pelo jogador.
6. Solicitar as pilhas de origem e destino.
7. Executar a validação e a movimentação.
8. Atualizar o estado da partida.

A função também controla as situações de entrada inválida e o encerramento da partida.

**Demonstração no código:** apresentar o laço principal de `executarJogo()` e destacar a integração entre `exibirJogo()`, `validarVitoria()` e `moverPino()`.

## 5.3 Fluxograma de execução


## 5.3 Fluxograma de execução

O fluxo geral do programa é dividido em duas etapas: inicialização e execução da partida.

A execução utiliza um laço principal que se repete até que o jogador vença, escolha encerrar ou a entrada de dados seja finalizada.

```text
                    INÍCIO
                       |
                       v
              Inicializar gerador
                 de números
                       |
                       v
              Exibir menu de
                 dificuldade
                       |
                       v
               Criar estruturas
                  do jogo
                       |
                       v
              Preparar os pinos
                       |
                       v
             Embaralhar os pinos
                       |
                       v
             Distribuir nas pilhas
                       |
                       v
              EXECUTAR JOGO
                       |
                       v
              +----------------+
         +--->| Verificar vitória |
         |    +----------------+
         |             |
         |       +-----+-----+
         |       |           |
         |      Não         Sim
         |       |           |
         |       v           v
         |   Exibir       Exibir
         |   tabuleiro    mensagem
         |       |        de vitória
         |       v           |
         |   Exibir menu     |
         |       |           |
         |       v           |
         |  Receber opção    |
         |       |           |
         |       v           |
         |  Entrada válida? |
         |       |           |
         |   +---+---+       |
         |   |       |       |
         |  Não     Sim      |
         |   |       |       |
         |   v       v       |
         | Repetir  Opção    |
         | leitura  escolhida|
         |           |       |
         |      +----+----+  |
         |      |         |  |
         |     Mover    Encerrar
         |     pino     partida
         |      |         |
         |      v         |
         |   Validar      |
         |   movimento    |
         |      |         |
         |      v         |
         |   Executar     |
         |   movimento    |
         |      |         |
         +------+         |
                          |
                +---------+
                |
                v
        Exibir estatísticas
                |
                v
          Liberar memória
                |
                v
               FIM
```

O retorno ao início do laço representa a repetição da partida após cada movimentação. A condição de vitória é verificada novamente antes da próxima exibição do tabuleiro.

Quando o jogador encerra a partida ou ocorre o fim da entrada de dados, o programa sai do laço e apresenta as estatísticas finais.

---

# 6. Gerenciamento de memória

O gerenciamento de memória é uma parte importante da implementação, pois o projeto utiliza alocação dinâmica para criar as pilhas e os pinos durante a execução.

## 6.1 Alocação dinâmica

A criação dos elementos utiliza a função `malloc()`, disponibilizada pela biblioteca `stdlib.h`.

Com ela, o programa solicita espaço na memória para armazenar:

- As estruturas `Pilha`.
- Os nós `Pino`.

A alocação dinâmica permite que os elementos sejam criados durante a execução, sem a necessidade de reservar antecipadamente um espaço fixo para cada nó.

Após a alocação, os atributos das estruturas são inicializados antes de serem utilizados.

**Demonstração no código:** apresentar as funções `criarPino()` e `criarPilha()`, destacando a utilização de `malloc()`.

## 6.2 Remoção e reutilização dos nós

Durante uma movimentação, a função `pop()` remove o nó do topo da pilha de origem, mas não libera sua memória.

Isso acontece porque o mesmo nó será reutilizado na pilha de destino por meio da função `push()`.

Dessa maneira, o programa transfere o elemento entre as pilhas sem precisar destruir e recriar sua estrutura.

Essa abordagem evita alocações desnecessárias durante a movimentação dos pinos.

## 6.3 Liberação de memória

Ao finalizar a partida, é necessário liberar toda a memória que foi alocada dinamicamente.

Para isso, foi implementada a função `liberarPilha()`.

Suas responsabilidades são:

1. Percorrer os nós armazenados na pilha.
2. Remover cada nó utilizando `pop()`.
3. Liberar a memória de cada nó com `free()`.
4. Liberar a própria estrutura da pilha.

Ao final, todas as pilhas criadas são liberadas, evitando que a memória permaneça ocupada após o encerramento do programa.

**Demonstração no código:** apresentar `liberarPilha()` e o trecho de limpeza final da função `main()`.

## 6.4 Tratamento de falhas de alocação

A alocação dinâmica pode falhar caso não exista memória disponível.

Por isso, as funções responsáveis pela criação das estruturas verificam o retorno de `malloc()` antes de utilizar os ponteiros.

Quando ocorre uma falha durante a inicialização, o programa interrompe o processo e libera as estruturas que já haviam sido criadas.

Esse cuidado evita a utilização de ponteiros inválidos e reduz o risco de vazamentos de memória.

---

# 7. Demonstração prática

Nesta etapa será realizada a execução do programa diretamente no terminal, demonstrando o funcionamento das principais funcionalidades implementadas.

## 7.1 Compilação do programa

Inicialmente, o código será compilado utilizando o compilador GCC.

```bash
gcc -Wall -Wextra -std=c11 -g -fsanitize=address,undefined Game.c -o Game
```

As opções utilizadas são:

- `-Wall`: habilita diversos avisos do compilador.
- `-Wextra`: habilita avisos adicionais.
- `-std=c11`: utiliza o padrão C11.
- `-g`: inclui informações de depuração.
- `-fsanitize=address,undefined`: habilita verificações de problemas de memória e comportamento indefinido.

**Demonstração:** executar a compilação e mostrar que o programa não apresenta erros ou avisos.

## 7.2 Inicialização da partida

Após a compilação, executar o programa:

```bash
./Game
```

Demonstrar:

1. Apresentação inicial do jogo.
2. Escolha do nível de dificuldade.
3. Criação das pilhas.
4. Distribuição aleatória dos pinos.
5. Exibição do tabuleiro inicial.

## 7.3 Movimentação dos pinos

Realizar algumas movimentações para demonstrar o funcionamento das pilhas.

Durante a demonstração:

- Selecionar uma pilha de origem.
- Selecionar uma pilha de destino.
- Observar a remoção do pino do topo.
- Observar sua inserção no destino.
- Verificar a atualização do contador de movimentos.

**Objetivo:** demonstrar na prática o princípio LIFO e as operações `pop()` e `push()`.

## 7.4 Validação de movimentos inválidos

Realizar tentativas de movimentação que violem as regras do jogo.

Exemplos:

- Selecionar uma pilha de origem vazia.
- Selecionar uma pilha de destino cheia.
- Informar a mesma pilha como origem e destino.
- Informar um índice inexistente.
- Tentar utilizar uma pilha temporária indisponível.

**Objetivo:** demonstrar que o programa impede operações inválidas sem comprometer a organização dos elementos.

## 7.5 Encerramento e estatísticas

Finalizar uma partida e demonstrar a apresentação dos resultados.

O programa apresenta:

- Quantidade total de movimentos realizados.
- Tempo total de partida.
- Resultado da partida, indicando vitória ou encerramento sem vitória.

Também demonstrar a liberação das estruturas alocadas dinamicamente.

---

# 8. Conclusão

O desenvolvimento do projeto permitiu aplicar, na prática, conceitos fundamentais de Estruturas de Dados utilizando a linguagem C.

A implementação de pilhas dinâmicas encadeadas proporcionou uma experiência prática com manipulação de ponteiros, listas simplesmente encadeadas e gerenciamento de memória.

Além da implementação das operações fundamentais de uma pilha, o projeto exigiu a criação de mecanismos de validação, controle de movimentações e verificação das condições de vitória.

Entre os principais conhecimentos aplicados, destacam-se:

- Implementação de estruturas de dados dinâmicas.
- Aplicação do princípio LIFO.
- Manipulação de ponteiros e nós encadeados.
- Utilização de alocação e liberação dinâmica de memória.
- Modularização e organização do código.
- Desenvolvimento de algoritmos de validação.
- Integração de diferentes funções para construir uma aplicação funcional.

O projeto demonstra como os conceitos teóricos estudados na disciplina podem ser utilizados na construção de um programa interativo, reforçando a importância das estruturas de dados para o desenvolvimento de software.

---

# 9. Perguntas

**Obrigado pela atenção!**
