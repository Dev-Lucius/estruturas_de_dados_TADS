/*
 * ============================================================================
 *  COLA COMPLETA DA LINGUAGEM C - PARA ESTUDO DE ESTRUTURA DE DADOS
 * ============================================================================
 * Compile com: gcc main.c -o main -Wall -Wextra
 * Execute com: ./main
 * ============================================================================
 */

#include <stdio.h>      /* Entrada e saída padrão (printf, scanf, FILE, etc) */
#include <stdlib.h>     /* Alocação dinâmica, conversão, rand, exit, etc */
#include <string.h>     /* Manipulação de strings (strcpy, strlen, strcmp, etc) */
#include <stdbool.h>    /* Tipo booleano (true/false) - C99+ */
#include <stdint.h>     /* Tipos inteiros com tamanho fixo (int32_t, uint64_t, etc) */
#include <limits.h>     /* Limites dos tipos inteiros (INT_MAX, INT_MIN, etc) */
#include <float.h>      /* Limites dos tipos de ponto flutuante (FLT_MAX, DBL_MIN, etc) */
#include <math.h>       /* Funções matemáticas (sqrt, pow, sin, etc) - linkar com -lm */

/* ============================================================================
 * 1. CONSTANTES E MACROS (PRÉ-PROCESSADOR)
 * ============================================================================
 * O pré-processador roda ANTES da compilação. Tudo que começa com # é
 * processado por ele.
 */

/* #define cria macros de substituição de texto (não são variáveis!) */
#define PI 3.14159265358979323846
#define TAM_MAX 100
#define QUADRADO(x) ((x) * (x))   /* Macro com parâmetro - SEMPRE use parênteses! */
#define MIN(a, b) ((a) < (b) ? (a) : (b))

/* Macros multilinha com barra invertida no final */
#define DEBUG_PRINT(msg) do { \
    printf("[DEBUG] %s:%d - %s\n", __FILE__, __LINE__, msg); \
} while(0)

/* Constantes definidas com const (são variáveis reais, com escopo e tipo) */
const int DIAS_SEMANA = 7;
const char* VERSAO = "1.0.0";

/* ============================================================================
 * 2. TIPOS DE DADOS BÁSICOS
 * ============================================================================
 * C é uma linguagem fortemente tipada e estaticamente tipada.
 * Tamanhos podem variar entre arquiteturas (32-bit vs 64-bit).
 */

void secao_tipos_de_dados(void) {
    printf("\n=== 2. TIPOS DE DADOS BÁSICOS ===\n");

    /* INTEIROS */
    char c = 'A';               /* 1 byte (-128 a 127 ou 0 a 255) */
    short s = 32767;            /* 2 bytes */
    int i = 2147483647;         /* 4 bytes (padrão para inteiros) */
    long l = 1234567890L;       /* 4 ou 8 bytes (sufixo L) */
    long long ll = 9223372036854775807LL; /* 8 bytes (sufixo LL) */

    /* INTEIROS SEM SINAL (unsigned) - apenas valores positivos, dobro da faixa */
    unsigned char uc = 255;
    unsigned int ui = 4294967295U;   /* sufixo U */
    unsigned long ul = 1234567890UL; /* sufixo UL */

    /* TIPOS COM TAMANHO FIXO (C99) - melhor para portabilidade */
    int8_t  i8  = -128;         /* exatamente 8 bits com sinal */
    uint8_t u8  = 255;          /* exatamente 8 bits sem sinal */
    int16_t i16 = -32768;       /* exatamente 16 bits */
    uint32_t u32 = 4294967295U; /* exatamente 32 bits */
    int64_t i64 = -9223372036854775807LL; /* exatamente 64 bits */

    /* PONTO FLUTUANTE */
    float f = 3.14f;            /* 4 bytes, ~7 dígitos de precisão (sufixo f) */
    double d = 3.141592653589793; /* 8 bytes, ~15 dígitos de precisão */
    long double ld = 3.14159265358979323846L; /* 8+ bytes (sufixo L) */

    /* BOOLEANO (C99, <stdbool.h>) */
    bool flag = true;           /* true = 1, false = 0 */
    /* Internamente, bool é um unsigned char. Qualquer valor != 0 é "verdadeiro" */

    /* VOID - tipo vazio, usado para funções sem retorno ou ponteiros genéricos */
    void* ptr_generico = NULL;  /* Ponteiro para qualquer tipo */

    /* SIZE_T - tipo para tamanhos e contagens (unsigned, depende da arquitetura) */
    size_t tamanho = sizeof(int);  /* sizeof retorna size_t */

    printf("sizeof(char)      = %zu byte\n", sizeof(char));
    printf("sizeof(short)     = %zu bytes\n", sizeof(short));
    printf("sizeof(int)       = %zu bytes\n", sizeof(int));
    printf("sizeof(long)      = %zu bytes\n", sizeof(long));
    printf("sizeof(long long) = %zu bytes\n", sizeof(long long));
    printf("sizeof(float)     = %zu bytes\n", sizeof(float));
    printf("sizeof(double)    = %zu bytes\n", sizeof(double));
    printf("sizeof(void*)     = %zu bytes (tamanho do ponteiro)\n", sizeof(void*));
    printf("sizeof(size_t)    = %zu bytes\n", sizeof(size_t));
}

/* ============================================================================
 * 3. MODIFICADORES DE ARMAZENAMENTO E QUALIFICADORES
 * ============================================================================
 */

/* auto     - automático (padrão para variáveis locais, raramente usado) */
/* static   - duração estática, visibilidade restrita ao arquivo/função */
/* extern   - declara uma variável definida em outro arquivo */
/* register - sugestão para armazenar em registrador (obsoleto, compilador decide) */
/* volatile - diz ao compilador que o valor pode mudar a qualquer momento (hardware, threads) */

static int contador_global = 0;  /* Visível apenas neste arquivo, mantém valor entre chamadas */

/* const    - valor não pode ser alterado após inicialização */
/* restrict - ponteiro é a única referência àquele dado (otimização) */

void exemplo_static(void) {
    static int chamadas = 0;  /* Inicializado apenas UMA VEZ, mantém valor entre chamadas */
    chamadas++;
    printf("Esta função foi chamada %d vezes\n", chamadas);
}

