#include <stdio.h>

int main()
{
    int n, b;

    scanf("%d %d", &n, &b);
    getchar();

    char titles[n][101];

    for (int i = 0; i < n; i++)
    {
        scanf(" %[^\n]", titles[i]);
    }

    for (int title = 0; title < n; title++)
    {
        int digit = 0;
        while (titles[title][digit] != '\0')
        {
            if (b == 1)
            {
                if (titles[title][digit] > 96 && titles[title][digit] < 123)
                {
                    titles[title][digit] -= 32;
                }
            }
            else
            {
                if (titles[title][digit] > 64 && titles[title][digit] < 91)
                {
                    titles[title][digit] += 32;
                }
            }
            digit++;
        }
    }

    for (int row = 0; row < n; row++)
    {
        printf("%s", titles[row]);
        if (row != n - 1)
            printf("\n");
    }
}