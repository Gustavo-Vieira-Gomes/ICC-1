#include <stdio.h>

int fatorial(int n) {
    int fat = 0;
    while (n > 1) {
        fat = n * (n-1);
        n = n - 1;
    }
    return fat;
}

float potencia(float num, int index) {
    float pot = 1;
    while (index > 0) {
        pot = pot * num;
        index = index - 1;
    }
    return pot;
}

int main() {
    float x, resultado;
    printf("Escreva o valor de x: ");
    scanf("%f", &x);

    resultado = x;
    int sinal = 1;
    for (int i=0; i <= 36; i = i + 2) {
        sinal *= -1;
        if (i % 2 == 0) {
            resultado = resultado + potencia(x, i + 2) / fatorial(2*(i+2)-1) * sinal;
        } else {
            resultado = resultado + potencia(x, i + 2) / fatorial(2*(i+2)-1) * sinal;
        }
    }
    printf ("O valor final é: %f\n", resultado);

    return 0;
}