// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

typedef struct Motor{
    int nrmMotor;
    int potencia;
    char combustivel[10];
} Motor;

typedef struct Rodas{
    int diametro;
    char nrmRoda[10];
} Rodas;

typedef struct Carro{
    int nrmChassi;
    char modelo[30];
    char cor[10];
    Motor mt;
    Rodas rd[4];
} Carro;


// Registrar Motor
void registrarMotor(Motor *mtr, int numMotor, int pot, char combust[10]){
    if(mtr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    mtr->nrmMotor = numMotor;
    mtr->potencia = pot;
    strcpy(mtr->combustivel, combust);
}

// Registrar Roda
void registrarRoda(Rodas *rod, int diam, char numRoda[10]){
    if(rod == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    rod->diametro=diam;
    strcpy(rod->nrmRoda, numRoda);
}

// Registrar Carro
void registrarCarro(Carro *cr, int numChassi, char modCarro[30], char corCarro[10], Motor motCarro, Rodas rodCarro){
    
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    cr->nrmChassi = numChassi;
    strcpy(cr->modelo, modCarro);
    strcpy(cr->cor, corCarro);
    cr->mt = motCarro;
    cr->rd[0] = rodCarro;
    cr->rd[1] = rodCarro;
    cr->rd[2] = rodCarro;
    cr->rd[3] = rodCarro;
}

// Instalar Motor no Carro
void instalarMotorCarro(Carro *cr, Motor mtr){
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }
    cr->mt = mtr;
}

// Instalar Roda no Carro
void instalarRodaCarro(Carro *cr, Rodas rods){
    if(cr == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    if(sizeof(cr->rd) < 4){
        printf("Carro Não Possui 4 Rodas");
    }

    cr->rd[0] = rods;
    cr->rd[1] = rods;
    cr->rd[2] = rods;
    cr->rd[3] = rods;
}

// Mostrar Carro
void mostrarCarro(Carro carro){
    printf("Número do Chassi: %d\n", carro.nrmChassi);
    printf("Modelo do Carro: %s\n", carro.modelo);
    printf("Cor do Carro: %s\n", carro.cor);
    printf("Potencia do Motor do Carro: %d\n", carro.mt.potencia);
    printf("Numero das Rodas do Carro: %s\n", carro.rd->nrmRoda);
}

int main(){

    struct Rodas roda;
    roda.diametro = 10;
    strcpy(roda.nrmRoda, "R13");

    struct Motor m1;
    m1.nrmMotor = 17;
    m1.potencia = 750;
    strcpy(m1.combustivel, "Gasolina");

    struct Carro c1;
    c1.nrmChassi = 25;
    strcpy(c1.modelo, "Hilux");
    strcpy(c1.cor, "Preto");
    c1.mt = m1;
    c1.rd[0] = roda;
    c1.rd[1] = roda;
    c1.rd[2] = roda;
    c1.rd[3] = roda;

    struct Carro c2;
    c2.nrmChassi = 25;
    strcpy(c2.modelo, "Civic");
    strcpy(c2.cor, "Branco");
    c2.mt = m1;
    c2.rd[0] = roda;
    c2.rd[1] = roda;
    c2.rd[2] = roda;
    c2.rd[3] = roda;

    struct Carro c3;
    registrarCarro(c3, 25, "Ferrari", "Vermelha", m1, roda);

    mostrarCarro(c1);
    mostrarCarro(c2);
    mostrarCarro(c3);

    return 0;
}


