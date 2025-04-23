#include <stdio.h>

int main()
{
    char nome[51];
    float nota_final, nota_inicial;
    int faltas, qnt_atividades;

    printf("Digite seu nome: ");
    scanf("%[^\n]50s", nome);

    printf("Insira sua nota final: ");
    scanf("%f", &nota_final);

    if (nota_final < 0 || nota_final > 10)
    {
        printf("Nota inválida!\n");
        return 1;
    }

    printf("Insira o número de faltas: ");
    scanf("%d", &faltas);

    if (faltas < 0)
    {
        printf("Faltas inválidas!\n");
        return 1;
    }

    printf("Insira a quantidade de atividades extras entregues: ");
    scanf("%d", &qnt_atividades);

    if (qnt_atividades < 0 || qnt_atividades > 5)
    {
        printf("Quantidade de atividades inválida!\n");
        return 1;
    }

    nota_final = nota_inicial;

    if (qnt_atividades >= 3)
    {
        nota_final = nota_final + 1;
        if (nota_final > 10)
        {
            nota_final = 10;
        }
    }

    if (faltas > 15)
    {
        nota_final = nota_final - 1;
        if (nota_final < 0)
        {
            nota_final = 0;
        }
    }

    if (nota_final >= 9.0)
    {
        printf("O Aluno %s com nota original %f e nota final %f teve desempenho Excelente\n", nome, nota_inicial, nota_final);
    }
    else if (nota_final >= 7.0)
    {
        printf("O Aluno %s com nota original %f e nota final %f teve desempenho Bom\n", nome, nota_inicial, nota_final);
    }
    else if (nota_final >= 5.0)
    {
        printf("O Aluno %s com nota original %f e nota final %f teve desempenho Regular\n", nome, nota_inicial, nota_final);
    }
    else
    {
        printf("O Aluno %s com nota original %f e nota final %f teve desempenho Ruim\n", nome, nota_inicial, nota_final);
    }

    return 0;
}