/* ============================================================================
 * 4. OPERADORES
 * ============================================================================
 */

void secao_operadores(void) {
    printf("\n=== 4. OPERADORES ===\n");

    int a = 10, b = 3;

    /* ARITMÉTICOS */
    printf("a + b  = %d (adição)\n", a + b);
    printf("a - b  = %d (subtração)\n", a - b);
    printf("a * b  = %d (multiplicação)\n", a * b);
    printf("a / b  = %d (divisão inteira - trunca!)\n", a / b);
    printf("a %% b  = %d (módulo/resto da divisão)\n", a % b);

    /* DIVISÃO DE INTEIROS vs PONTO FLUTUANTE */
    printf("5 / 2    = %d (inteiro)\n", 5 / 2);
    printf("5.0 / 2  = %.1f (float, pelo menos um operando é float)\n", 5.0 / 2);

    /* RELACIONAIS (retornam 0 para falso, 1 para verdadeiro) */
    printf("a == b   -> %d (igual)\n", a == b);
    printf("a != b   -> %d (diferente)\n", a != b);
    printf("a > b    -> %d (maior)\n", a > b);
    printf("a < b    -> %d (menor)\n", a < b);
    printf("a >= b   -> %d (maior ou igual)\n", a >= b);
    printf("a <= b   -> %d (menor ou igual)\n", a <= b);

    /* LÓGICOS */
    printf("(a > 5) && (b < 5) -> %d (E lógico)\n", (a > 5) && (b < 5));
    printf("(a > 5) || (b > 5) -> %d (OU lógico)\n", (a > 5) || (b > 5));
    printf("!(a == b)          -> %d (NÃO lógico)\n", !(a == b));
    /* AVALIAÇÃO EM CURTO-CIRCUITO: se (a && b) e a é falso, b NÃO é avaliado */

    /* BIT A BIT (trabalham nos bits) */
    int x = 5;  /* 0101 */
    int y = 3;  /* 0011 */
    printf("x & y  = %d (E bit a bit: 0101 & 0011 = 0001)\n", x & y);
    printf("x | y  = %d (OU bit a bit: 0101 | 0011 = 0111)\n", x | y);
    printf("x ^ y  = %d (OU exclusivo: 0101 ^ 0011 = 0110)\n", x ^ y);
    printf("~x     = %d (NOT bit a bit - inverte todos os bits)\n", ~x);
    printf("x << 1 = %d (deslocamento à esquerda: 0101 -> 1010)\n", x << 1);
    printf("x >> 1 = %d (deslocamento à direita: 0101 -> 0010)\n", x >> 1);

    /* ATRIBUIÇÃO COMPOSTA */
    int z = 10;
    z += 5;   /* z = z + 5;  z agora é 15 */
    z -= 3;   /* z = z - 3;  z agora é 12 */
    z *= 2;   /* z = z * 2;  z agora é 24 */
    z /= 4;   /* z = z / 4;  z agora é 6 */
    z %= 4;   /* z = z % 4;  z agora é 2 */
    z &= 1;   /* z = z & 1;  z agora é 0 */
    z |= 1;   /* z = z | 1;  z agora é 1 */
    z ^= 3;   /* z = z ^ 3;  z agora é 2 */
    z <<= 1;  /* z = z << 1; z agora é 4 */
    z >>= 1;  /* z = z >> 1; z agora é 2 */

    /* INCREMENTO E DECREMENTO */
    int n = 5;
    printf("n++ (pós-incremento): retorna %d, depois n=%d\n", n++, n); /* retorna 5, n vira 6 */
    n = 5;
    printf("++n (pré-incremento): retorna %d, n=%d\n", ++n, n);       /* n vira 6, retorna 6 */

    /* OPERADOR TERNÁRIO (condicional) */
    int maior = (a > b) ? a : b;  /* se condição for verdadeira, retorna a, senão b */
    printf("Maior entre %d e %d: %d\n", a, b, maior);

    /* OPERADOR VÍRGULA (avalia da esquerda para direita, retorna o último valor) */
    int resultado = (a = 1, b = 2, a + b);  /* a=1, b=2, retorna 3 */
    printf("Resultado do operador vírgula: %d\n", resultado);

    /* OPERADOR SIZEOF (retorna o tamanho em bytes, não executa a expressão) */
    printf("sizeof(int) = %zu\n", sizeof(int));
    printf("sizeof(a)   = %zu\n", sizeof(a));
    printf("sizeof(a+b) = %zu\n", sizeof(a + b));

    /* PRECEDÊNCIA (maior precedência = avaliado primeiro):
     * () [] -> . (mais alta)
     * ++ -- (pós)  ! ~  ++ -- (pré)  * &  sizeof  (unários)
     * * / %
     * + -
     * << >>
     * < <= > >=
     * == !=
     * &
     * ^
     * |
     * &&
     * ||
     * ?:
     * = += -= *= ... (mais baixa, exceto vírgula)
     * ,
     */
}

/* ============================================================================
 * 5. ENTRADA E SAÍDA (PRINTF / SCANF)
 * ============================================================================
 */

