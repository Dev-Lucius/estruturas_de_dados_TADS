#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estruturas Básicas --> Structs
typedef struct {
    int num;
    char fileira;
    int flag_livre; // 1 = Livre, 0 = Ocupada
} Poltrona;

typedef struct {
    Poltrona poltronas[15];
    int num_sala;
} Sala;

typedef struct {
    int dia, mes, ano;
} Data;

typedef struct {
    char nomeFilme[30];
    Data dataFilme;
    int horaFilme;
    Sala salaReservada;
} Sessao;

// Funções
// Passagem por REFERÊNCIA -> Modificam os Dados
// Regra --> recebe um PONTEIRO para a struct ja existente
//   - e preenche os campos. NAO faz malloc aqui!
//   - O malloc eh feito quem CHAMA a funcao.
void cadastrarPoltrona(Poltrona *p, int num, char fileira){
    if(p == NULL){
        fprintf(stderr, "Error \n");
        return;
    }

    p->num = num;
    p->fileira = fileira;
    p->flag_livre = 1; // Como ela foi récem Criada, logo, ela está disponível
}

void inicializarSala(Sala *s, int numSala){
    s->num_sala = numSala;

    // Preenchendo todas as 15 Poltronas
    for(int i = 0; i < 15; i++){
        s->poltronas[i].num = i + 1;
        s->poltronas[i].fileira = 'A';
        s->poltronas[i].flag_livre = 1; // De início, todas estão Livres
    }
}

void cadastrarData(Data *d, int dia, int mes, int ano){
    if(d == NULL){
        fprintf(stderr, "Error \n");
        return; 
    }

    d->dia = dia;
    d->mes = mes;
    d->ano = ano;
}

void cadastartSessao(Sessao *s, char *filme, Data d, int hora, Sala sala){
    if(s == NULL){
        fprintf(stderr, "Erro ao Cadastrar Sessão! \n");
        return; 
    }

    strcpy(s->nomeFilme, filme);
    s->dataFilme = d;
    s->horaFilme = hora;
    s->salaReservada = sala; // Aqui vamos copiar a Sala Inteira (bem como as 15 Poltronas)
}

void comprarPoltrona(Sessao *s, int posPoltrona){
    // Sessão Não ser Nula
    if((s == NULL)){
        fprintf(stderr, "Erro ao Cadastrar Sessão! \n");
        return;  
    }

    // Validando Posições
    if(posPoltrona < 0 || posPoltrona >= 15){
        fprintf(stderr, "Posição Inválida \n");
        return;
    }

    Poltrona *p = &s->salaReservada.poltronas[posPoltrona];

    // Agora vamos Verificar se a Poltrona está Livre
    if(p->flag_livre == 0){
        printf("A Poltrona %d Já Está Ocupada! \n", posPoltrona);
        return;
    }

    p->flag_livre = 0; // Atualizando a Ocupação da Poltrona !!!
    printf("Poltrona %d Comprada Com Sucesso! \n", posPoltrona);
}

void cancelarPoltrona(Sessao *s, int posPoltrona){
    // Sessão Não ser Nula
    if((s == NULL)){
        fprintf(stderr, "Erro ao Cadastrar Sessão! \n");
        return;  
    }

    // Validando Posições
    if(posPoltrona < 0 || posPoltrona >= 15){
        fprintf(stderr, "Posição Inválida \n");
        return;
    }

    Poltrona *p = &s->salaReservada.poltronas[posPoltrona];

    // Agora vamos Verificar se a Poltrona está Ocupada (só cancela se tiver sido comprada)
    if(p->flag_livre == 1){
        printf("A Poltrona %d Já Está Livre! Não há compra para cancelar.\n", posPoltrona);
        return;
    }

    p->flag_livre = 1; // Como a Compra foi Cancelada, logo a Poltrona voltou a ficar disponível!
    printf("Poltrona %d Cancelada Com Sucesso! \n", posPoltrona);
}


// Funções
// Passagem por VALOR -> Apenas Exibição
void mostrarPoltrona(Poltrona p){
    
    char disponibilidade[20];
    strcpy(disponibilidade, "Indisponível");
    if(p.flag_livre == 1){
        strcpy(disponibilidade, "Disponível");
    }
    
    printf("Número da Poltrona: %d \n", p.num);
    printf("Fileira da Poltrona: %c \n", p.fileira);
    printf("Disponibilidade: %s \n", disponibilidade);
}

