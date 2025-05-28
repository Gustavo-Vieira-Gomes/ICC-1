#include <stdio.h>

void bubblesort(int* vet, int tamanho){
    int flag = 0;

    while (flag != 1)
    {
        flag = 1;
        for(int i = 0; i < tamanho - 1; i++){
            if (vet[i] > vet[i+1]) {
                flag = 0;
                int intermediario = vet[i];
                vet[i] = vet[i+1];
                vet[i+1] = intermediario;
            }
        }
    }

    for (int j=0; j< tamanho; j++){
        if (j < tamanho - 1){
            printf("%d ", vet[j]);
        } else {
            printf("%d", vet[j]);
        }
    }
    
}

int main() {
    int tamanho;
    scanf("%d", &tamanho);

    int vet[tamanho];

    for (int i=0; i< tamanho; i++){
        scanf("%d", &vet[i]);
    }

    bubblesort(vet, tamanho);
}