void secao_entrada_saida(void) {
    printf("\n=== 5. ENTRADA E SAÍDA ===\n");

    /* PRINTF - especificadores de formato principais:
     * %%   - caractere %
     * %c   - char
     * %d   - int (decimal com sinal)
     * %u   - unsigned int
     * %ld  - long
     * %lld - long long
     * %lu  - unsigned long
     * %llu - unsigned long long
     * %zu  - size_t
     * %f   - float/double
     * %e   - notação científica
     * %g   - %f ou %e, o mais curto
     * %Lf  - long double
     * %s   - string (char*)
     * %p   - ponteiro (endereço de memória)
     * %x   - hexadecimal (minúsculo)
     * %X   - hexadecimal (maiúsculo)
     * %o   - octal
     * %b   - binário (extensão GNU, não padrão C)
     *
     * Modificadores de largura e precisão:
     * %5d    - mínimo 5 caracteres de largura
     * %-5d   - alinhado à esquerda
     * %05d   - preenchido com zeros
     * %.2f   - 2 casas decimais
     * %8.2f  - 8 caracteres de largura, 2 decimais
     */

    int num = 42;
    float pi = 3.14159f;
    printf("Inteiro: [%5d], [%-5d], [%05d]\n", num, num, num);
    printf("Float:   [%.2f], [%8.2f], [%-8.2f]\n", pi, pi, pi);
    printf("Hex:     %x, %X\n", 255, 255);
    printf("Ponteiro: %p\n", (void*)&num);

    /* SCANF - leitura de entrada (CUIDADO: não faz bounds checking!) */
    /*
    int idade;
    char nome[50];
    printf("Digite sua idade: ");
    scanf("%d", &idade);           /* & é obrigatório para variáveis simples */
    /*
    printf("Digite seu nome: ");
    scanf("%49s", nome);           /* arrays já são ponteiros, NÃO use & */
                                   /* %49s limita a 49 caracteres + \\0 */
    */

    /* Leitura segura de strings com espaços: */
    /* fgets(nome, sizeof(nome), stdin);  /* lê até newline ou tamanho-1 */

    /* getchar() / putchar() - caractere por caractere */
    /* getchar() lê um caractere do stdin (retorna int para comportar EOF) */
    /* putchar('A') imprime um caractere */

    /* sprintf / snprintf - escreve em string ao invés de stdout */
    char buffer[100];
    snprintf(buffer, sizeof(buffer), "Valor: %d", 42);
    printf("Buffer: %s\n", buffer);

    /* sscanf - lê de string ao invés de stdin */
    int valor_lido;
    sscanf("123", "%d", &valor_lido);
    printf("Valor lido de string: %d\n", valor_lido);
}

/* ============================================================================
 * 6. ESTRUTURAS DE CONTROLE
 * ============================================================================
 */

void secao_estruturas_controle(void) {
    printf("\n=== 6. ESTRUTURAS DE CONTROLE ===\n");

    /* IF / ELSE IF / ELSE */
    int nota = 85;
    if (nota >= 90) {
        printf("Conceito A\n");
    } else if (nota >= 80) {
        printf("Conceito B\n");
    } else if (nota >= 70) {
        printf("Conceito C\n");
    } else {
        printf("Reprovado\n");
    }

    /* IF sem chaves (apenas uma instrução) - PERIGOSO, evite! */
    if (nota > 60)
        printf("Aprovado\n");  /* apenas esta linha pertence ao if */
    /* printf("Isso SEMPRE executa\n");  /* não pertence ao if! */

    /* SWITCH / CASE */
    int opcao = 2;
    switch (opcao) {
        case 1:
            printf("Opção 1 selecionada\n");
            break;  /* SEMPRE use break! Sem ele, ocorre "fall-through" */
        case 2:
            printf("Opção 2 selecionada\n");
            break;
        case 3:
            printf("Opção 3 selecionada\n");
            break;
        default:
            printf("Opção inválida\n");
            break;
    }

    /* Fall-through intencional (comente para indicar) */
    char letra = 'a';
    switch (letra) {
        case 'a':  /* fall through */
        case 'e':  /* fall through */
        case 'i':  /* fall through */
        case 'o':  /* fall through */
        case 'u':
            printf("'%c' é uma vogal\n", letra);
            break;
        default:
            printf("'%c' não é uma vogal\n", letra);
    }

    /* FOR */
    printf("FOR: ");
    for (int i = 0; i < 5; i++) {  /* inicialização; condição; incremento */
        printf("%d ", i);
    }
    printf("\n");

    /* FOR com múltiplas variáveis */
    printf("FOR duplo: ");
    for (int i = 0, j = 10; i < j; i++, j--) {
        printf("(%d,%d) ", i, j);
    }
    printf("\n");

    /* FOR infinito */
    /* for (;;) { ... } */

    /* WHILE */
    printf("WHILE: ");
    int contador = 0;
    while (contador < 5) {
        printf("%d ", contador);
        contador++;
    }
    printf("\n");

    /* DO-WHILE (executa pelo menos uma vez) */
    printf("DO-WHILE: ");
    int c = 0;
    do {
        printf("%d ", c);
        c++;
    } while (c < 5);
    printf("\n");

    /* BREAK - sai do loop/switch mais interno */
    printf("BREAK: ");
    for (int i = 0; i < 10; i++) {
        if (i == 5) break;
        printf("%d ", i);
    }
    printf("\n");

    /* CONTINUE - pula para a próxima iteração */
    printf("CONTINUE (ímpares): ");
    for (int i = 0; i < 10; i++) {
        if (i % 2 == 0) continue;  /* pula números pares */
        printf("%d ", i);
    }
    printf("\n");

    /* GOTO - salto incondicional (EVITE! Use apenas para sair de loops aninhados) */
    printf("GOTO: ");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == 1 && j == 1) goto fim;
            printf("(%d,%d) ", i, j);
        }
    }
fim:
    printf("-> saída via goto\n");
}

/* ============================================================================
 * 7. FUNÇÕES
 * ============================================================================
 * Em C, funções devem ser declaradas (protótipo) ou definidas antes de usadas.
 * Passagem de parâmetros é SEMPRE POR VALOR (exceto arrays, que decaem para ponteiros).
 */

/* Declaração (protótipo) - permite usar a função antes de defini-la */
int soma(int a, int b);

/* Definição */
int soma(int a, int b) {
    return a + b;
}

/* Função sem retorno (void) */
void imprime_mensagem(const char* msg) {
    printf("%s\n", msg);
}

/* Função com parâmetros padrão? NÃO EXISTE EM C! */
/* Alternativa: funções com número variável de argumentos (variadic) */
#include <stdarg.h>

/* Função que aceita qualquer número de argumentos int */
int soma_variavel(int count, ...) {
    va_list args;
    va_start(args, count);
    int total = 0;
    for (int i = 0; i < count; i++) {
        total += va_arg(args, int);
    }
    va_end(args);
    return total;
}

/* Passagem por referência usando ponteiros (simula passagem por referência) */
void troca(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Função que retorna múltiplos valores via ponteiros */
void min_max(int arr[], int n, int* min, int* max) {
    *min = *max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < *min) *min = arr[i];
        if (arr[i] > *max) *max = arr[i];
    }
}

