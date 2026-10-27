/**
 * Exercício 3 - Simulador do processador Neander usando FILA
 *
 *  1. Fila de comandos: cada nó guarda o comando (mnemônico/operando) e a
 *     variável que ele altera (AC, MEM[x] ou PC).
 *  2. Parser: lê um pequeno programa em assembly Neander e insere os
 *     comandos na fila.
 *  3. Execução: os comandos são retirados da fila e executados; no final
 *     verifica-se o resultado.
 *
 * Sintaxe aceita pelo parser (maiúsculas ou minúsculas):
 *   ; comentário            (também vale #)
 *   .DATA endereço valor    define o conteúdo inicial de uma posição da memória
 *   rotulo: LDA 128         rótulo opcional antes de qualquer instrução
 *   JMP rotulo              desvios aceitam rótulo ou endereço numérico
 *   Números em decimal ou hexadecimal (0x80).
 *
 * Instruções: NOP STA LDA ADD OR AND NOT JMP JN JZ HLT
 *
 * Compilar e Executar:
 * gcc neander.c -o neander
 * ./neander              (executa dois programas de exemplo)
 * ./neander programa.asm (executa um programa seu)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define TAM_MEM 256
#define MAX_ROTULOS 64
#define TAM_ROTULO 32
#define MAX_CICLOS 10000

#define USO_LIVRE 0
#define USO_DADO 1
#define USO_CODIGO 2

// ---------------------------------------------------------------
// Tabela de instruções do Neander
// ---------------------------------------------------------------
typedef struct
{
    const char *nome;
    int codigo;         // opcode
    int temOperando;    // 1 = é seguida de um endereço
} InfoOp;

static const InfoOp TABELA_OPS[] = {
    {"NOP", 0x00, 0}, {"STA", 0x10, 1}, {"LDA", 0x20, 1}, {"ADD", 0x30, 1},
    {"OR",  0x40, 1}, {"AND", 0x50, 1}, {"NOT", 0x60, 0}, {"JMP", 0x80, 1},
    {"JN",  0x90, 1}, {"JZ",  0xA0, 1}, {"HLT", 0xF0, 0}};
#define NUM_OPS (sizeof(TABELA_OPS) / sizeof(TABELA_OPS[0]))

static int ehSalto(int codigo)
{
    return codigo == 0x80 || codigo == 0x90 || codigo == 0xA0;
}

// ---------------------------------------------------------------
// Fila de comandos
// ---------------------------------------------------------------
typedef struct comando
{
    int endereco;               // endereço da instrução na memória
    int linha;                  // linha do arquivo-fonte (para mensagens)
    const InfoOp *info;         // mnemônico e opcode
    int operando;               // endereço usado (se houver)
    char rotulo[TAM_ROTULO];    // rótulo usado como operando ("" se não houver)
    char alvo[16];              // variável alterada: "AC", "MEM[130]", "PC" ou "-"
    struct comando *proximo;
} Comando;

typedef struct filaCmd
{
    Comando *inicio;
    Comando *fim;
    int qtd;
} FilaCmd;

FilaCmd *criaFilaCmd()
{
    FilaCmd *f = (FilaCmd *)malloc(sizeof(FilaCmd));
    if (f == NULL)
        return NULL;
    f->inicio = NULL;
    f->fim = NULL;
    f->qtd = 0;
    return f;
}

void enfileiraCmd(FilaCmd *f, Comando *c)
{
    if (f == NULL || c == NULL)
        return;
    c->proximo = NULL;
    if (f->inicio == NULL)
        f->inicio = c;
    else
        f->fim->proximo = c;
    f->fim = c;
    f->qtd++;
}

Comando *desenfileiraCmd(FilaCmd *f)
{
    if (f == NULL || f->inicio == NULL)
        return NULL;
    Comando *c = f->inicio;
    f->inicio = c->proximo;
    c->proximo = NULL;
    f->qtd--;
    if (f->inicio == NULL)
        f->fim = NULL;
    return c;
}

void apagaFilaCmd(FilaCmd *f)
{
    if (f == NULL)
        return;
    Comando *c;
    while ((c = desenfileiraCmd(f)) != NULL)
        free(c);
    free(f);
}

// ---------------------------------------------------------------
// Máquina Neander (memória + registradores)
// ---------------------------------------------------------------
typedef struct maquina
{
    unsigned char mem[TAM_MEM];
    unsigned char uso[TAM_MEM];     // USO_LIVRE, USO_DADO ou USO_CODIGO
    unsigned char escrito[TAM_MEM]; // 1 = alterado por STA durante a execução
    unsigned char ac;               // acumulador (8 bits)
    int n, z;                       // flags: negativo e zero
    int ultimaInstrucao;            // endereço da última instrução do programa
    long ciclos;
} Maquina;

static void iniciaMaquina(Maquina *m)
{
    memset(m, 0, sizeof(Maquina));
    m->z = 1;                       // AC = 0 no início
}

// ---------------------------------------------------------------
// Parser
// ---------------------------------------------------------------
typedef struct
{
    char nome[TAM_ROTULO];
    int endereco;
} Rotulo;

// Grava a mensagem de erro e retorna 0
static int falha(char *erro, size_t tam, int linha, const char *fmt, ...)
{
    char msg[100];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(msg, sizeof msg, fmt, ap);
    va_end(ap);

    if (linha > 0)
        snprintf(erro, tam, "linha %d: %s", linha, msg);
    else
        snprintf(erro, tam, "%s", msg);
    return 0;
}

// Converte decimal ou hexadecimal (0x..) e confere o intervalo
static int numero(const char *s, int min, int max, int *out)
{
    char *fim;
    int base = (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) ? 16 : 10;
    long v = strtol(s, &fim, base);
    if (fim == s || *fim != '\0' || v < min || v > max)
        return 0;
    *out = (int)v;
    return 1;
}

static const InfoOp *buscaOp(const char *mnemonico)
{
    for (size_t i = 0; i < NUM_OPS; i++)
        if (strcmp(TABELA_OPS[i].nome, mnemonico) == 0)
            return &TABELA_OPS[i];
    return NULL;
}

static int ehRotuloValido(const char *s)
{
    if (s[0] == '\0' || strlen(s) >= TAM_ROTULO)
        return 0;
    if (!isalpha((unsigned char)s[0]) && s[0] != '_')
        return 0;
    for (const char *p = s; *p; p++)
        if (!isalnum((unsigned char)*p) && *p != '_')
            return 0;
    return 1;
}

// Lê o programa (texto) e insere os comandos na fila, na ordem em que aparecem.
// Também carrega os .DATA na memória. Retorna 1 se OK; senão 0 e a mensagem em erro.
// Em caso de erro, a fila fica com o que já foi lido (quem chama deve apagá-la).
int carregaPrograma(const char *texto, Maquina *m, FilaCmd *fila, char *erro, size_t tamErro)
{
    Rotulo rotulos[MAX_ROTULOS];
    int nRot = 0;
    int pc = 0;                 // endereço da próxima instrução
    int linha = 0;
    char buf[160];
    const char *p = texto;

    // ---------- 1ª passada: lê linha a linha ----------
    while (*p != '\0')
    {
        size_t len = strcspn(p, "\n");
        linha++;
        if (len >= sizeof buf)
            return falha(erro, tamErro, linha, "linha muito longa");
        memcpy(buf, p, len);
        buf[len] = '\0';
        p += len;
        if (*p == '\n')
            p++;

        for (char *q = buf; *q; q++)    // trata \r (arquivos do Windows)
            if (*q == '\r')
                *q = ' ';
        char *cmt = strpbrk(buf, ";#"); // remove comentário
        if (cmt)
            *cmt = '\0';

        // rótulo ("nome:")
        char *resto = buf;
        char *dp = strchr(buf, ':');
        if (dp)
        {
            *dp = '\0';
            char *ini = buf;
            while (isspace((unsigned char)*ini))
                ini++;
            char *fimR = ini + strlen(ini);
            while (fimR > ini && isspace((unsigned char)fimR[-1]))
                *--fimR = '\0';

            if (!ehRotuloValido(ini))
                return falha(erro, tamErro, linha, "rótulo inválido '%s'", ini);
            for (int i = 0; i < nRot; i++)
                if (strcmp(rotulos[i].nome, ini) == 0)
                    return falha(erro, tamErro, linha, "rótulo '%s' repetido", ini);
            if (nRot >= MAX_ROTULOS)
                return falha(erro, tamErro, linha, "rótulos demais");

            snprintf(rotulos[nRot].nome, TAM_ROTULO, "%s", ini);
            rotulos[nRot].endereco = pc;
            nRot++;
            resto = dp + 1;
        }

        char t1[32], t2[32], t3[32], t4[32];
        int n = sscanf(resto, "%31s %31s %31s %31s", t1, t2, t3, t4);
        if (n < 1)
            continue;               // linha vazia (ou só com rótulo)
        for (char *q = t1; *q; q++)
            *q = (char)toupper((unsigned char)*q);

        // ---- diretiva .DATA endereço valor ----
        if (strcmp(t1, ".DATA") == 0)
        {
            int ender, val;
            if (n != 3)
                return falha(erro, tamErro, linha, "uso: .DATA endereco valor");
            if (!numero(t2, 0, TAM_MEM - 1, &ender))
                return falha(erro, tamErro, linha, "endereço inválido '%s' (0 a 255)", t2);
            if (!numero(t3, -128, 255, &val))
                return falha(erro, tamErro, linha, "valor inválido '%s' (-128 a 255)", t3);
            if (m->uso[ender] != USO_LIVRE)
                return falha(erro, tamErro, linha, "endereço %d já está ocupado", ender);

            m->mem[ender] = (unsigned char)val;
            m->uso[ender] = USO_DADO;
            continue;
        }

        // ---- instrução ----
        const InfoOp *op = buscaOp(t1);
        if (op == NULL)
            return falha(erro, tamErro, linha, "comando desconhecido '%s'", t1);
        if (n != 1 + op->temOperando)
            return falha(erro, tamErro, linha,
                         op->temOperando ? "%s exige exatamente um operando"
                                         : "%s não tem operando", op->nome);

        int operando = 0;
        char rot[TAM_ROTULO] = "";
        if (op->temOperando)
        {
            if (!numero(t2, 0, TAM_MEM - 1, &operando))
            {
                if (ehSalto(op->codigo) && ehRotuloValido(t2))
                    snprintf(rot, sizeof rot, "%s", t2);    // resolvido na 2ª passada
                else
                    return falha(erro, tamErro, linha, "operando inválido '%s'", t2);
            }
        }

        int tam = 1 + op->temOperando;
        if (pc + tam > TAM_MEM)
            return falha(erro, tamErro, linha, "o programa não cabe na memória");
        for (int i = 0; i < tam; i++)
            if (m->uso[pc + i] != USO_LIVRE)
                return falha(erro, tamErro, linha,
                             "instrução no endereço %d colide com outro dado/código", pc);
        for (int i = 0; i < tam; i++)
            m->uso[pc + i] = USO_CODIGO;

        Comando *c = (Comando *)calloc(1, sizeof(Comando));
        if (c == NULL)
            return falha(erro, tamErro, linha, "sem memória");
        c->endereco = pc;
        c->linha = linha;
        c->info = op;
        c->operando = operando;
        snprintf(c->rotulo, sizeof c->rotulo, "%s", rot);
        enfileiraCmd(fila, c);

        m->ultimaInstrucao = pc;
        pc += tam;
    }

    if (fila->qtd == 0)
        return falha(erro, tamErro, 0, "o programa não tem nenhuma instrução");

    // ---------- 2ª passada: resolve rótulos, valida e define o "alvo" ----------
    for (Comando *c = fila->inicio; c != NULL; c = c->proximo)
    {
        int codigo = c->info->codigo;

        if (c->rotulo[0] != '\0')
        {
            int achou = 0;
            for (int i = 0; i < nRot; i++)
                if (strcmp(rotulos[i].nome, c->rotulo) == 0)
                {
                    c->operando = rotulos[i].endereco;
                    achou = 1;
                    break;
                }
            if (!achou)
                return falha(erro, tamErro, c->linha, "rótulo '%s' não definido", c->rotulo);
        }

        if (ehSalto(codigo))
        { // o destino precisa ser o início de uma instrução
            int ok = 0;
            for (const Comando *d = fila->inicio; d != NULL; d = d->proximo)
                if (d->endereco == c->operando)
                {
                    ok = 1;
                    break;
                }
            if (!ok)
                return falha(erro, tamErro, c->linha,
                             "desvio para %d, que não é o início de uma instrução", c->operando);
            snprintf(c->alvo, sizeof c->alvo, "PC");
        }
        else if (codigo == 0x10)
        {
            if (m->uso[c->operando] == USO_CODIGO)
                return falha(erro, tamErro, c->linha,
                             "STA escreveria na área de código (endereço %d)", c->operando);
            snprintf(c->alvo, sizeof c->alvo, "MEM[%d]", c->operando);
        }
        else if (codigo == 0x20 || codigo == 0x30 || codigo == 0x40 ||
                 codigo == 0x50 || codigo == 0x60)
            snprintf(c->alvo, sizeof c->alvo, "AC");
        else
            snprintf(c->alvo, sizeof c->alvo, "-");

        // grava o código de máquina na memória (como num Neander de verdade)
        m->mem[c->endereco] = (unsigned char)codigo;
        if (c->info->temOperando)
            m->mem[c->endereco + 1] = (unsigned char)c->operando;
    }
    return 1;
}

// ---------------------------------------------------------------
// Execução
// ---------------------------------------------------------------
static void atualizaFlags(Maquina *m)
{
    m->n = (m->ac & 0x80) != 0;
    m->z = (m->ac == 0);
}

// Executa UM comando. Retorna 1 se houve desvio (destino em *destino).
// Em HLT, coloca 1 em *parar.
static int executaComando(Maquina *m, const Comando *c, char *efeito, size_t tam,
                          int *destino, int *parar)
{
    int a = c->operando;
    int desvio = 0;

    switch (c->info->codigo)
    {
    case 0x00: // NOP
        snprintf(efeito, tam, "nada a fazer");
        break;
    case 0x10: // STA: MEM[a] <- AC
        m->mem[a] = m->ac;
        m->escrito[a] = 1;
        snprintf(efeito, tam, "MEM[%d] = %d", a, m->ac);
        break;
    case 0x20: // LDA: AC <- MEM[a]
        m->ac = m->mem[a];
        atualizaFlags(m);
        snprintf(efeito, tam, "AC = %d", m->ac);
        break;
    case 0x30: // ADD: AC <- AC + MEM[a]  (8 bits, estouro "dá a volta")
        m->ac = (unsigned char)(m->ac + m->mem[a]);
        atualizaFlags(m);
        snprintf(efeito, tam, "AC = %d", m->ac);
        break;
    case 0x40: // OR
        m->ac = (unsigned char)(m->ac | m->mem[a]);
        atualizaFlags(m);
        snprintf(efeito, tam, "AC = %d", m->ac);
        break;
    case 0x50: // AND
        m->ac = (unsigned char)(m->ac & m->mem[a]);
        atualizaFlags(m);
        snprintf(efeito, tam, "AC = %d", m->ac);
        break;
    case 0x60: // NOT
        m->ac = (unsigned char)(~m->ac);
        atualizaFlags(m);
        snprintf(efeito, tam, "AC = %d", m->ac);
        break;
    case 0x80: // JMP
        desvio = 1;
        break;
    case 0x90: // JN: desvia se N = 1
        desvio = m->n;
        break;
    case 0xA0: // JZ: desvia se Z = 1
        desvio = m->z;
        break;
    case 0xF0: // HLT
        *parar = 1;
        snprintf(efeito, tam, "parada");
        break;
    }

    if (ehSalto(c->info->codigo))
    {
        *destino = a;
        if (desvio)
            snprintf(efeito, tam, "PC -> %d", a);
        else
            snprintf(efeito, tam, "sem desvio");
    }
    return desvio;
}

// Gira a fila (tira do início e põe no fim) até o comando de "endereco" ficar na frente
static void rotacionaAte(FilaCmd *f, int endereco)
{
    while (f->inicio->endereco != endereco)
        enfileiraCmd(f, desenfileiraCmd(f));
}

static void descreveComando(const Comando *c, char *buf, size_t tam)
{
    if (!c->info->temOperando)
        snprintf(buf, tam, "%s", c->info->nome);
    else if (c->rotulo[0] != '\0')
        snprintf(buf, tam, "%s %d (%s)", c->info->nome, c->operando, c->rotulo);
    else
        snprintf(buf, tam, "%s %d", c->info->nome, c->operando);
}

/**
 * Executa o programa usando a fila.
 *
 * Como uma fila só permite retirar do início, a execução é CIRCULAR:
 *   - retira o comando da frente e o executa;
 *   - devolve-o ao FIM da fila (a fila sempre contém o programa inteiro,
 *     em ordem de endereço, só que "girada");
 *   - fluxo normal: o próximo comando já é o da frente;
 *   - desvio (JMP/JN/JZ): gira a fila até o destino ficar na frente
 *     (funciona para desvios para frente e para trás, ou seja, laços).
 */
