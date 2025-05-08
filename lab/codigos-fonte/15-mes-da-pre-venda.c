#include <stdio.h>

int main() {
    int mes[31], maior;

    for (int i=0; i < 31; i++) {
        scanf("%d", &mes[i]);
        if (i == 0) {
            maior = mes[i];
        } else {
            if (mes[i] > maior) {
                maior = mes[i];
            }
        }
    }

    printf("%d\n", maior);
    for (int i = 0; i< 31; i++) {
        if (mes[i] == maior) {
            printf("%d\n", i+1);
        }
    }
}