/* Função inline (sugestão ao compilador para expandir no local da chamada) */
static inline int quadrado_inline(int x) {
    return x * x;
}

/* Função recursiva */
unsigned long long fatorial(int n) {
    if (n <= 1) return 1;           /* caso base */
    return n * fatorial(n - 1);     /* chamada recursiva */
}

/* Recursão de cauda (otimizável pelo compilador) */
unsigned long long fatorial_tail(int n, unsigned long long acc) {
    if (n <= 1) return acc;
    return fatorial_tail(n - 1, n * acc);
}

void secao_funcoes(void) {
    printf("\n=== 7. FUNÇÕES ===\n");

    printf("soma(3, 4) = %d\n", soma(3, 4));
    imprime_mensagem("Hello, C!");
    printf("soma_variavel(4, 1, 2, 3, 4) = %d\n", soma_variavel(4, 1, 2, 3, 4));

    int x = 5, y = 10;
    printf("Antes da troca: x=%d, y=%d\n", x, y);
    troca(&x, &y);  /* passamos os ENDEREÇOS */
    printf("Depois da troca: x=%d, y=%d\n", x, y);

    int arr[] = {3, 1, 4, 1, 5, 9, 2, 6};
    int min, max;
    min_max(arr, 8, &min, &max);
    printf("Array: min=%d, max=%d\n", min, max);

    printf("fatorial(5) = %llu\n", fatorial(5));
    printf("fatorial_tail(5, 1) = %llu\n", fatorial_tail(5, 1));
}

/* ============================================================================
 * 8. ARRAYS (VETORES)
 * ============================================================================
 * Arrays em C são blocos contíguos de memória.
 * O nome do array é um ponteiro para o primeiro elemento (decay).
 * NÃO há verificação de limites (bounds checking)!
 */

void secao_arrays(void) {
    printf("\n=== 8. ARRAYS ===\n");

    /* Declaração e inicialização */
    int numeros[5];              /* array de 5 inteiros (valores lixo) */
    int valores[5] = {1, 2, 3, 4, 5};
    int parcial[] = {1, 2, 3};   /* tamanho inferido: 3 elementos */
    int zeros[5] = {0};          /* primeiro = 0, resto = 0 (inicialização parcial) */
    int repetido[5] = {[0] = 1, [2] = 3};  /* designadores (C99) */

    /* Acesso */
    numeros[0] = 10;  /* índices começam em 0 */
    numeros[4] = 50;  /* último elemento de array[5] é o índice 4 */
    /* numeros[5] = 60;  /* COMPORTAMENTO INDEFINIDO! Estourou o array */

    printf("Array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", valores[i]);
    }
    printf("\n");

    /* Tamanho do array em tempo de compilação */
    int n = sizeof(valores) / sizeof(valores[0]);  /* total / elemento = count */
    printf("Tamanho do array 'valores': %d elementos\n", n);

    /* ARRAYS MULTIDIMENSIONAIS */
    int matriz[3][4] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12}
    };

    printf("Matriz 3x4:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%3d ", matriz[i][j]);
        }
        printf("\n");
    }

    /* Arrays multidimensionais como parâmetro: deve especificar todas as dimensões
     * exceto a primeira */
    /* void func(int matriz[][4], int linhas); */

    /* ARRAYS DE STRINGS */
    char* frutas[] = {"Maçã", "Banana", "Laranja"};
    printf("Frutas: ");
    for (int i = 0; i < 3; i++) {
        printf("%s ", frutas[i]);
    }
    printf("\n");
}

/* ============================================================================
 * 9. STRINGS
 * ============================================================================
 * Em C, strings são arrays de char terminados por \\0 (null terminator).
 * NÃO há tipo string nativo!
 */

void secao_strings(void) {
    printf("\n=== 9. STRINGS ===\n");

    /* Declaração */
    char str1[20] = "Hello";     /* array com espaço para 19 chars + \\0 */
    char str2[] = "World";       /* tamanho automático: 6 bytes (5 + \\0) */
    char str3[20];               /* não inicializado (lixo) */

    /* Cópia (NUNCA use = para strings, use strcpy) */
    strcpy(str3, str1);          /* copia str1 para str3 */
    printf("strcpy: %s\n", str3);

    /* Concatenação */
    strcat(str3, " ");           /* concatena espaço */
    strcat(str3, str2);          /* concatena str2 */
    printf("strcat: %s\n", str3);

    /* Comprimento (não conta o \\0) */
    printf("strlen(str3) = %zu\n", strlen(str3));

    /* Comparação (retorna 0 se iguais, <0 se str1<str2, >0 se str1>str2) */
    printf("strcmp(\"abc\", \"def\") = %d\n", strcmp("abc", "def"));
    printf("strcmp(\"abc\", \"abc\") = %d\n", strcmp("abc", "abc"));

    /* Busca de caractere/substring */
    char* pos = strchr(str3, 'l');  /* primeira ocorrência de 'l' */
    printf("strchr('%s', 'l') -> '%s'\n", str3, pos);

    char* sub = strstr(str3, "orl");  /* primeira ocorrência de "orl" */
    printf("strstr('%s', \"orl\") -> '%s'\n", str3, sub);

    /* Tokenização (cuidado: modifica a string original!) */
    char texto[] = "um,dois,tres";
    char* token = strtok(texto, ",");
    printf("Tokens: ");
    while (token != NULL) {
        printf("[%s] ", token);
        token = strtok(NULL, ",");  /* NULL continua na mesma string */
    }
    printf("\n");

    /* VERSÕES SEGURAS (com limite de tamanho) */
    char dest[10];
    strncpy(dest, "Hello World", sizeof(dest) - 1);  /* copia no máximo 9 chars */
    dest[sizeof(dest) - 1] = '\0';  /* GARANTE o terminador! strncpy não garante */
    printf("strncpy seguro: %s\n", dest);

    /* LEITURA SEGURA */
    /* fgets(dest, sizeof(dest), stdin);  /* lê até newline ou tamanho-1, inclui \\n */
}

/* ============================================================================
 * 10. PONTEIROS
 * ============================================================================
 * Ponteiros são variáveis que armazenam ENDEREÇOS DE MEMÓRIA.
 * São FUNDAMENTAIS para estruturas de dados (listas, árvores, grafos).
 */

