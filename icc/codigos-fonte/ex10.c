#include <stdio.h>

int main() {
    int n, main=0, first=0, second=0, flag = 0;

    printf("Informe quantos valores terão os vetores iniciais: ");
    scanf("%d", &n);

    int vet1[n], vet2[n], mainVet[2*n];

    printf("Informe os valores do vetor 1:\n");
    for (int i=0; i < n; i++) {
        scanf("%d", &vet1[i]);
    }

    printf("Informe os valores do vetor 2:\n");
    for (int i=0; i < n; i++) {
        scanf("%d", &vet2[i]);
    }

    while (main < 2*n)
     {
        printf("%d %d %d %d %d %d \n", first, vet1[first], second, vet2[second], main, mainVet[main]);
        if (first == n && second == n){
            break;
        }

        if (first == n) {
            mainVet[main] = vet2[second];
            second++;
        }

        if (second == n) {
            mainVet[main] = vet1[first];
            first++;
        }

        if (first != n && second != n){
            if (vet1[first] < vet2[second]) {
                mainVet[main] = vet1[first];
                first++;
            } else {
                mainVet[main] = vet2[second];
                second++;
            }
        }
        main++;
    }

    for (int i=0; i < 2*n; i++) {
        printf("%d", mainVet[i]);
    }

}