int executaPrograma(Maquina *m, FilaCmd *fila, char *erro, size_t tamErro)
{
    printf("\n--- Execução ---\n");
    printf("%5s %4s  %-16s %-14s %4s %2s %2s\n", "Ciclo", "End.", "Comando", "Efeito", "AC", "N", "Z");

    int parar = 0;
    while (!parar)
    {
        if (m->ciclos >= MAX_CICLOS)
            return falha(erro, tamErro, 0,
                         "limite de %d ciclos atingido (laço infinito?)", MAX_CICLOS);

        Comando *c = desenfileiraCmd(fila);
        m->ciclos++;

        char efeito[40] = "";
        char desc[40];
        int destino = 0;
        int desvio = executaComando(m, c, efeito, sizeof efeito, &destino, &parar);

        descreveComando(c, desc, sizeof desc);
        printf("%5ld %4d  %-16s %-14s %4d %2d %2d\n",
               m->ciclos, c->endereco, desc, efeito, m->ac, m->n, m->z);

        enfileiraCmd(fila, c);          // volta para o fim da fila

        if (parar)
            break;
        if (desvio)
            rotacionaAte(fila, destino);
        else if (c->endereco == m->ultimaInstrucao)
            return falha(erro, tamErro, 0, "o programa chegou ao fim sem executar HLT");
    }
    return 1;
}

