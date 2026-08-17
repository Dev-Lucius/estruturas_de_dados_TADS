/*
Escreva uma função void inverteVetor(int *v, int n) que inverta os elementos de
um vetor no próprio local (in-place) utilizando dois ponteiros (um apontando
para o início e outro para o fim)
*/

#include <stdio.h>
#include <stdlib.h>

void inverterVetor(int *v, int n){

    for(int i = 0; i < n / 2; i++){
        // Armazena-se o Valor Atual do Ponteiro em uma Variável Temporária
        int temp = *(v + i);

        // Atribui-se o valor do elemento correspondente 
        // Localizado na posição oposta do vetor
        *(v + i) = *(v + (n - 1 - i));
        
        // Coloca-se o valor armazenado em temp na posição oposta
        // finalizando a troca
        *(v + (n - 1 - i)) = temp;
    }
}

int main(){
    
    int *pont;
    int num;

    printf("Insira o Tamanho para o Ponteiro: \n");
    scanf("%d", &num);

    // Aloca a memória dinamicamente para 'num' elementos
    pont = (int*) malloc(num *sizeof(int));

    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = ", i+1);
        // &pont[i] == pont + 1
        scanf("%d", (pont + i));
    }

    inverterVetor(pont, num);
    
    printf("Ponteiro Invertido \n");
    for(int i = 0; i < num; i++){
        printf("Ponteiro[%d] = %d \n", i+1, *(pont+i));
    }

    free(pont);
    return 0;
}
