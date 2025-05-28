#include <stdio.h>
#include <math.h>
#define PI 3.141592

double getAlfa(int dimension, int index) {
    if (index == 0){
        return (1.0 / sqrt((double) dimension));
    } else {
        return sqrt(2.0/dimension);
    }
}

int main()
{
    int n;
    double alfa1, alfa2, frequency = 0.0;

    scanf("%d", &n);

    double matrice[n][n], result[n][n];

    // Ler os valores da matriz
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%lf", &matrice[i][j]);

    // Percorrendo cada valor da matriz e calculando a sua frequencia
    for (int i = 0; i < n; i++)
    {
        alfa1 = getAlfa(n, i);
        for (int j = 0; j < n; j++)
        {
            alfa2 = getAlfa(n, j);

            // Percorrendo cada valor da matriz para calcular a base da frequencia do valor de linha i e coluna j
            for (int m = 0; m < n; m++)
            {
                for (int p = 0; p < n; p++)
                {
                    frequency += matrice[m][p] * cos(((2 * p + 1) * j * PI) / (2.0 * n)) * cos(((2 * m + 1) * i * PI) / (2.0 * n));
                }
            }
            // Adicionando fator de correçao
            result[i][j] = alfa1 * alfa2 * frequency;
            frequency = 0.0;
        }
    }

    // Apresentando as saidas
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++)
        {
            printf("%9.3lf", result[i][j]);
            if (j< n-1) printf(" ");
        }
        printf("\n");
    }
}