// ---------------------------------------------------------------
// Apresentação e verificação
// ---------------------------------------------------------------
static void mostraFilaCmd(const FilaCmd *f)
{
    printf("\n--- Fila de comandos (%d) ---\n", f->qtd);
    printf("%5s %6s  %-16s %s\n", "End.", "Linha", "Comando", "Altera");
    for (const Comando *c = f->inicio; c != NULL; c = c->proximo)
    {
        char desc[40];
        descreveComando(c, desc, sizeof desc);
        printf("%5d %6d  %-16s %s\n", c->endereco, c->linha, desc, c->alvo);
    }
}

static void mostraDadosIniciais(const Maquina *m)
{
    printf("\nDados iniciais:");
    int algum = 0;
    for (int i = 0; i < TAM_MEM; i++)
        if (m->uso[i] == USO_DADO)
        {
            printf(" MEM[%d]=%d", i, m->mem[i]);
            algum = 1;
        }
    printf(algum ? "\n" : " (nenhum)\n");
}

static void mostraResultado(const Maquina *m)
{
    printf("\n--- Resultado ---\n");
    printf("AC = %d   N = %d   Z = %d   (ciclos: %ld)\n", m->ac, m->n, m->z, m->ciclos);
    printf("Posições alteradas por STA:");
    int alguma = 0;
    for (int i = 0; i < TAM_MEM; i++)
        if (m->escrito[i])
        {
            printf(" MEM[%d]=%d", i, m->mem[i]);
            alguma = 1;
        }
    printf(alguma ? "\n" : " (nenhuma)\n");
}

