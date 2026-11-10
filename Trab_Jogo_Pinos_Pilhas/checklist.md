# Checklist – Atividade Avaliada 3 (Jogo de Pinos com Pilhas em C)

**Apresentação:** 17/11/2026 · **Valor:** 3,0 no 2º bimestre

---

## 0. Antes de começar

- [x] Reler o PDF inteiro e sublinhar os requisitos obrigatórios
- [x] Confirmar com o professor a **condição de vitória** (4 pilhas com 3 pinos da mesma cor cada, temporários vazios?)
- [x] Confirmar se pode usar **vários arquivos** (`.h`/`.c`) ou se precisa ser arquivo único
- [x] Confirmar se a pilha deve seguir o modelo visto em aula (vetor ou encadeada)
- [x] Escolher o compilador/IDE e testar um "Hello World" (`gcc -Wall -Wextra`)
- [x] Criar a pasta do projeto e (opcional) um repositório Git

---

## 1. Structs e constantes

- [x] Definir constantes: `NUM_PILHAS`, `NUM_TEMPS`, `CAP_PILHA`, `PINOS_POR_COR`
- [x] `enum Cor` (com `VAZIO = 0` e as 4 cores)
- [x] `struct Pino` (`cor` + ponteiro `prox`)
- [x] `struct Pilha` (`topo`, `tamanho`, `capacidade`)
- [x] `struct Jogo` (`slots[]`, `temps_ativos`, `movimentos`, `inicio`)
- [ ] Compilar só com as structs, sem erros nem warnings

---

## 2. Operações da pilha

- [ ] `inicializar(Pilha*, int cap)`: `topo = NULL`, `tamanho = 0`
- [ ] `vazia(Pilha*)`
- [ ] `cheia(Pilha*)`
- [ ] `push(Pilha*, Cor)`
  - [ ] Testa se está cheia
  - [ ] Testa se o `malloc` retornou `NULL`
  - [ ] Atualiza `topo` e `tamanho`
- [ ] `pop(Pilha*, Cor*)`
  - [ ] Testa se está vazia
  - [ ] Avança o `topo`, diminui `tamanho`
  - [ ] Dá `free` no nó removido
- [ ] `cor_do_topo(Pilha*)` (retorna `VAZIO` se não há pinos)
- [ ] `cor_na_posicao(Pilha*, int pos)` (0 = base)
- [ ] `pilha_uma_cor(Pilha*)`
- [ ] `liberar_pilha(Pilha*)` (faz `pop` até esvaziar)

### Testes isolados da pilha (numa `main` provisória)

- [ ] Push de 4 pinos em pilha de capacidade 4 → todos aceitos
- [ ] Push do 5º pino → recusado
- [ ] Pop em pilha vazia → recusado
- [ ] Ordem LIFO correta (último a entrar é o primeiro a sair)
- [ ] Pilha de capacidade 1 (temporário) aceita só 1 pino
- [ ] `cor_na_posicao` devolve as cores certas da base ao topo
- [ ] Sem vazamento de memória (testar com `valgrind`, se disponível)

---

## 3. Inicialização do jogo

- [ ] `inicializar_jogo(Jogo*, int nivel)`
  - [ ] Pilhas 0–3 com capacidade 4
  - [ ] Temporários 4–5 com capacidade 1
  - [ ] `temps_ativos` = 2 (fácil), 1 (médio) ou 0 (difícil)
  - [ ] `movimentos = 0` e `inicio = time(NULL)`
- [ ] Chamar `srand(time(NULL))` **uma única vez** no `main`
- [ ] Montar vetor com 12 pinos (3 de cada cor)
- [ ] Embaralhar (Fisher-Yates)
- [ ] Distribuir 3 pinos em cada pilha com `push`
- [ ] Conferir: no início, cada pilha tem 3 pinos e os temporários estão vazios
- [ ] (Opcional) Regerar se o tabuleiro já nascer resolvido

---

## 4. Interface no terminal

- [ ] Função `desenhar_tabuleiro(Jogo*)`
- [ ] Mostrar os temporários **ativos** no topo (e indicar os inativos ou ocultá-los)
- [ ] Desenhar as 4 pilhas de cima para baixo (linha 4 até a 1) usando `cor_na_posicao`
- [ ] Mostrar rótulos P1–P4 e Temp1/Temp2
- [ ] Mostrar tempo decorrido e número de movimentos
- [ ] Mostrar a legenda das cores (letras ou cores ANSI)
- [ ] Limpar a tela entre jogadas (`system("clear")` / `"cls"`)
- [ ] Testar o desenho com pilhas vazias, parciais e cheias

