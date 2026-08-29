# DataStruct Cine

Sistema de gerenciamento de reservas de cinema desenvolvido em C, utilizando structs e passagem de parâmetros por referência e por valor.

---

## Requisitos do Sistema

1. Reserva de pelo menos quatro sessões de cinema, com filmes diferentes.
2. Gerenciamento da venda de poltronas: uma poltrona não pode ser vendida duas ou mais vezes na mesma sessão.
3. Exibição de todas as poltronas vendidas e livres.
4. Cancelamento de compra de poltrona, desde que o usuário selecione o filme e a poltrona comprada.
5. Menu interativo com as seguintes opções:
   - Compra de poltrona (escolha de sessão, exibição do mapa da sala, escolha da poltrona, exibição do mapa atualizado).
   - Cancelamento de compra de poltrona (liberação da poltrona e exibição do mapa atualizado).
   - Relatório de poltronas por sessão.
   - Visualização de todas as sessões disponíveis.

---

## Estrutura de Dados

O sistema utiliza quatro structs principais:

| Struct      | Descrição                                                              |
|-------------|------------------------------------------------------------------------|
| `Poltrona`  | Representa uma poltrona individual (número, fileira, status livre/ocupado). |
| `Sala`      | Agrupa 15 poltronas e o número da sala.                                |
| `Data`      | Armazena dia, mês e ano da sessão.                                     |
| `Sessao`    | Contém o nome do filme, data, horário e a sala reservada.               |

Cada sessão possui sua própria cópia da sala (e das 15 poltronas), garantindo independência entre sessões.

---

## Funcionalidades do Menu

| Opção | Ação                                              |
|-------|---------------------------------------------------|
| 1     | Comprar poltrona em uma sessão específica.        |
| 2     | Cancelar a compra de uma poltrona ocupada.        |
| 3     | Exibir relatório de poltronas livres e vendidas.  |
| 4     | Listar todas as sessões cadastradas.              |
| 0     | Encerrar o programa.                              |

---

## Como Compilar e Executar

```bash
gcc main.c -o cinema
./cinema
```

---

## Convenções de Código

- **Passagem por referência**: funções que modificam dados recebem ponteiros (`Poltrona*`, `Sala*`, `Sessao*`, `Data*`). O `malloc` não é realizado dentro das funções; a alocação é responsabilidade do chamador.
- **Passagem por valor**: funções de exibição (`mostrarPoltrona`, `mostrarMapaSala`, `mostrarSessao`) recebem cópias das structs, preservando os dados originais.

---

## Sessões Pré-Cadastradas

| Índice | Filme              | Data       | Horário | Sala |
|--------|--------------------|------------|---------|------|
| 0      | Oppenheimer        | 15/09/2025 | 14:00   | 1    |
| 1      | Barbie             | 15/09/2025 | 17:00   | 2    |
| 2      | Super Mario Bros   | 16/09/2025 | 16:00   | 3    |
| 3      | Duna: Parte Dois   | 15/09/2025 | 20:00   | 20   |

---

## Observações Técnicas

- As poltronas são indexadas de 0 a 14 dentro de cada sala.
- O mapa de cada sala exibe as poltronas em fileiras de 5, facilitando a visualização.
- O relatório de poltronas separa e conta explicitamente as poltronas livres e as vendidas por sessão.
- Todas as validações de índice (sessão e poltrona) são realizadas antes da operação.