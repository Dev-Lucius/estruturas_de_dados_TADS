// Exercícios do Apartamento
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Apartamento Apartamento;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct {
    int cod;
    char nome[50];
    char cpf[15];
} Proprietario;

struct Apartamento {
    char condominio[30];
    int num;
    int andar;
    int qtd_comodos;
    int box;
    double v_aluguel;
    double v_condominio;
    Data compra;
    Proprietario *dono;   /* ponteiro unico: varios aps podem apontar pro mesmo dono */
};

/* 1. Mostrar apartamento (passagem por valor) */
void mostrarDadosApartamento(Apartamento ap) {
    printf("| Condominio: %s", ap.condominio);
    printf("| Numero: %d | Andar: %d | Comodos: %d | Box: %d", ap.num, ap.andar, ap.qtd_comodos, ap.box);
    printf("| Aluguel: R$ %.2f | Condominio: R$ %.2f", ap.v_aluguel, ap.v_condominio);
    printf("| Data de Compra: %02d/%02d/%d ", ap.compra.dia, ap.compra.mes, ap.compra.ano);
    
    if (ap.dono != NULL) {
        printf("| Dono: %s (CPF: %s)", ap.dono->nome, ap.dono->cpf);
    } else {
        printf("| Dono: (sem proprietario) ");
    }
}

/* 2. Alterar aluguel em 10% (passagem por referencia) */
void alteraAluguelEm10porcentos(Apartamento *ap) {
    if (ap != NULL) {
        ap->v_aluguel = ap->v_aluguel * 1.10;
    }
}

/* 3. Retornar box do apartamento */
int retornarBoxApartamento(Apartamento ap) {
    return ap.box;
}

/* 4. Criar novo apartamento dinamicamente */
Apartamento* criarNovoApartamento(const char *condominio, int num, int andar,
                                   int qtd_comodos, int box,
                                   double v_aluguel, double v_condominio,
                                   int dia, int mes, int ano) {
    Apartamento *ap = (Apartamento *)malloc(sizeof(Apartamento));
    if (ap == NULL) {
        fprintf(stderr, "Erro ao alocar apartamento!\n");
        exit(EXIT_FAILURE);
    }
    strcpy(ap->condominio, condominio);
    ap->num = num;
    ap->andar = andar;
    ap->qtd_comodos = qtd_comodos;
    ap->box = box;
    ap->v_aluguel = v_aluguel;
    ap->v_condominio = v_condominio;
    ap->compra.dia = dia;
    ap->compra.mes = mes;
    ap->compra.ano = ano;
    ap->dono = NULL;   /* importante: inicializa ponteiro */
    return ap;
}

/* 5. Alterar valor do aluguel (passagem por referencia) */
void alterarValorAluguel(Apartamento *ap, double valorAluguel) {
    if (ap != NULL) {
        ap->v_aluguel = valorAluguel;
    }
}

/* 6. Mostrar proprietario */
void mostrarProprietario(const Proprietario *p) {
    if (p == NULL) return;
    printf(" === DADOS DO PROPRIETARIO === ");
    printf("Codigo: %d", p->cod);
    printf("Nome:   %s", p->nome);
    printf("CPF:    %s", p->cpf);
    printf("\n");
}

/* 7. Vender apartamento: atualiza data e vincula novo dono */
void venderApartamento(Apartamento *ap, Proprietario *pr, int d, int m, int a) {
    if (ap == NULL || pr == NULL) return;

    ap->compra.dia = d;
    ap->compra.mes = m;
    ap->compra.ano = a;
    ap->dono = pr;   /* apartamento agora aponta para o novo proprietario */

    printf("Apartamento %d vendido para %s em %02d/%02d/%d\n\n", ap->num, pr->nome, d, m, a);
}

/* ============================================================
 *  MAIN
 * ============================================================ */

