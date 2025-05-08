#include <stdio.h>

int main() {
    double soma = 1.0, fatorial=1.0;
    int n, sinal = -1 ;

    scanf("%d", &n);

    for (int i=2; i <= n; i++) {
        sinal *= -1;
        fatorial *= i;
        soma += (sinal * (1.0 / fatorial));
    }

    printf("%lf", soma);

}