void secao_ponteiros(void) {
    printf("\n=== 10. PONTEIROS ===\n");

    int valor = 42;
    int* ptr = &valor;           /* ptr armazena o endereço de valor */

    printf("valor = %d\n", valor);
    printf("&valor = %p (endereço de valor)\n", (void*)&valor);
    printf("ptr = %p (conteúdo do ponteiro = endereço de valor)\n", (void*)ptr);
    printf("*ptr = %d (valor apontado)\n", *ptr);  /* dereferenciação */

    /* Modificando o valor via ponteiro */
    *ptr = 100;
    printf("Após *ptr = 100: valor = %d\n", valor);

    /* ARITMÉTICA DE PONTEIROS */
    int arr[] = {10, 20, 30, 40, 50};
    int* p = arr;  /* p aponta para arr[0] */

    printf("Aritmética de ponteiros:\n");
    printf("*p       = %d (arr[0])\n", *p);
    printf("*(p+1)   = %d (arr[1])\n", *(p + 1));  /* pula sizeof(int) bytes */
    printf("*(p+2)   = %d (arr[2])\n", *(p + 2));
    printf("p[2]     = %d (notação de array = *(p+2))\n", p[2]);
    printf("2[p]     = %d (também válido! = *(2+p))\n", 2[p]);  /* curiosidade */

    p++;  /* p agora aponta para arr[1] */
    printf("Após p++: *p = %d\n", *p);

    /* Diferença entre ponteiros (número de elementos entre eles) */
    int* inicio = arr;
    int* fim = &arr[4];
    printf("fim - inicio = %ld elementos\n", fim - inicio);

    /* PONTEIROS E ARRAYS */
    /* arr[i] é SEMPRE equivalente a *(arr + i) */
    /* &arr[i] é SEMPRE equivalente a arr + i */

    /* PONTEIRO PARA PONTEIRO */
    int x = 5;
    int* px = &x;
    int** ppx = &px;  /* ponteiro para ponteiro */
    printf("x = %d, *px = %d, **ppx = %d\n", x, *px, **ppx);

    /* PONTEIRO PARA VOID (genérico) */
    void* vptr = &x;
    printf("void* aponta para x: %d\n", *(int*)vptr);  /* precisa fazer cast antes de dereferenciar */

    /* PONTEIRO NULO */
    int* nulo = NULL;  /* NULL é (void*)0, ponteiro que não aponta para lugar nenhum */
    if (nulo == NULL) {
        printf("Ponteiro nulo detectado!\n");
    }

    /* PONTEIRO CONSTANTE vs CONTEÚDO CONSTANTE */
    int a = 1, b = 2;
    const int* ptr1 = &a;   /* conteúdo é constante (não pode alterar *ptr1) */
    /* *ptr1 = 10;  /* ERRO! */
    ptr1 = &b;              /* OK, pode apontar para outro lugar */

    int* const ptr2 = &a;   /* ponteiro é constante (não pode alterar ptr2) */
    *ptr2 = 10;             /* OK, pode alterar o conteúdo */
    /* ptr2 = &b;  /* ERRO! */

    const int* const ptr3 = &a;  /* ambos constantes: nem ponteiro nem conteúdo mudam */

    /* PONTEIROS E ARRAYS MULTIDIMENSIONAIS */
    int matriz[3][4];
    int (*pm)[4] = matriz;  /* ponteiro para array de 4 inteiros */
    printf("matriz[1][2] via ponteiro: %d\n", pm[1][2]);  /* ainda não inicializado, lixo */
}

/* ============================================================================
 * 11. STRUCTS (ESTRUTURAS)
 * ============================================================================
 * Structs agrupam variáveis de tipos diferentes em um único tipo.
 * São a base para nós de listas, árvores, grafos, etc.
 */

/* Declaração de struct */
struct Pessoa {
    char nome[50];
    int idade;
    float altura;
};

/* Struct com ponteiro para si mesma (fundamental para estruturas de dados!) */
struct No {
    int dados;
    struct No* proximo;  /* ponteiro para o próximo nó */
};

/* Struct aninhada */
struct Endereco {
    char rua[100];
    int numero;
};

struct Cliente {
    char nome[50];
    struct Endereco endereco;  /* struct aninhada por valor */
    struct Cliente* proximo;    /* ponteiro para próximo (lista encadeada) */
};

void secao_structs(void) {
    printf("\n=== 11. STRUCTS ===\n");

    /* Inicialização */
    struct Pessoa p1 = {"Maria", 25, 1.65f};
    struct Pessoa p2 = {.nome = "João", .idade = 30};  /* designadores (C99) */

    printf("Pessoa: %s, %d anos, %.2fm\n", p1.nome, p1.idade, p1.altura);

    /* Acesso via ponteiro */
    struct Pessoa* ptr = &p1;
    printf("Via ponteiro: %s\n", ptr->nome);   /* -> é (*ptr).nome simplificado */
    printf("Equivalente:  %s\n", (*ptr).nome);

    /* Struct aninhada */
    struct Cliente cli = {
        .nome = "Ana",
        .endereco = {"Av. Principal", 123},
        .proximo = NULL
    };
    printf("Cliente: %s, Rua: %s, Nº: %d\n", cli.nome, cli.endereco.rua, cli.endereco.numero);

    /* ARRAY DE STRUCTS */
    struct Pessoa turma[3] = {
        {"Alice", 20, 1.60f},
        {"Bob", 22, 1.75f},
        {"Carol", 21, 1.68f}
    };
    printf("Turma:\n");
    for (int i = 0; i < 3; i++) {
        printf("  %s (%d anos)\n", turma[i].nome, turma[i].idade);
    }

    /* PONTEIROS PARA STRUCTS E ALOCAÇÃO DINÂMICA */
    struct No* no = (struct No*)malloc(sizeof(struct No));
    if (no != NULL) {
        no->dados = 42;
        no->proximo = NULL;
        printf("Nó alocado: dados=%d, prox=%p\n", no->dados, (void*)no->proximo);
        free(no);
    }
}