---

## 5. Movimentação e validações

- [ ] Função `mover(Jogo*, int origem, int destino)` única para os 3 tipos de movimento
  - [ ] Pilha → pilha
  - [ ] Pilha → temporário
  - [ ] Temporário → pilha
- [ ] Validar índices dentro do intervalo
- [ ] Validar `origem != destino`
- [ ] Validar que temporários inativos no nível não podem ser usados
- [ ] Validar origem não vazia
- [ ] Validar destino não cheio
- [ ] Incrementar `movimentos` só quando o movimento for válido
- [ ] Retornar códigos de erro distintos para mostrar mensagens claras ao jogador

### Testes de movimento

- [ ] Mover de pilha vazia → erro
- [ ] Mover para pilha cheia → erro
- [ ] Mover para temporário já ocupado → erro
- [ ] Usar Temp2 no nível médio → bloqueado
- [ ] Usar Temp1/Temp2 no nível difícil → bloqueado
- [ ] Movimento válido atualiza o desenho corretamente

---

## 6. Fim de jogo

- [ ] Função `venceu(Jogo*)`
  - [ ] Cada uma das 4 pilhas com 3 pinos
  - [ ] Cada pilha com uma única cor
  - [ ] Temporários vazios
- [ ] Testar com um estado montado à mão, quase pronto
- [ ] Testar que **não** acusa vitória em estados parciais
- [ ] Mensagem de parabéns ao vencer

---

## 7. Tempo e desempenho

- [ ] Guardar `inicio` com `time(NULL)`
- [ ] Calcular tempo com `difftime(time(NULL), inicio)`
- [ ] Mostrar o tempo no tabuleiro durante o jogo
- [ ] Mostrar tempo total e número de movimentos ao final

---

## 8. Menu e laço principal

- [ ] Menu inicial: 1-Fácil, 2-Médio, 3-Difícil, 0-Sair
- [ ] Validar a opção digitada
- [ ] Laço do jogo:
  - [ ] Desenhar
  - [ ] Ler a jogada (`origem destino`)
  - [ ] Chamar `mover()` e tratar erro
  - [ ] Chamar `venceu()`
- [ ] Tratar entrada inválida (letras, buffer sujo) sem travar o programa
- [ ] Opção de desistir/voltar ao menu durante a partida
- [ ] Opção de jogar novamente ao terminar
- [ ] Liberar toda a memória ao encerrar cada partida (`liberar_pilha` em todos os slots)

---

## 9. Qualidade do código

- [ ] Compilar com `-Wall -Wextra` sem warnings
- [ ] Nomes de funções e variáveis claros
- [ ] Comentários curtos explicando cada função
- [ ] Sem número "mágico" no código (usar as constantes)
- [ ] Sem `goto` e sem variáveis globais desnecessárias
- [ ] Código organizado: structs → pilha → jogo → interface → `main`
- [ ] Verificar vazamentos de memória

---

## 10. Testes finais (jogar de verdade)

- [ ] Jogar uma partida completa no nível **fácil**
- [ ] Jogar uma partida completa no nível **médio**
- [ ] Jogar uma partida completa no nível **difícil**
- [ ] Reiniciar várias vezes e conferir que o embaralhamento muda
- [ ] Testar entradas absurdas (`-1`, `99`, `abc`, ENTER vazio)
- [ ] Pedir para alguém jogar sem explicação (se entenderem, a interface está boa)

---

## 11. Preparação da apresentação (17/11)

- [ ] Projeto compilando na máquina que será usada na apresentação
- [ ] Backup do código (pen drive, e-mail ou nuvem)
- [ ] Saber explicar:
  - [ ] Por que a pilha é encadeada e como `topo` funciona
  - [ ] Por que os temporários são pilhas de capacidade 1
  - [ ] Onde ocorrem `push` e `pop` em cada tipo de movimento
  - [ ] Como a função `mover()` valida as jogadas
  - [ ] Como `venceu()` decide o fim do jogo
  - [ ] Como o nível altera o jogo (`temps_ativos`)
  - [ ] Como o tempo é medido
- [ ] Ensaiar a demonstração (uma partida rápida em cada nível)
- [ ] Preparar resposta para "o que aconteceria se...?" (ex.: capacidade da pilha diferente)

---

## 12. Extras (só se sobrar tempo)

- [ ] Desfazer jogada (pilha de histórico)
- [ ] Ranking de melhores tempos por nível
- [ ] Dica automática de movimento
- [ ] Cores ANSI no terminal
- [ ] Separar o código em `pilha.h/.c`, `jogo.h/.c` e `main.c`

---