static int confere(const Maquina *m, int endereco, int esperado)
{
    int ok = (m->mem[endereco] == (unsigned char)esperado);
    printf("Verificação: MEM[%d] = %d (esperado %d) -> %s\n",
           endereco, m->mem[endereco], esperado, ok ? "OK" : "ERRADO");
    return ok;
}

// Carrega, mostra a fila, executa e (opcionalmente) verifica.
// endEsperado < 0 = não verificar. Retorna 1 se tudo deu certo.
static int executaTexto(const char *titulo, const char *texto, int endEsperado, int valEsperado)
{
    Maquina m;
    iniciaMaquina(&m);
    FilaCmd *fila = criaFilaCmd();
    char erro[120] = "";
    int ok = 0;

    printf("\n==================== %s ====================\n", titulo);
    if (fila == NULL)
    {
        printf("Erro: sem memória.\n");
        return 0;
    }

    if (!carregaPrograma(texto, &m, fila, erro, sizeof erro))
    {
        printf("Erro no programa: %s\n", erro);
    }
    else
    {
        mostraFilaCmd(fila);
        mostraDadosIniciais(&m);
        if (!executaPrograma(&m, fila, erro, sizeof erro))
        {
            printf("Erro na execução: %s\n", erro);
        }
        else
        {
            mostraResultado(&m);
            ok = (endEsperado < 0) ? 1 : confere(&m, endEsperado, valEsperado);
        }
    }

    apagaFilaCmd(fila);
    return ok;
}