int main() {

    Proprietario *antonio = (Proprietario *)malloc(sizeof(Proprietario));
    antonio->cod = 1;
    strcpy(antonio->nome, "Antonio Lima");
    strcpy(antonio->cpf, "123.456.789-00");

    Proprietario *andressa = (Proprietario *)malloc(sizeof(Proprietario));
    andressa->cod = 2;
    strcpy(andressa->nome, "Andressa Lopes");
    strcpy(andressa->cpf, "987.654.321-00");

    /* Novo proprietario (para troca do dono do AP 101) */
    Proprietario *carlos = (Proprietario *)malloc(sizeof(Proprietario));
    carlos->cod = 3;
    strcpy(carlos->nome, "Carlos Souza");
    strcpy(carlos->cpf, "111.222.333-44");

    /* --------------------------------------------------------
     *  1a PARTE: Apartamentos 101 e 201 (na stack)
     * -------------------------------------------------------- */
    Apartamento ap101;
    strcpy(ap101.condominio, "Residencial Central");
    ap101.num = 101;
    ap101.andar = 1;
    ap101.qtd_comodos = 3;
    ap101.box = 12;
    ap101.v_aluguel = 1200.00;
    ap101.v_condominio = 350.00;
    ap101.compra.dia = 15;
    ap101.compra.mes = 3;
    ap101.compra.ano = 2015;
    ap101.dono = antonio;   /* Antonio eh dono do 101 */

    Apartamento ap201;
    strcpy(ap201.condominio, "Residencial Central");
    ap201.num = 201;
    ap201.andar = 2;
    ap201.qtd_comodos = 4;
    ap201.box = 24;
    ap201.v_aluguel = 1800.00;
    ap201.v_condominio = 400.00;
    ap201.compra.dia = 29;
    ap201.compra.mes = 9;
    ap201.compra.ano = 2013;
    ap201.dono = andressa;  /* Andressa eh dona do 201 */

    printf("========== DADOS INICIAIS ==========\n\n");
    mostrarDadosApartamento(ap101);
    mostrarDadosApartamento(ap201);

    /* Reajuste de 10% no AP 101 */
    printf(">>> Reajuste de 10%% no AP 101...\n\n");
    alteraAluguelEm10porcentos(&ap101);
    mostrarDadosApartamento(ap101);

    Apartamento *ap301 = criarNovoApartamento(
        "Residencial do Sul", 25, 5, 3, 3,
        329.00, 250.00, 12, 6, 2022);

    Apartamento *ap401 = criarNovoApartamento(
        "Residencia do Norte", 76, 10, 5, 3,
        500.00, 750.00, 22, 1, 2025);

    printf("========== APARTAMENTOS DINAMICOS ==========\n\n");
    mostrarDadosApartamento(*ap301);

    printf("--- Box do AP 301: %d ---\n\n", retornarBoxApartamento(*ap301));

    mostrarDadosApartamento(*ap401);

    
    alterarValorAluguel(&ap101, 500.00);
    alterarValorAluguel(&ap201, 600.00);
    alterarValorAluguel(ap301, 700.00);
    alterarValorAluguel(ap401, 800.00);

    printf("========== APOS ALTERACAO DE ALUGUEL ==========\n\n");
    printf("AP 101: R$ %.2f\n", ap101.v_aluguel);
    printf("AP 201: R$ %.2f\n", ap201.v_aluguel);
    printf("AP 301: R$ %.2f\n", ap301->v_aluguel);
    printf("AP 401: R$ %.2f\n\n", ap401->v_aluguel);

    printf("========== PROPRIETARIOS ==========\n\n");
    mostrarProprietario(antonio);
    mostrarProprietario(andressa);

    /* Troca do dono do AP 101 (Antonio -> Carlos) */
    printf(">>> Trocando dono do AP 101...\n");
    ap101.dono = carlos;
    mostrarDadosApartamento(ap101);

    printf(">>> Vendendo AP 201 para Carlos...\n");
    venderApartamento(&ap201, carlos, 20, 8, 2025);
    mostrarDadosApartamento(ap201);

    printf("========== BLOCO DE 4 APARTAMENTOS ==========\n\n");

    Apartamento bloco[4];

    /* AP 1 */
    strcpy(bloco[0].condominio, "Edificio Solaris");
    bloco[0].num = 501; bloco[0].andar = 5; bloco[0].qtd_comodos = 2;
    bloco[0].box = 10; bloco[0].v_aluguel = 900.00; bloco[0].v_condominio = 300.00;
    bloco[0].compra.dia = 1; bloco[0].compra.mes = 1; bloco[0].compra.ano = 2020;
    bloco[0].dono = antonio;   /* Antonio tem 2 aps! */

    /* AP 2 */
    strcpy(bloco[1].condominio, "Edificio Solaris");
    bloco[1].num = 502; bloco[1].andar = 5; bloco[1].qtd_comodos = 3;
    bloco[1].box = 11; bloco[1].v_aluguel = 1100.00; bloco[1].v_condominio = 350.00;
    bloco[1].compra.dia = 15; bloco[1].compra.mes = 3; bloco[1].compra.ano = 2021;
    bloco[1].dono = antonio;   /* MESMO Antonio! */

    /* AP 3 */
    strcpy(bloco[2].condominio, "Edificio Solaris");
    bloco[2].num = 601; bloco[2].andar = 6; bloco[2].qtd_comodos = 3;
    bloco[2].box = 20; bloco[2].v_aluguel = 1300.00; bloco[2].v_condominio = 400.00;
    bloco[2].compra.dia = 10; bloco[2].compra.mes = 7; bloco[2].compra.ano = 2022;
    bloco[2].dono = andressa;  /* Andressa tem 2 aps! */

    /* AP 4 */
    strcpy(bloco[3].condominio, "Edificio Solaris");
    bloco[3].num = 602; bloco[3].andar = 6; bloco[3].qtd_comodos = 4;
    bloco[3].box = 21; bloco[3].v_aluguel = 1500.00; bloco[3].v_condominio = 450.00;
    bloco[3].compra.dia = 5; bloco[3].compra.mes = 12; bloco[3].compra.ano = 2023;
    bloco[3].dono = andressa;  /* MESMA Andressa! */

    for (int i = 0; i < 4; i++) {
        mostrarDadosApartamento(bloco[i]);
    }

    /* Prova de que eh o mesmo ponteiro */
    printf(">>> PROVA: mesmo dono em varios apartamentos\n");
    printf("Dono do 501: %s\n", bloco[0].dono->nome);
    printf("Dono do 502: %s\n", bloco[1].dono->nome);
    printf("Mesmo endereco? %s\n\n",
           (bloco[0].dono == bloco[1].dono) ? "SIM!" : "NAO");

    free(ap301);
    free(ap401);
    free(antonio);
    free(andressa);
    free(carlos);

    return 0;
}
