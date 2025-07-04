#include <stdio.h>
#include <string.h>

#define MAX_JOGOS 100005
#define MAX_NOME 55

char jogos[MAX_JOGOS][MAX_NOME];

int busca_binaria(int esquerda, int direita, char alvo[]) {
    if (esquerda > direita)
        return -1;

    int meio = (esquerda + direita) / 2;
    int comparacao = strcmp(jogos[meio], alvo);

    if (comparacao == 0)
        return meio;
    else if (comparacao > 0)
        return busca_binaria(esquerda, meio - 1, alvo);
    else
        return busca_binaria(meio + 1, direita, alvo);
}

int main() {
    int n;
    scanf("%d", &n);
    getchar();

    for (int i = 0; i < n; i++) {
        fgets(jogos[i], MAX_NOME, stdin);
        jogos[i][strcspn(jogos[i], "\n")] = '\0';
    }

    char alvo[MAX_NOME];
    fgets(alvo, MAX_NOME, stdin);
    alvo[strcspn(alvo, "\n")] = '\0';

    int posicao = busca_binaria(0, n - 1, alvo);

    if (posicao != -1)
        printf("Jogo encontrado na posicao %d\n", posicao);
    else
        printf("Jogo nao encontrado\n");

    return 0;
}
