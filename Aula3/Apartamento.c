/*
1° Parte
Defina uma estrutura para armazenar dados de um apartamento:
- Ex: Nome do condomínio, número, andar, quantidade cômodos, valor do aluguel, valor condomínio, box e etc.
    1. Crie dois apartamentos, atribua valores aos seus membros (ap101, ap201);
    2. Crie uma função para imprimir os valores de um apartamento (passagem por valor);
    3. Crie uma função para alterar o valor do aluguel de um apartamento em 10% (passagem por referência)


2° Parte
Crie dois ponteiros de apartamentos, utilize alocação dinâmica (malloc). Após, atribua valores aos campos dos apartamentos (ex. 301 e 401).
-  Após mostre o apartamento criado (301);
- Defina uma função que recebe um apartamento e retorna o box do apartamento;
- Mostre apenas o box do apartamento 301;
- Defina um função para criar um novo apartamento, a função recebe por parâmetro os dados do apartamento 
  (Condomínio, andar, número, etc) e retorna o ponteiro do novo apartamento (atribua ao 401);
-  Mostre os dados do apartamento 401 criado
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Struct do Apartamento
typedef struct {
    char condominio[30];
    int num, andar, qtd_comodos, box;
    double v_aluguel, v_condominio;
} Apartamento;

// 1. Função para imprimir (passagem por valor)
void mostrarDadosApartamento(Apartamento ap) {
    printf("Condominio = %s \n", ap.condominio);
    printf("Numero = %d \n", ap.num);
    printf("Andar = %d \n", ap.andar);
    printf("Quantidade de Comodos = %d \n", ap.qtd_comodos);
    printf("Box = %d \n", ap.box);
    printf("Valor do Condominio = R$ %.2f | Valor do Aluguel = R$ %.2f \n", ap.v_condominio, ap.v_aluguel);
    printf("---------------------------------------------------\n");
}        

// 2. Função para alterar aluguel (passagem por referência)
void alteraAluguelEm10porcentos(Apartamento *ap) {
    ap->v_aluguel = ap->v_aluguel * 1.10;
}

// 3. Função Para retornar o numero do Box
int retornarBoxApartamento(Apartamento ap){
    
    if(ap.box == NULL){
        return 1;
    }

    printf("Box = %d \n", ap.box);
    return 0;
}

// 4. Função para Criar um Novo Apartamento (aloca dinamicamente e retorna o ponteiro)
Apartamento* criarNovoApartamento(char *condominio, int num, int andar, int qtd_comodos, int box, double v_aluguel, double v_condomio){
    
    Apartamento *ap = (Apartamento*)malloc(sizeof(Apartamento));

    strcpy(ap->condominio, condominio);
    ap->num = num;
    ap->andar = andar;
    ap->qtd_comodos = qtd_comodos;
    ap->box = box;
    ap->v_aluguel = v_aluguel;
    ap->v_condominio = v_condomio;

    return ap;
}

// 5. Função para Alterar o valor do Aluguel de um Apartamento (Passagem por Referência)
void alterarValorAluguel(Apartamento *ap, double valorAluguel){
    ap->v_aluguel = valorAluguel;
}

int main() {

    // 1°e Parte
    Apartamento ap101;
    strcpy(ap101.condominio, "Residencial Central");
    ap101.num = 101;
    ap101.andar = 1;
    ap101.qtd_comodos = 3;
    ap101.box = 12;
    ap101.v_aluguel = 1200.00;
    ap101.v_condominio = 350.00;

    Apartamento ap201;
    strcpy(ap201.condominio, "Residencial Central");
    ap201.num = 201;
    ap201.andar = 2;
    ap201.qtd_comodos = 4;
    ap201.box = 24;
    ap201.v_aluguel = 1800.00;
    ap201.v_condominio = 400.00;

    // TESTES
    printf("=== DADOS INICIAIS ===\n\n");
    printf("--- AP 101 ---\n");
    mostrarDadosApartamento(ap101);

    printf("--- AP 201 ---\n");
    mostrarDadosApartamento(ap201);

    // Aplicando reajuste de 10% no ap101
    printf("\n>>> Aplicando reajuste de 10%% no aluguel do AP 101...\n\n");
    alteraAluguelEm10porcentos(&ap101);

    printf("=== DADOS APOS REAJUSTE ===\n\n");
    printf("--- AP 101 ---\n");
    mostrarDadosApartamento(ap101);

    printf("--- AP 201 (Permanece inalterado) ---\n");
    mostrarDadosApartamento(ap201);


    // 2° Parte
    Apartamento *ap301;
    Apartamento *ap401;

    ap301 = (Apartamento *)malloc(sizeof(Apartamento));
    ap401 = (Apartamento *)malloc(sizeof(Apartamento));

    strcpy(ap301->condominio, "Residencial do Sul");
    ap301->num = 25;
    ap301->andar = 5;
    ap301->qtd_comodos = 3;
    ap301->box = 3;
    ap301->v_aluguel = 329.00;
    ap301->v_condominio = 250.00;

    // TESTES
    printf("=== DADOS DO AP 301 ===\n\n");
    mostrarDadosApartamento(*ap301);
    
    printf("--- Box do 301 --- \n");
    retornarBoxApartamento(*ap301);

    printf("=== DADOS DO AP 401 === \n\n");
    ap401 = criarNovoApartamento("Residencia do Norte", 76, 10, 5, 3, 500.00, 750.00);
    mostrarDadosApartamento(*ap401);

    printf("Antes da Alteração \n");
    printf("Aluguel do AP 101 = %.2f \n", ap101.v_aluguel);
    printf("Aluguel do AP 102 = %.2f \n", ap201.v_aluguel);
    printf("Aluguel do AP 102 = %.2f \n", ap301->v_aluguel);
    printf("Aluguel do AP 102 = %2.f \n", ap401->v_aluguel);

    // Após a Alteração
    alterarValorAluguel(&ap101, 500.00);
    alterarValorAluguel(&ap201, 600.00);
    alterarValorAluguel(ap301, 700.00); // Já é ponteiro
    alterarValorAluguel(ap401, 800.00); // Já é ponteiro

    printf("Após da Alteração \n");
    printf("Aluguel do AP 101 = %.2f \n", ap101.v_aluguel);
    printf("Aluguel do AP 102 = %.2f \n", ap201.v_aluguel);
    printf("Aluguel do AP 102 = %.2f \n", ap301->v_aluguel);
    printf("Aluguel do AP 102 = %.2f \n", ap401->v_aluguel);

    return 0;
}