void mostrarMapaSala(Sala s){
    printf("Número da Sala: %d \n", s.num_sala);

    for(int i = 0; i < 15; i++){
        printf("[%c%d %s]   ",
                s.poltronas[i].fileira,
                s.poltronas[i].num,
                s.poltronas[i].flag_livre ? "Livre" : "Ocup");
        if ((i + 1) % 5 == 0) printf ("\n"); // Aqui vamos Quebrar A Linha a Cada 5 Iterações do For
    }
}

void mostrarData(Data d){
    printf("Data da Sessão Atual \n");
    printf("Dia: %d \n", d.dia);
    printf("Mes: %d \n", d.mes);
    printf("Ano: %d \n", d.ano); 
}

void mostrarSessao(Sessao s){
    printf("Sessão Atual \n");
    printf("Filme: %s \n", s.nomeFilme);
    printf("Data: %02d/%02d/%d \n", s.dataFilme.dia, s.dataFilme.mes, s.dataFilme.ano);
    printf("Horário: %02d:00 \n", s.horaFilme);
    printf("Número daSala Reservada: %d \n", s.salaReservada.num_sala);
    mostrarMapaSala(s.salaReservada);
}

// Menu Principal
// Requisito (5)
int menuPrincipal(){
    int op;
    printf("\n DataStruct Cine \n");
    printf("1) Comprar Poltrona \n");
    printf("2) Cancelar Compra de Poltrona \n");
    printf("3) Ver Relatório de Poltronas \n");
    printf("4) Ver Todas as Sessões \n");
    printf("0) Sair \n");
    scanf("%d", &op);
    return op;
}

// Requisito (3)
void mostrarRelatorioSessao(Sessao *s) {
    int livres = 0, ocupadas = 0;

    printf("\n=== RELATORIO: %s ===\n", s->nomeFilme);
    printf("Data: %02d/%02d/%d | Horario: %02d:00 | Sala: %d\n\n",
           s->dataFilme.dia, s->dataFilme.mes, s->dataFilme.ano,
           s->horaFilme, s->salaReservada.num_sala);

    printf("POLTRONAS LIVRES:\n");
    for (int i = 0; i < 15; i++) {
        if (s->salaReservada.poltronas[i].flag_livre) {
            printf("  %c%d ", s->salaReservada.poltronas[i].fileira,
                   s->salaReservada.poltronas[i].num);
            livres++;
        }
    }
    if (livres == 0) printf("  (Nenhuma)");
    printf("\n\nPOLTRONAS VENDIDAS:\n");
    for (int i = 0; i < 15; i++) {
        if (!s->salaReservada.poltronas[i].flag_livre) {
            printf("  %c%d ", s->salaReservada.poltronas[i].fileira,
                   s->salaReservada.poltronas[i].num);
            ocupadas++;
        }
    }
    if (ocupadas == 0) printf("  (Nenhuma)");
    printf("\n\nTotal: %d livres | %d vendidas\n", livres, ocupadas);
}

void mostrarTodasSessoesCinema(Sessao sessoes[], int n) {
    printf("\nSESSOES DISPONIVEIS\n\n");
    for (int i = 0; i < n; i++) {
        mostrarSessao(sessoes[i]);
    }
    printf("\n");
}


