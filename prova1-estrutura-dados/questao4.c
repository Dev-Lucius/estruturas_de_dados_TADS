// Códigos em C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Compilar e Executar
// gcc codigo.c -o codigo
// ./codigo

typedef struct Motor {
    int nrmMotor;
    int potencia;
    char combustivel[10];
} Motor;

typedef struct Rodas {
    int diametro;
    char nrmRoda[10];
} Rodas;

typedef struct Carro {
    int nrmChassi;
    char modelo[30];
    char cor[10];
    Motor mt;
    Rodas rd[4];
} Carro;

// Copia texto respeitando o tamanho do destino (evita overflow)
static void copiarTexto(char *dest, size_t tam, const char *orig) {
    snprintf(dest, tam, "%s", orig);
}

// Registrar Motor
void registrarMotor(Motor *mtr, int numMotor, int pot, const char *combust) {
    if (mtr == NULL) {
        fprintf(stderr, "Erro: motor NULL\n");
        return;
    }

    mtr->nrmMotor = numMotor;
    mtr->potencia = pot;
    copiarTexto(mtr->combustivel, sizeof(mtr->combustivel), combust);
}

// Registrar Roda
void registrarRoda(Rodas *rod, int diam, const char *numRoda) {
    if (rod == NULL) {
        fprintf(stderr, "Erro: roda NULL\n");
        return;
    }

    rod->diametro = diam;
    copiarTexto(rod->nrmRoda, sizeof(rod->nrmRoda), numRoda);
}

// Registrar Carro (recebe as 4 rodas)
void registrarCarro(Carro *cr, int numChassi, const char *modCarro,
                    const char *corCarro, Motor motCarro, Rodas rodasCarro[4]) {
    if (cr == NULL) {
        fprintf(stderr, "Erro: carro NULL\n");
        return;
    }

    cr->nrmChassi = numChassi;
    copiarTexto(cr->modelo, sizeof(cr->modelo), modCarro);
    copiarTexto(cr->cor, sizeof(cr->cor), corCarro);
    cr->mt = motCarro;

    for (int i = 0; i < 4; i++) {
        cr->rd[i] = rodasCarro[i];
    }
}

// Instalar Motor no Carro
void instalarMotorCarro(Carro *cr, Motor mtr) {
    if (cr == NULL) {
        fprintf(stderr, "Erro: carro NULL\n");
        return;
    }
    cr->mt = mtr;
}

// Instalar uma Roda em uma posição do Carro (0 a 3)
void instalarRodaCarro(Carro *cr, Rodas rod, int posicao) {
    if (cr == NULL) {
        fprintf(stderr, "Erro: carro NULL\n");
        return;
    }

    if (posicao < 0 || posicao >= 4) {
        fprintf(stderr, "Erro: posicao de roda invalida (%d)\n", posicao);
        return;
    }

    cr->rd[posicao] = rod;
}

// Mostrar Carro (ponteiro const evita copiar a struct inteira)
void mostrarCarro(const Carro *carro) {
    printf("Numero do Chassi: %d\n", carro->nrmChassi);
    printf("Modelo do Carro: %s\n", carro->modelo);
    printf("Cor do Carro: %s\n", carro->cor);
    printf("Potencia do Motor: %d\n", carro->mt.potencia);
    printf("Combustivel: %s\n", carro->mt.combustivel);

    for (int i = 0; i < 4; i++) {
        printf("Roda %d: %s (diametro %d)\n",
               i + 1, carro->rd[i].nrmRoda, carro->rd[i].diametro);
    }
    printf("\n");
}

int main() {

    Motor m1;
    registrarMotor(&m1, 17, 750, "Gasolina");

    Rodas jogoRodas[4];
    for (int i = 0; i < 4; i++) {
        registrarRoda(&jogoRodas[i], 10, "R13");
    }

    Carro c1, c2, c3;
    registrarCarro(&c1, 25, "Hilux", "Preto", m1, jogoRodas);
    registrarCarro(&c2, 26, "Civic", "Branco", m1, jogoRodas);
    registrarCarro(&c3, 27, "Ferrari", "Vermelha", m1, jogoRodas);

    // Exemplo: trocar a roda da posição 0 do c3
    Rodas rodaNova;
    registrarRoda(&rodaNova, 12, "R15");
    instalarRodaCarro(&c3, rodaNova, 0);

    mostrarCarro(&c1);
    mostrarCarro(&c2);
    mostrarCarro(&c3);

    return 0;
}
