#include <stdio.h>
#define EXIT_SUCCESS 0
#define EXIT_ERROR 1

float get_discount(float charge, int userAge)
{
    if (userAge < 6)
    {
        charge = charge * 0;
    }
    else if (userAge < 18)
    {
        charge = charge * 0.5;
    }
    else if (userAge >= 60)
    {
        charge = charge * 0.75;
    }
    return charge;
}

float get_charge(int service, int periodTime)
{
    switch (periodTime)
    {
    case 1:
        switch (service)
        {
        case 1:
            return 4.0;
            break;
        case 2:
            return 4.50;
            break;
        case 3:
            return 3.80;
            break;
        case 4:
            return 4.30;
            break;
        default:
            break;
        }
        break;

    case 2:
        switch (service)
        {
        case 1:
            return 5.00;
            break;
        case 2:
            return 6.00;
            break;
        case 3:
            return 5.20;
            break;
        case 4:
            return 5.50;
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

int main()
{
    int service, periodTime, age;
    float tarifa;

    printf("Insira o código do serviço: ");
    scanf("%d", &service);

    if (service < 1 || service > 4)
    {
        printf("Código inválido!\n");
        return EXIT_ERROR;
    }

    printf("Insira o período do dia: ");
    scanf("%d", &periodTime);

    if (periodTime != 1 && periodTime != 2)
    {
        printf("Período inválido!\n");
        return EXIT_ERROR;
    }

    printf("Insira a idade: ");
    scanf("%d", &age);

    if (age < 0)
    {
        printf("Idade inválida!\n");
        return EXIT_ERROR;
    }

    tarifa = get_charge(service, periodTime);

    tarifa = get_discount(tarifa, age);

    printf("Tarifa Final: R$ %.2f\n", tarifa);

    return EXIT_SUCCESS;
}