/* ============================================================================
 * 12. UNIONS
 * ============================================================================
 * Union é como uma struct, mas todos os campos COMPARTILHAM o mesmo espaço
 * de memória. O tamanho é igual ao do maior campo.
 */

union Dado {
    int inteiro;
    float flutuante;
    char bytes[4];
};

void secao_unions(void) {
    printf("\n=== 12. UNIONS ===\n");

    union Dado d;
    printf("sizeof(union Dado) = %zu (tamanho do maior campo: float = %zu)\n",
           sizeof(union Dado), sizeof(float));

    d.inteiro = 65;  /* 'A' em ASCII */
    printf("Como inteiro: %d\n", d.inteiro);
    printf("Como float:   %f (interpretação incorreta do mesmo padrão de bits)\n", d.flutuante);
    printf("Primeiro byte: %d (ASCII %c)\n", (unsigned char)d.bytes[0], d.bytes[0]);

    /* Union anônima dentro de struct (útil para polimorfismo básico) */
    struct Valor {
        enum { T_INT, T_FLOAT, T_CHAR } tipo;
        union {
            int i;
            float f;
            char c;
        } val;  /* union nomeada dentro da struct */
    };

    struct Valor v1 = {.tipo = T_INT, .val.i = 42};
    struct Valor v2 = {.tipo = T_FLOAT, .val.f = 3.14f};
    printf("Valor int: %d, Valor float: %.2f\n", v1.val.i, v2.val.f);
}

/* ============================================================================
 * 13. ENUM (ENUMERAÇÕES)
 * ============================================================================
 * Enums criam constantes nomeadas com valores inteiros.
 */

enum Cor { VERMELHO, VERDE, AZUL };           /* 0, 1, 2 */
enum Dia { DOM = 1, SEG, TER, QUA, QUI, SEX, SAB };  /* 1, 2, 3, 4, 5, 6, 7 */
enum Status { OK = 200, ERRO = 500, NAO_ENCONTRADO = 404 };

/* Typedef com enum (veja seção 14) */
typedef enum {
    PRIORIDADE_BAIXA = 1,
    PRIORIDADE_MEDIA = 5,
    PRIORIDADE_ALTA = 10
} Prioridade;

void secao_enums(void) {
    printf("\n=== 13. ENUMS ===\n");

    enum Cor c = VERMELHO;
    printf("VERMELHO = %d, VERDE = %d, AZUL = %d\n", VERMELHO, VERDE, AZUL);
    printf("Dia: DOM=%d, SEG=%d, ..., SAB=%d\n", DOM, SEG, SAB);

    Prioridade p = PRIORIDADE_ALTA;
    printf("Prioridade ALTA = %d\n", p);

    /* Enums são inteiros subjacentes */
    printf("sizeof(enum Cor) = %zu\n", sizeof(enum Cor));
}

/* ============================================================================
 * 14. TYPEDEF
 * ============================================================================
 * typedef cria um ALIAS (apelido) para um tipo existente.
 * Muito usado para simplificar declarações complexas.
 */

/* Apelido para tipos básicos */
typedef unsigned int uint;
typedef unsigned char byte;

/* Apelido para struct (padrão em estruturas de dados) */
typedef struct NoLista {
    int dados;
    struct NoLista* prox;
} NoLista;  /* agora posso usar apenas 'NoLista' em vez de 'struct NoLista' */

/* Apelido para ponteiro de função */
typedef int (*Comparador)(const void*, const void*);

/* Apelido para array */
typedef int Vetor10[10];  /* Vetor10 é um array de 10 inteiros */

void secao_typedef(void) {
    printf("\n=== 14. TYPEDEF ===\n");

    uint numero = 100;           /* mesmo que unsigned int */
    byte b = 255;                /* mesmo que unsigned char */

    NoLista* cabeca = NULL;      /* struct implícita graças ao typedef */
    printf("NoLista criado (NULL): %p\n", (void*)cabeca);

    Vetor10 v;                   /* array de 10 inteiros */
    printf("sizeof(Vetor10) = %zu\n", sizeof(v));
}

/* ============================================================================
 * 15. ALOCAÇÃO DINÂMICA DE MEMÓRIA
 * ============================================================================
 * Memória alocada na HEAP (monte) em tempo de execução.
 * ESSENCIAL para estruturas de dados de tamanho variável.
 */

void secao_alocacao_dinamica(void) {
    printf("\n=== 15. ALOCAÇÃO DINÂMICA ===\n");

    /* MALLOC - aloca memória NÃO INICIALIZADA */
    int* ptr1 = (int*)malloc(5 * sizeof(int));  /* 5 inteiros = 20 bytes (geralmente) */
    if (ptr1 == NULL) {
        fprintf(stderr, "Erro ao alocar memória!\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < 5; i++) {
        ptr1[i] = i * 10;  /* inicializa manualmente */
    }
    printf("malloc: ");
    for (int i = 0; i < 5; i++) printf("%d ", ptr1[i]);
    printf("\n");

    /* CALLOC - aloca e ZERA a memória (count, size) */
    int* ptr2 = (int*)calloc(5, sizeof(int));  /* 5 inteiros, todos = 0 */
    printf("calloc (todos zeros): ");
    for (int i = 0; i < 5; i++) printf("%d ", ptr2[i]);
    printf("\n");

    /* REALLOC - redimensiona um bloco alocado anteriormente */
    ptr1 = (int*)realloc(ptr1, 10 * sizeof(int));  /* expande para 10 inteiros */
    if (ptr1 != NULL) {
        for (int i = 5; i < 10; i++) ptr1[i] = i * 10;
        printf("realloc (10 elementos): ");
        for (int i = 0; i < 10; i++) printf("%d ", ptr1[i]);
        printf("\n");
    }

    /* REALLOC com NULL equivale a malloc */
    int* ptr3 = (int*)realloc(NULL, 5 * sizeof(int));  /* mesmo que malloc */

    /* FREE - libera a memória alocada */
    free(ptr1);
    free(ptr2);
    free(ptr3);
    /* ptr1 = NULL;  /* BOA PRÁTICA: anular o ponteiro após free */

    /* Dangling pointer (ponteiro pendente) - ponteiro que aponta para memória já liberada */
    /* Acessar *ptr1 após free é comportamento indefinido! */

    /* Memory leak (vazamento de memória) - alocar sem liberar */
    /* int* leak = malloc(100);  /* sem free(leak); -> vazamento! */

    /* ALOCAÇÃO DE ARRAY 2D (matriz dinâmica) */
    int linhas = 3, colunas = 4;
    int** matriz = (int**)malloc(linhas * sizeof(int*));
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (int*)malloc(colunas * sizeof(int));
    }
    /* Uso: matriz[i][j] */
    /* Liberação (ordem inversa): */
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    /* ALOCAÇÃO DE ARRAY DE STRUCTS */
    struct Pessoa* turma = (struct Pessoa*)malloc(30 * sizeof(struct Pessoa));
    if (turma) {
        strcpy(turma[0].nome, "Aluno 1");
        turma[0].idade = 20;
        printf("Struct alocada: %s (%d anos)\n", turma[0].nome, turma[0].idade);
        free(turma);
    }
}

