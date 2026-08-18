// Crie uma Struct para Armazenar Dados de um Carro;
// Defina duas variáveis para armazenar os dados de um Carro
// Mostre os dados armazenados dos carros
// Troque o ano de fabricação dos carros
// Mostre os Dados Atualizados

#include <stdio.h>
#include <string.h>

typedef struct{
    int cod;
    char placa[10];
    char marca[15];
    double potencia;
    double quilometragem;
} Carro;

typedef struct {
    int dia;
    int mes;
    int ano
} Data;

int main(){

    Carro c1;
    Data d1;
    d1.dia = 25;
    d1.mes = 5;
    d1.ano = 2019;

    c1.cod = 1;
    strcpy(c1.placa, "AFKG-(4582)");
    strcpy(c1.marca, "MacLauren");
    c1.potencia = 375.25;
    c1.quilometragem = 12.55;

    printf("Codigo = %d \n", c1.cod);
    printf("Placa = %s \n", c1.placa);
    printf("Marca = %s \n", c1.marca);
    printf("Potência = %f \n", c1.potencia);
    printf("Quilometragem = %f \n", c1.quilometragem);
    printf("Ano de Fabricação = %d \n", d1.ano);
    printf("Dia de Fabricação = %d \n", d1.dia);
    printf("Mes de Fabricação = %d \n", d1.mes);

    // Trocando Ano de Fabricação
    d1.dia = 15;
    d1.mes = 9;
    d1.ano = 2006;

    printf("Após a Troca \n");
    printf("Ano de Fabricação = %d \n", d1.ano);
    printf("Dia de Fabricação = %d \n", d1.dia);
    printf("Mes de Fabricação = %d \n", d1.mes);
}
