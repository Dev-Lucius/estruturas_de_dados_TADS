/*
    1) Defina uma estrutura Motor (double potencia, int modelo, double consumo)
    2) Inclua na estrutura Carro, um motor;
    3) Defina valores para os atributos de um carro e seu motor;
    4) Mostre os dados do carro;
    5) Crie uma função para trocar o consumo do motor, passe a estrutura carro para função;
    6) Crie uma função para consultar o modelo do motor, passe a estrutura carro como parâmetro, mostre o modelo do motor
*/

#include <stdio.h>
#include <string.h>

typedef struct{
    double potencia;
    char modelo[30];
    double consumo;
} Motor;

typedef struct{
    int cod;
    char placa[10];
    char marca[15];
    double quilometragem;
    Motor motor;
} Carro;

int main(){

    Carro c1;

    // Carro
    c1.cod = 1;
    strcpy(c1.placa, "AFKG-(4582)");
    strcpy(c1.marca, "MacLauren");
    c1.quilometragem = 12.55;

    // Motor
    c1.motor.potencia = 375.25;
    strcpy(c1.motor.modelo, "BMW V12");
    c1.motor.consumo = 46.78;

    printf("Dados do Carro \n");
    printf("Código = %d \n", c1.cod);
    printf("Placa do Carro = %s \n", c1.placa);
    printf("Marca do Carro = %s \n", c1.marca);
    printf("Quilometragem = %f \n", c1.quilometragem);

    printf("\nDados do Motor do Carro \n");
    printf("Potência do Motor = %f \n", c1.motor.potencia);
    printf("Modelo do Motor = %s \n", c1.motor.modelo);
    printf("Consumo do Carro = %f \n", c1.motor.consumo);

    return 0;
}
