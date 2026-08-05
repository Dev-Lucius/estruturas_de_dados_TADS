int main(){

    // Exercícios II
    // Variáveis
    int a, b, s;
    a = 20; b = 40; s = a + b;

    int *ps = (int*) malloc(sizeof(int));
    
    // Sempre validar se a alocação funcionou -> Boa Prática
    if (ps == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    *ps = s;
    
    // a. Mostre o resultado de A+B, armazenado no espaço referenciado por *ps
    printf("Resultado da Soma = %d\n", *ps);

    // b. Mostre o endereço ARMAZENADO NO ponteiro (aponta para o bloco do malloc)
    printf("Endereço armazenado NO ponteiro (ps) = %p\n", (void*) ps);
    
    // c. Mostre o endereço DO PRÓPRIO ponteiro (onde ps está guardado)
    printf("Endereço DO ponteiro (&ps) = %p\n", (void*) &ps);

    // d. Mostre o endereço das variáveis A e B
    printf("Endereço Variável A (&a) = %p\n", (void*) &a);
    printf("Endereço Variável B (&b) = %p\n", (void*) &b);

    // Libera Memória -> Boa Prática
    free(ps);
    return 0;
}
