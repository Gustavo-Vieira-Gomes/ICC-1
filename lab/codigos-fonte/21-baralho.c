#include <stdio.h>

int getRowIndex(char naipe)
{
    switch (naipe)
    {
    case 'C':
        return 0;
    case 'O':
        return 1;
    case 'P':
        return 2;
    case 'E':
        return 3;
    default:
        return -1;
    }
}

int getColumnIndex(char *value)
{
    if (value[0] == '1' && value[1] == '0' && value[2] == '\0')
        return 9;

    char c = value[0];
    if (c == 'A')
        return 0;
    if (c >= '2' && c <= '9')
        return c - '1';
    if (c == 'J')
        return 10;
    if (c == 'Q')
        return 11;
    if (c == 'K')
        return 12;

    return -1;
}

const char *getColumnStr(int index)
{
    switch (index)
    {
    case 0:
        return "A";
    case 1:
        return "2";
    case 2:
        return "3";
    case 3:
        return "4";
    case 4:
        return "5";
    case 5:
        return "6";
    case 6:
        return "7";
    case 7:
        return "8";
    case 8:
        return "9";
    case 9:
        return "10";
    case 10:
        return "J";
    case 11:
        return "Q";
    case 12:
        return "K";
    default:
        return "?";
    }
}

int main()
{
    int cards_used;
    scanf("%d", &cards_used);

    int cards_quantity[4][13] = {0};
    char card[4];

    for (int i = 0; i < cards_used; i++)
    {
        scanf("%s", card);

        int len = 0;
        while (card[len] != '\0' && len < 4)
            len++;

        if (len < 2)
            continue;

        char naipe = card[len - 1];

        char valor[3] = {'\0', '\0', '\0'};

        for (int j = 0; j < len - 1; j++)
            valor[j] = card[j];

        int row = getRowIndex(naipe);
        int column = getColumnIndex(valor);

        if (row != -1 && column != -1)
        {
            cards_quantity[row][column]++;
        }
        else
        {
            printf("Carta inválida: %s\n", card);
        }
    }

    for (int row = 0; row < 4; row++)
    {
        switch (row)
        {
        case 0:
            printf("Naipe: Copas\n");
            break;
        case 1:
            printf("Naipe: Ouros\n");
            break;
        case 2:
            printf("Naipe: Paus\n");
            break;
        case 3:
            printf("Naipe: Espadas\n");
            break;
        }

        for (int col = 0; col < 13; col++)
        {
            int count = cards_quantity[row][col];

            printf("%s: %d\n", getColumnStr(col), count);
        }
    }

    return 0;
}
