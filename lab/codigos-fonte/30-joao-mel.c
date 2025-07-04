#include <stdio.h>

#define MAX 100

int linhas, colunas;
char mapa[MAX][MAX];
int visitado[MAX][MAX];

int buscar(int i, int j) {
    if (i < 0 || i >= linhas || j < 0 || j >= colunas)
        return 0;

    if (visitado[i][j] || mapa[i][j] == '#')
        return 0;

    if (mapa[i][j] == 'P')
        return 1;

    visitado[i][j] = 1;

    if (buscar(i - 1, j)) return 1;
    if (buscar(i + 1, j)) return 1;
    if (buscar(i, j - 1)) return 1;
    if (buscar(i, j + 1)) return 1;

    return 0;
}

int main() {
    scanf("%d %d", &linhas, &colunas);

    int ini_i = -1, ini_j = -1;

    for (int i = 0; i < linhas; i++) {
        scanf("%s", mapa[i]);
        for (int j = 0; j < colunas; j++) {
            if (mapa[i][j] == 'J') {
                ini_i = i;
                ini_j = j;
            }
        }
    }

    if (buscar(ini_i, ini_j))
        printf("Sim\n");
    else
        printf("Nao\n");

    return 0;
}
