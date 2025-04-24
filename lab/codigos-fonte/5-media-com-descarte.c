#include <stdio.h>

int main(void) {
    double number, menor;
    double soma = 0.0;

    scanf("%lf", &number);
    menor = number;
    soma += number;

    scanf("%lf", &number);
    soma += number;
    if (number < menor){
        menor = number;
    }

    scanf("%lf", &number);
    soma += number;
    if (number < menor){
        menor = number;
    }

    scanf("%lf", &number);
    soma += number;
    if (number < menor){
        menor = number;
    }

    printf("%.4lf", (soma - menor)/3.0);
}
