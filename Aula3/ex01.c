// Crie uma Struct para Armazenar Dados de um Carro;

#include <stdio.h>
#include <string.h>

typedef struct{
    int cod;
    char placa[10];
    char marca[15];
    double potencia;
    double quilometragem;
} Carro;

int main(){

    Carro c1;

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
}