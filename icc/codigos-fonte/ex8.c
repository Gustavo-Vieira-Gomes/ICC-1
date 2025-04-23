#include <stdio.h>
#include <math.h>

int main() {
    int sinal = -1;
    double soma=0, pi;

    for (int i = 1; i <= 1000; i+=2) {
        sinal *= -1;
        soma += (1/(i*i*i)) * sinal;
    }
    pi = cbrt(soma * 32);
    printf("O valor de pi é: %lf\n", pi);

    return 0;
}