/*
Implemente a função void codigoAsc(char *p, int n) para percorrer uma string
e exibir cada caractere acompanhado do seu respectivo valor numérico na
tabela ASCII.
*/

#include <stdio.h>
#include <stdlib.h>

void codigoAsc(char *p, int n){
    for (int i=0; i<n; i++) printf("%c = %d \n", *(p+i), *(p+i)); 
}

int main(){

    char *str;
    int n;
    
    printf("Insira o Tamanho para a String: \n");
    scanf("%d", &n);

    printf("Insira os Elementos na String: \n");
    for(int i = 0; i < n; i++){
        printf("String[%d] = ", i+1);
        scanf("%s", str + i);
    }

    printf("String = %s \n", str);
    codigoAsc(str, n);
    
    return 0;
}
