#include <stdio.h>

void main() {
    float result=0.0;

    for (float i = 1.0, j = 1.0; i < 100.0, j <= 50.0; i += 2.0, j++) {
        result += (i/j);
    }
    printf("Resultado é: %.2f\n", result);
}
