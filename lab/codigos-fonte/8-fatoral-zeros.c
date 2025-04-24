#include <stdio.h>

void main(){
    int m5 = 0, numero, index;

    scanf("%d", &numero);

    for (numero; numero > 1; numero--){
        index = numero;
        while (index % 5 == 0){
          m5 += 1;
        index = index / 5;
        }
    }

    printf("%d", m5);
}
