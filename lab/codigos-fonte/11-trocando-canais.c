#include <stdio.h>

void swap(int *a, int *b) {
    int intermediario;

    intermediario = *a;
    *a = *b;
    *b = intermediario;
}


int main() {
    int canal1, canal2, *controle1, *controle2;

    scanf("%d %d", &canal1, &canal2);
    controle1 = &canal1;
    controle2 = &canal2;

    swap(controle1, controle2);

    printf("%d %d\n", canal1, canal2);

    return 0;
}