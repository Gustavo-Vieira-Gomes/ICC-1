#include <stdio.h>

int main()
{
    int numeros[10];

    for (int i = 0; i < 10; i++)
    {
        scanf("%d", &numeros[i]);
    }

    for (int j = 0; j < 10; j++)
    {
        for (int k = j; k < 10; k++)
        {

            if (numeros[j] > numeros[k])
            {
                int intermediario = numeros[j];
                numeros[j] = numeros[k];
                numeros[k] = intermediario;
            }
        }
    }

    for (int n = 0; n < 10; n++)
    {
        printf("%d ", numeros[n]);
    }
}