#include <stdio.h>

int main() {
    double x, resultado = 0.0;

    scanf("%lf", &x);

    // Parte Inteira
    while (x >= 2)
    {
        x /= 2;
        resultado += 1.0;
    }

    while (x < 1)
    {
        x *= 2;
        resultado -= 1.0;
    }
    
    // Parte Fracionária
    double fracao = 0.5;
    for (int i=0; i<20; i++) {
        x *= x;
        if (x >= 2) {
            x /= 2;
            resultado += fracao;
        }
        fracao = fracao ;
    }

    printf("O resultado é %lf", resultado);
}