/* ============================================================================
 * 16. MANIPULAÇÃO DE ARQUIVOS
 * ============================================================================
 */

void secao_arquivos(void) {
    printf("\n=== 16. ARQUIVOS ===\n");

    /* Modos de abertura:
     * "r"  - leitura (arquivo deve existir)
     * "w"  - escrita (cria novo ou trunca existente)
     * "a"  - append (escrita no final, cria se não existir)
     * "r+" - leitura e escrita (arquivo deve existir)
     * "w+" - leitura e escrita (cria novo ou trunca)
     * "a+" - leitura e append (cria se não existir)
     * "b"  - modo binário (ex: "rb", "wb")
     */

    FILE* arquivo = fopen("teste.txt", "w");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para escrita");  /* imprime mensagem de erro do sistema */
        return;
    }

    /* ESCRITA */
    fprintf(arquivo, "Linha 1: número %d\n", 42);
    fprintf(arquivo, "Linha 2: texto %s\n", "exemplo");
    fputs("Linha 3: fputs\n", arquivo);
    fputc('A', arquivo);  /* escreve um caractere */
    fputc('\n', arquivo);

    fclose(arquivo);

    /* LEITURA */
    arquivo = fopen("teste.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir arquivo para leitura");
        return;
    }

    /* Ler linha por linha */
    char linha[100];
    printf("Conteúdo do arquivo:\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        printf("  %s", linha);  /* fgets já inclui o \n */
    }

    /* Voltar ao início do arquivo */
    rewind(arquivo);

    /* Ler caractere por caractere */
    /* int c;
    while ((c = fgetc(arquivo)) != EOF) {
        putchar(c);
    } */

    /* Ler com fscanf */
    /* fscanf(arquivo, "%d %s", &num, str); */

    /* Posicionamento no arquivo */
    /* fseek(arquivo, 0, SEEK_SET);   /* início */
    /* fseek(arquivo, 0, SEEK_END);   /* fim */
    /* fseek(arquivo, 10, SEEK_CUR);  /* 10 bytes a partir da posição atual */
    /* long pos = ftell(arquivo);     /* posição atual em bytes */

    fclose(arquivo);

    /* Remover arquivo de teste */
    remove("teste.txt");
    printf("Arquivo de teste removido.\n");
}

/* ============================================================================
 * 17. PONTEIROS PARA FUNÇÕES
 * ============================================================================
 * Permitem passar funções como parâmetros (callbacks) e criar
 * estruturas de dados genéricas (como qsort).
 */

/* Declaração de ponteiro para função */
int comparar_int(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
    /* Equivalente mais curto: return (*(int*)a - *(int*)b); */
}

/* Função que recebe ponteiro para função */
void executar(int (*funcao)(int), int valor) {
    printf("Resultado da função: %d\n", funcao(valor));
}

int dobro(int x) { return 2 * x; }
int triplo(int x) { return 3 * x; }