int main(){

    // Requisitos
    // -1. O sistema deve prever a reserva de pelo menos quatro sessões de cinema, com filmes diferentes;
    // -2. O sistemas deve gerenciar a venda de poltronas, uma poltrona não pode ser vendida duas ou mais vezes na mesma sessão do cinema
    // -3. O sistema deve mostrar todas as poltronas vendidas e livres
    // -4. O usuário poderá cancelar um compra de poltrona em um filme, desde que selecione o filme e a poltrona comprada;
    // -5. Deve possui um Menu com as Opções:
    //      * 1) Compra de Poltrona
    //           - O Cliente Escolhe a Sessão
    //           - O sistema Mostrar o Mapa da Sala
    //           - O Cliente escolhe a poltrona para compra
    //           - O Sistema mostra a mapa da Sala Atualizado
    //      * 2) Cancelar Uma Compra de Poltrona
    //            - O Cliente informa a sessão, filme e a Poltrona que quer cancelar a compra  
    //            - O sistema deve liberar a poltrona para outro cliente comprar  
    //            - O sistema mostrar o mapa da Sala Atualizado


    // Requisito (1)
    Sessao sessoes[4];
    
    strcpy(sessoes[0].nomeFilme, "Oppenheimer");
    sessoes[0].dataFilme.dia = 15; 
    sessoes[0].dataFilme.mes = 9; 
    sessoes[0].dataFilme.ano = 2025;
    sessoes[0].horaFilme = 14;
    inicializarSala(&sessoes[0].salaReservada, 1);

    strcpy(sessoes[1].nomeFilme, "Barbie");
    sessoes[1].dataFilme.dia = 15; 
    sessoes[1].dataFilme.mes = 9; 
    sessoes[1].dataFilme.ano = 2025;
    sessoes[1].horaFilme = 17;
    inicializarSala(&sessoes[1].salaReservada, 2);

    strcpy(sessoes[2].nomeFilme, "Super Mario Bros");
    sessoes[2].dataFilme.dia = 16; 
    sessoes[2].dataFilme.mes = 9; 
    sessoes[2].dataFilme.ano = 2025;
    sessoes[2].horaFilme = 16;
    inicializarSala(&sessoes[2].salaReservada, 3);

    strcpy(sessoes[3].nomeFilme, "Duna: Parte Dois");
    sessoes[3].dataFilme.dia = 15; 
    sessoes[3].dataFilme.mes = 9; 
    sessoes[3].dataFilme.ano = 2025;
    sessoes[3].horaFilme = 20;
    inicializarSala(&sessoes[3].salaReservada, 20);


    int opcaoEscolhida = -1;  // Evita Lixo de Memória

    while(opcaoEscolhida != 0){
        
        opcaoEscolhida = menuPrincipal();

        switch (opcaoEscolhida){
            case 1: {
                printf("Comprar Poltrona \n");
                mostrarTodasSessoesCinema(sessoes, 4); 

                int idSessao;
                printf("Digite o numero da sessao (0 a 3): ");
                scanf("%d", &idSessao);

                if(idSessao < 0 || idSessao >= 4){
                    printf("\n Sessão Inválida \n");
                    break;
                }

                mostrarMapaSala(sessoes[idSessao].salaReservada);

                int pos;
                printf("Digite o numero da poltrona (0 a 14) \n");
                scanf("%d", &pos);
                
                // CORREÇÃO 3: passando Sessao* em vez de Sala*
                comprarPoltrona(&sessoes[idSessao], pos);

                printf("\nATUALIZAÇÃO\n");
                mostrarMapaSala(sessoes[idSessao].salaReservada);
                break;
            }

            case 2: {
                printf("Cancelar Compra \n");
                mostrarTodasSessoesCinema(sessoes, 4);  

                int idSessao;
                printf("Digite o numero da sessao (0 a 3): ");
                scanf("%d", &idSessao);

                if(idSessao < 0 || idSessao >= 4){
                    printf("\n Sessão Inválida \n");
                    break;
                }

                printf("Sessão Selecionada: %s \n", sessoes[idSessao].nomeFilme);
                mostrarMapaSala(sessoes[idSessao].salaReservada);

                int pos;
                printf("Digite o numero da poltrona (0 a 14) \n");
                scanf("%d", &pos);

                cancelarPoltrona(&sessoes[idSessao], pos);
                printf("\nATUALIZAÇÃO\n");
                mostrarMapaSala(sessoes[idSessao].salaReservada);
                break;
            }
            case 3: {
                printf("Relatório de Poltronas \n");
                mostrarTodasSessoesCinema(sessoes, 4);  

                int idSessao;
                printf("Digite o numero da sessao (0 a 3): ");
                scanf("%d", &idSessao);

                if(idSessao < 0 || idSessao >= 4){
                    printf("\n Sessão Inválida \n");
                    break;
                }

                mostrarRelatorioSessao(&sessoes[idSessao]);
                break;
            }

            case 4: {
                mostrarTodasSessoesCinema(sessoes, 4);
                break;
            }

            case 0: 
                printf("Encerrando... \n");
                break;
            
            default:
                printf("Opção Inválida \n");
                break;
        }
    }

    return 0;
}