// ---------------------------------------------------------------
// Programas de exemplo
// ---------------------------------------------------------------
static const char PROG_SOMA[] =
    "; Soma dois numeros: MEM[130] = MEM[128] + MEM[129]\n"
    ".DATA 128 5\n"
    ".DATA 129 7\n"
    "LDA 128     ; AC <- MEM[128]\n"
    "ADD 129     ; AC <- AC + MEM[129]\n"
    "STA 130     ; MEM[130] <- AC\n"
    "HLT\n";

static const char PROG_MULT[] =
    "; Multiplica por somas repetidas: MEM[130] = MEM[128] * MEM[129]\n"
    ".DATA 128 4    ; A (valor somado a cada volta)\n"
    ".DATA 129 3    ; B (contador de voltas)\n"
    ".DATA 130 0    ; resultado\n"
    ".DATA 131 -1   ; constante -1\n"
    "laco: LDA 129\n"
    "      JZ fim   ; se B = 0, terminou\n"
    "      LDA 130\n"
    "      ADD 128   ; resultado += A\n"
    "      STA 130\n"
    "      LDA 129\n"
    "      ADD 131   ; B = B - 1\n"
    "      STA 129\n"
    "      JMP laco\n"
    "fim:  HLT\n";

// ---------------------------------------------------------------
// Programa principal
// ---------------------------------------------------------------
static char *leArquivo(const char *caminho)
{
    FILE *f = fopen(caminho, "rb");
    if (f == NULL)
        return NULL;

    fseek(f, 0, SEEK_END);
    long tam = ftell(f);
    rewind(f);
    if (tam < 0 || tam > 1000000)
    {
        fclose(f);
        return NULL;
    }

    char *buf = (char *)malloc((size_t)tam + 1);
    if (buf == NULL)
    {
        fclose(f);
        return NULL;
    }
    size_t lidos = fread(buf, 1, (size_t)tam, f);
    buf[lidos] = '\0';
    fclose(f);
    return buf;
}

int main(int argc, char *argv[])
{
    if (argc >= 2)
    {
        char *texto = leArquivo(argv[1]);
        if (texto == NULL)
        {
            fprintf(stderr, "Erro: não foi possível ler '%s'.\n", argv[1]);
            return 1;
        }
        int ok = executaTexto(argv[1], texto, -1, 0);
        free(texto);
        return ok ? 0 : 1;
    }

    int ok1 = executaTexto("Exemplo 1 - Soma: 5 + 7", PROG_SOMA, 130, 12);
    int ok2 = executaTexto("Exemplo 2 - Multiplicação: 4 x 3 (usa laço)", PROG_MULT, 130, 12);
    return (ok1 && ok2) ? 0 : 1;
}