void secao_ponteiros_funcoes(void) {
    printf("\n=== 17. PONTEIROS PARA FUNÇÕES ===\n");

    int arr[] = {5, 2, 8, 1, 9, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Array original: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    /* qsort - ordenação rápida da stdlib, usa callback */
    qsort(arr, n, sizeof(int), comparar_int);

    printf("Array ordenado: ");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");

    /* Usando ponteiro para função */
    int (*op)(int);  /* declara ponteiro para função que recebe int e retorna int */
    op = dobro;
    printf("dobro(5) via ponteiro: %d\n", op(5));
    op = triplo;
    printf("triplo(5) via ponteiro: %d\n", op(5));

    /* Passando função como parâmetro */
    executar(dobro, 7);
    executar(triplo, 7);

    /* Array de ponteiros para funções */
    int (*operacoes[])(int) = {dobro, triplo};
    printf("operacoes[0](4) = %d\n", operacoes[0](4));
    printf("operacoes[1](4) = %d\n", operacoes[1](4));
}

/* ============================================================================
 * 18. PRÉ-PROCESSADOR AVANÇADO
 * ============================================================================
 */

/* Diretivas condicionais */
#define DEBUG 1

#if DEBUG
    #define LOG(msg) printf("[LOG] %s\n", msg)
#else
    #define LOG(msg)  /* nada */
#endif

/* Verificação de macros definidas */
#ifdef __linux__
    /* código específico para Linux */
#elif defined(_WIN32)
    /* código específico para Windows */
#endif

/* Concatenação de tokens com ## */
#define CRIAR_VAR(nome) int var_##nome
/* CRIAR_VAR(teste) vira: int var_teste */

/* Stringificação com # */
#define STRINGIFY(x) #x
/* STRINGIFY(hello) vira: "hello" */

/* Pragmas (diretivas específicas do compilador) */
/* #pragma once  /* incluído no início do arquivo, evita inclusão múltipla */

/* ============================================================================
 * 19. EXEMPLOS PRÁTICOS PARA ESTRUTURA DE DADOS
 * ============================================================================
 */

/* --- LISTA ENCADEADA SIMPLES --- */
typedef struct NoSimples {
    int dado;
    struct NoSimples* prox;
} NoSimples;

NoSimples* criar_no(int valor) {
    NoSimples* novo = (NoSimples*)malloc(sizeof(NoSimples));
    if (novo) {
        novo->dado = valor;
        novo->prox = NULL;
    }
    return novo;
}

void inserir_inicio(NoSimples** cabeca, int valor) {
    NoSimples* novo = criar_no(valor);
    novo->prox = *cabeca;
    *cabeca = novo;
}

void liberar_lista(NoSimples* cabeca) {
    while (cabeca != NULL) {
        NoSimples* temp = cabeca;
        cabeca = cabeca->prox;
        free(temp);
    }
}

void imprimir_lista(NoSimples* cabeca) {
    printf("Lista: ");
    while (cabeca != NULL) {
        printf("%d -> ", cabeca->dado);
        cabeca = cabeca->prox;
    }
    printf("NULL\n");
}

/* --- PILHA (STACK) COM ARRAY --- */
#define MAX_PILHA 100
typedef struct {
    int dados[MAX_PILHA];
    int topo;
} Pilha;

void pilha_inicializar(Pilha* p) { p->topo = -1; }
bool pilha_vazia(Pilha* p) { return p->topo == -1; }
bool pilha_cheia(Pilha* p) { return p->topo == MAX_PILHA - 1; }

bool pilha_empilhar(Pilha* p, int valor) {
    if (pilha_cheia(p)) return false;
    p->dados[++p->topo] = valor;
    return true;
}

bool pilha_desempilhar(Pilha* p, int* valor) {
    if (pilha_vazia(p)) return false;
    *valor = p->dados[p->topo--];
    return true;
}

/* --- FILA (QUEUE) COM ARRAY CIRCULAR --- */
typedef struct {
    int dados[MAX_PILHA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void fila_inicializar(Fila* f) {
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
}

bool fila_vazia(Fila* f) { return f->tamanho == 0; }
bool fila_cheia(Fila* f) { return f->tamanho == MAX_PILHA; }

bool fila_enfileirar(Fila* f, int valor) {
    if (fila_cheia(f)) return false;
    f->fim = (f->fim + 1) % MAX_PILHA;
    f->dados[f->fim] = valor;
    f->tamanho++;
    return true;
}

bool fila_desenfileirar(Fila* f, int* valor) {
    if (fila_vazia(f)) return false;
    *valor = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % MAX_PILHA;
    f->tamanho--;
    return true;
}

void secao_exemplos_ed(void) {
    printf("\n=== 19. EXEMPLOS PRÁTICOS PARA ESTRUTURA DE DADOS ===\n");

    /* Lista Encadeada */
    NoSimples* lista = NULL;
    inserir_inicio(&lista, 30);
    inserir_inicio(&lista, 20);
    inserir_inicio(&lista, 10);
    imprimir_lista(lista);
    liberar_lista(lista);

    /* Pilha */
    Pilha p;
    pilha_inicializar(&p);
    pilha_empilhar(&p, 10);
    pilha_empilhar(&p, 20);
    pilha_empilhar(&p, 30);
    int val;
    printf("Pilha (LIFO): ");
    while (!pilha_vazia(&p)) {
        pilha_desempilhar(&p, &val);
        printf("%d ", val);
    }
    printf("\n");

    /* Fila */
    Fila f;
    fila_inicializar(&f);
    fila_enfileirar(&f, 10);
    fila_enfileirar(&f, 20);
    fila_enfileirar(&f, 30);
    printf("Fila (FIFO): ");
    while (!fila_vazia(&f)) {
        fila_desenfileirar(&f, &val);
        printf("%d ", val);
    }
    printf("\n");
}

/* ============================================================================
 * 20. BOAS PRÁTICAS E DICAS PARA ESTRUTURA DE DADOS
 * ============================================================================
 */

/*
 * 1. SEMPRE verifique se malloc/calloc/realloc retornou NULL
 * 2. SEMPRE libere memória alocada (free) - evite memory leaks
 * 3. Após free(ptr), defina ptr = NULL (evita dangling pointer)
 * 4. Use const para parâmetros que não devem ser modificados
 * 5. Use size_t para índices e tamanhos (não int)
 * 6. Prefira sizeof(variável) em vez de sizeof(tipo) - mais seguro
 * 7. Use typedef para simplificar declarações complexas
 * 8. Inicialize variáveis ao declarar (evita lixo de memória)
 * 9. Use asserts para invariantes (debug): assert(ptr != NULL);
 * 10. Compile com -Wall -Wextra -Werror para pegar erros cedo
 * 11. Use valgrind para detectar vazamentos de memória
 * 12. Não retorne ponteiros para variáveis locais (stack)! Use malloc ou parâmetros
 * 13. Cuidado com buffer overflow em strings (sempre use versões seguras)
 * 14. Documente suas structs e funções com comentários claros
 * 15. Separe interface (.h) da implementação (.c)
 */

/* ============================================================================
 * MAIN - PONTO DE ENTRADA DO PROGRAMA
 * ============================================================================
 * argc = quantidade de argumentos (incluindo o nome do programa)
 * argv = array de strings com os argumentos
 * argv[0] = nome do programa
 * argv[1] = primeiro argumento
 * ...
 */

int main(int argc, char* argv[]) {
    printf("============================================================\n");
    printf("  COLA COMPLETA DA LINGUAGEM C\n");
    printf("  Compile: gcc main.c -o main -Wall -Wextra -std=c11\n");
    printf("  Execute: ./main\n");
    printf("============================================================\n");

    /* Argumentos da linha de comando */
    printf("\nArgumentos recebidos: %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("  argv[%d] = %s\n", i, argv[i]);
    }

    /* Executa todas as seções */
    secao_tipos_de_dados();
    secao_operadores();
    secao_entrada_saida();
    secao_estruturas_controle();
    secao_funcoes();
    secao_arrays();
    secao_strings();
    secao_ponteiros();
    secao_structs();
    secao_unions();
    secao_enums();
    secao_typedef();
    secao_alocacao_dinamica();
    secao_arquivos();
    secao_ponteiros_funcoes();
    secao_exemplos_ed();

    printf("\n============================================================\n");
    printf("  FIM DA COLA. BONS ESTUDOS!\n");
    printf("============================================================\n");

    return EXIT_SUCCESS;  /* 0 = sucesso, != 0 = erro */
}
