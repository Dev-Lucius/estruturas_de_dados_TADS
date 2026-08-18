// Crie uma Struct para Armazenar Dados de um Filme;
// Defina duas variáveis para armazenar os dados de um Filme
// Mostre os dados armazenados do Filme
// Troque o ano de lançamento do filmes
// Mostre os Dados Atualizados

#include <stdio.h>
#include <string.h>

typedef struct{
    int cod;
    char nome[50];
    char diretor[50];
    float avaliacao;
    double arrecadacao;
    int anoLançamento;
} Filme;

int main(){

    Filme f1;

    f1.cod = 1;
    strcpy(f1.nome, "Homem Aranha: Um Novo Dia");
    strcpy(f1.diretor, "Destin Daniel Cretton");
    f1.avaliacao = 9.87;
    f1.arrecadacao = 26000000.90;
    f1.anoLançamento = 2026;

    printf("Codigo = %d \n", f1.cod);
    printf("Nome Filme = %s \n", f1.nome);
    printf("Diretor = %s \n", f1.diretor);
    printf("Avaliação = %.2f \n", f1.avaliacao);
    printf("Arrecadação = %.5f \n", f1.arrecadacao);
    printf("Ano de Lançamento = %d \n", f1.anoLançamento);

    printf("Alterando Ano de Lançamento \n");
    f1.anoLançamento = 2025;
    printf("Ano de Lançamento = %d \n", f1.anoLançamento);
}
