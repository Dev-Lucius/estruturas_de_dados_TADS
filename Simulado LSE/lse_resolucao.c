// Resolução completa - Lista de Exercícios: Lista1 LSE.pdf

/*
    - Compilar: gcc -Wall -Wextra -std=c11 -o lse lse_resolucao.c
    - Executar: ./lse
*/

/*
    - Organização da Resolução
        * Parte 0 --> Estruturas e Funções
        * respostas.md
         --> Exercícios 1 a 10 (Diagnóstico + versão Corrigida)
        * questionario.md --> Questionário de Verdadeiro / Falso + Justificativa
        * main() --> Demonstra Cada Questão Na Prática

    - Padrão Adotado em Cada Questão
        * "ERRO" --> o que está errado no código da Lista
        * "POR QUÊ"--> A explicação conceitual
        * "CORREÇÂO" --> a função correta
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Parte 0

#define TAM_NOME 50
#define TAM_MAT 15

// Nó da lista 
typedef struct aluno{
    char nome[TAM_NOME];
    char matricula[TAM_MAT];
    struct aluno *proximo;
} Aluno;

// "Cabeça da Lista"
// Guarda apenas o endereço do primeiro nó
// se ests ponteiro for perdido, a lista inteira se perde !!
typedef struct{
    Aluno *primeiro;
} LSE;

// Função Criar Aluno
/*
    - Aloca e Inicializa o Nó (Correção do Ex1 + Justificativa na Parte 1) 
*/
Aluno *criarAluno(const char *nome, const char *matricula){
    Aluno *novo = (Aluno*) malloc(sizeof(Aluno));

    // Verificação
    if(novo == NULL){
        return NULL;
    }

    // snprintf sempre respeita o tamanho vetor
    /*
        - snprintf() tem a exata mesma função que printf(), mas com uma diferença crucial
            * Ao invés de apenas exibir o Resultado diretamente na Tela;
            * Ele formata e salva o texto dentro de uma variável de texto (um array de char)
            * O "n" no nome traz a ideia de Segurança --> Você é Obrigado a Passa o Tamanho Máximo Suportado pela Variável
        
        - snprintf(destino, tamanho_maximo, "texto com %especificadores", variaveis);
            * destino --> O array no qual as Variáveis serão Alocadas
            * tamanho_maximo --> O Limite de Bytes que podem ser gravados
            * format-string e variaveis --> : Funcionam exatamente igual ao printf tradicional

    */
    // strcpy funciona mas não respeita o tamanho do vetor, logo, temos mais risco de Buffer Overflow (Estouro de Memória)
    snprintf(novo->nome, TAM_NOME, "%s", nome);
    snprintf(novo->matricula, TAM_MAT, "%s", matricula);

    // A linha que falta no Ex1 do PDF
    novo->proximo = NULL;
    return novo;
}

// Demonstração Prática

static void titulo(const char *txt) {
    printf("\n=== %s ===\n", txt);
}
 
/* Monta uma lista com 5 alunos, de Ana a Elisa (usa insereFim). */
static void montaTurma(LSE *lista) {
    const char *nomes[5] = {"Ana", "Bruno", "Carla", "Diego", "Elisa"};
    const char *mats[5]  = {"2024001", "2024002", "2024003", "2024004", "2024005"};
    for (int i = 0; i < 5; i++) {
        insereFim(lista, criarAluno(nomes[i], mats[i]));
    }
}
 
int main(void) {
    LSE turma;
    inicializaLista(&turma);
 
    titulo("Q1 - Alocacao segura (proximo inicializado com NULL)");
    Aluno *juca = criarAluno("Juca da silva!", "9999");
    printf("   nome = %s | proximo == NULL? %s\n", juca->nome,
           juca->proximo == NULL ? "sim" : "NAO");
    free(juca);
 
    titulo("Q2 - Insercao no inicio (ordem correta): insere Carla, Bruno, Ana");
    insereInicio(&turma, criarAluno("Carla", "2024003"));
    insereInicio(&turma, criarAluno("Bruno", "2024002"));
    insereInicio(&turma, criarAluno("Ana",   "2024001"));
    imprimeLista(&turma);           /* esperado: Ana, Bruno, Carla */
    apagaLista(&turma);
 
    titulo("Q4 - Insercao no fim (inclusive em lista vazia)");
    montaTurma(&turma);
    imprimeLista(&turma);           /* esperado: Ana..Elisa, e termina! */
 
    titulo("Q3 - Busca por matricula (achou / nao achou / lista vazia)");
    Aluno *a = buscaMatricula(&turma, "2024003");
    printf("   2024003 -> %s\n", a ? a->nome : "(nao encontrado)");
    a = buscaMatricula(&turma, "0000000");
    printf("   0000000 -> %s\n", a ? a->nome : "(nao encontrado)");
    LSE vazia;
    inicializaLista(&vazia);
    a = buscaMatricula(&vazia, "2024001");
    printf("   lista vazia -> %s (sem crash)\n", a ? a->nome : "(nao encontrado)");
 
    titulo("Q6 - Contagem");
    printf("   turma: %d alunos (esperado 5) | vazia: %d (esperado 0)\n",
           contaAlunos(&turma), contaAlunos(&vazia));
 
    titulo("Q7 - Insercao por posicao: Juca na posicao 2; posicao 99 (invalida)");
    if (!inserePosicao(&turma, 2, criarAluno("Juca", "2024099"))) {
        printf("   falhou\n");
    }
    Aluno *invalido = criarAluno("Fantasma", "0");
    if (!inserePosicao(&turma, 99, invalido)) {
        printf("   posicao 99 recusada, liberando o no que sobrou\n");
        free(invalido);             /* quem chamou continua dono do nó */
    }
    imprimeLista(&turma);           /* esperado: Ana, Juca, Bruno, ... */
 
    titulo("Q9 - Impressao (do-while com avanco do ponteiro)");
    imprimeLista(&turma);
 
    titulo("Q10 - Ordem invertida SEM destruir a lista");
    printf("  recursao:\n");
    imprimeInvertida(&turma);
    printf("  vetor auxiliar:\n");
    imprimeInvertidaVetor(&turma);
    printf("  lista original intacta (1o nome): %s\n", turma.primeiro->nome);
 
    titulo("Q10 - Inversao in-place (altera a lista!)");
    inverteLista(&turma);
    printf("  apos inverteLista -> 1o nome: %s (a lista MUDOU)\n",
           turma.primeiro->nome);
    inverteLista(&turma);
    printf("  apos inverter de novo -> 1o nome: %s (restaurada)\n",
           turma.primeiro->nome);
 
    titulo("Q5 - Remocao no inicio (inclusive em lista vazia)");
    printf("   removeInicio em lista vazia -> %d (0 = nada feito, sem crash)\n",
           removeInicio(&vazia));
    int removeu = removeInicio(&turma);   /* separado do printf: a ordem de
                                            avaliação dos argumentos é indefinida */
    printf("   removeInicio na turma       -> %d | agora: %d alunos\n",
           removeu, contaAlunos(&turma));
 
    titulo("Q8 - Apagar a lista liberando cada no");
    apagaLista(&turma);
    printf("   alunos restantes: %d | primeiro == NULL? %s\n",
           contaAlunos(&turma), turma.primeiro == NULL ? "sim" : "NAO");
 
    titulo("PARTE 2 - Gabarito Verdadeiro/Falso");
    imprimeGabarito();
 
    return 0;