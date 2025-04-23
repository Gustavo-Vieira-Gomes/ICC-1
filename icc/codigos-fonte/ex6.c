#include <stdio.h>

int main() {
    float massa, massai;
    int contador=0, hours, minutes, seconds;
    scanf("%f", &massa);
    massai = massa;
    while (massa >= 0.5)
    {
        massa /= 2;
        contador += 1;
    }

    seconds = contador * 50;
    minutes = seconds / 60;
    seconds = seconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    printf("Massa inicial: %f\n", massai);
    printf("Massa final: %f\n", massa);
    printf("%d Horas, %d Minutos, %d Segundos\n", hours, minutes, seconds);
}