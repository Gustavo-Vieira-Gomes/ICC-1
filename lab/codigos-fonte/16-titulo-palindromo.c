#include <stdio.h>

int main()
{
    int n, freq[26] = {0}, qnt_impares=0;
    scanf("%d", &n);

    char nome[n + 1];
    scanf("%s", nome);

    for (int i = 0; i < n; i++) {
        freq[nome[i] - 'a']++;
    }

    for (int j = 0; j < 26; j++) {
        if (freq[j] % 2 == 1) {
            qnt_impares++;
        }
    }

    if (n % 2 == 0) {
        if (qnt_impares > 0) {
            printf("Nao");
        } else {
            printf("Sim");
        }
    } else {
        if (qnt_impares > 1) {
            printf("Nao");
        } else {
            printf("Sim");
        }
    }
}
