#include <stdio.h>

// Código utilizando apenas os recursos ensinados até o momento: If else, switchs, laços de repetição e Ponteiros
// É Possível refatorar este código usando funções e arrays, mas a ideia foi fazer de forma rústica com o que foi ensinado até agora.

int main()
{
    int *card1, *card2, *card3, livro1, livro2, livro3, operacao, intermediario;

    scanf("%d %d %d", &livro1, &livro2, &livro3);

    card1 = &livro1;
    card2 = &livro2;
    card3 = &livro3;

    for (int i = 1; i <= 3; i++)
    {
        scanf("%d", &operacao);
        switch (i)
        {
        case 1:
            switch (operacao)
            {
            case -1:
                card1 = NULL;
                break;

            case 0:
                *card1 += 1;
                break;

            case 1:
                break;

            case 2:
                if (card1 == NULL)
                {
                    card1 = card2;
                    card2 = NULL;
                }
                else
                {
                    if (card2 == NULL)
                    {
                        card2 = card1;
                        card1 = NULL;
                    }
                    else
                    {
                        intermediario = *card1;
                        *card1 = *card2;
                        *card2 = intermediario;
                        break;
                    }
                }

            case 3:
                if (card1 == NULL)
                {
                    card1 = card3;
                    card3 = NULL;
                }
                else
                {
                    if (card3 == NULL)
                    {
                        card3 = card1;
                        card1 = NULL;
                    }
                    else
                    {
                        intermediario = *card1;
                        *card1 = *card3;
                        *card3 = intermediario;
                        break;
                    }
                }
            }
            break;

        case 2:
            switch (operacao)
            {
            case -1:
                card2 = NULL;
                break;

            case 0:
                *card2 += 1;
                break;

            case 1:
                if (card2 == NULL)
                {
                    card2 = card1;
                    card1 = NULL;
                }
                else
                {
                    if (card1 == NULL)
                    {
                        card1 = card2;
                        card2 = NULL;
                    }
                    else
                    {
                        intermediario = *card2;
                        *card2 = *card1;
                        *card1 = intermediario;
                        break;
                    }
                }
                break;

            case 2:
                break;

            case 3:
                if (card2 == NULL)
                {
                    card2 = card3;
                    card3 = NULL;
                }
                else
                {
                    if (card3 == NULL)
                    {
                        card3 = card2;
                        card2 = NULL;
                    }
                    else
                    {
                        intermediario = *card2;
                        *card2 = *card3;
                        *card3 = intermediario;
                        break;
                    }
                }
                break;
            }
            break;

        case 3:
            switch (operacao)
            {
            case -1:
                card3 = NULL;
                break;

            case 0:
                *card3 += 1;
                break;

            case 1:
                if (card3 == NULL)
                {
                    card3 = card1;
                    card1 = NULL;
                }
                else
                {
                    if (card1 == NULL)
                    {
                        card1 = card3;
                        card3 = NULL;
                    }
                    else
                    {
                        intermediario = *card3;
                        *card3 = *card1;
                        *card1 = intermediario;
                        break;
                    }
                }
                break;

            case 2:
                if (card3 == NULL)
                {
                    card3 = card2;
                    card2 = NULL;
                }
                else
                {
                    if (card2 == NULL)
                    {
                        card2 = card3;
                        card3 = NULL;
                    }
                    else
                    {
                        intermediario = *card3;
                        *card3 = *card2;
                        *card2 = intermediario;
                        break;
                    }
                }
                break;

            case 3:
                break;
            }
            break;
        }
    }

    if (card1 == NULL)
    {
        printf("cartao1 -> Livro fora da estante\n");
    }
    else
    {
        printf("cartao1 -> %d\n", *card1);
    }

    if (card2 == NULL)
    {
        printf("cartao2 -> Livro fora da estante\n");
    }
    else
    {
        printf("cartao2 -> %d\n", *card2);
    }

    if (card3 == NULL)
    {
        printf("cartao3 -> Livro fora da estante\n");
    }
    else
    {
        printf("cartao3 -> %d\n", *card3);
    }

    return 0;
}