# Questionário

- 1. (F) - "Cada nó guarda o dado e o endereço do PRÓXIMO nó. O endereço do anterior é característica da Lista Duplamente Encadeada."

- 2. (V) - "Em uma LSE (não circular), NULL no campo 'proximo' marca o último nó."

- 3. (V) - "Inserir no início é O(1): só ajusta dois ponteiros, sem deslocar elementos como em um vetor (que seria O(n))"

- 4. (F) - "LSE tem acesso SEQUENCIAL: para chegar ao 5º nó é preciso percorrer os 4 anteriores (O(n)). O acesso direto por índice é do vetor."

- 5. (V) - "Sem ponteiro para o fim, é preciso percorrer até o penúltimo nó para colocar seu 'proximo' em NULL (e dar free no último): O(n)"

- 6. (F) - "A LSE usa alocação DINÂMICA (malloc, no heap), nó a nó, em tempo de execução; o tamanho não é fixado na compilação."

- 7. (F) - "Em C não há coletor de lixo: free() é OBRIGATÓRIO. Sem ele ocorre memory leak (o SO só recupera a memória quando o programa termina)."

- 8. (V) - "Perdendo a cabeça sem outra referência, os nós continuam alocados "mas inalcançáveis: memory leak (ver Exercício 8)."

- 9. (V) - "Os nós vêm de malloc e podem estar em qualquer lugar do heap; quem os une são os ponteiros, não a contiguidade."

- 10 (V) - "A LSE guarda 1 ponteiro por nó; a LDE guarda 2 (anterior e próximo), gastando mais memória por nó."