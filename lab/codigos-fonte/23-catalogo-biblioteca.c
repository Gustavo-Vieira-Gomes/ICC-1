#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int verificarDuplicata(char **titles, char **authors, int n, char *titulo, char *autor)
{
    for (int i = 0; i < n; i++)
    {
        if (strcmp(titles[i], titulo) == 0 && strcmp(authors[i], autor) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    int n;

    scanf("%d", &n);
    getchar();

    char **titles = (char **)malloc(n * sizeof(char *));
    char **authors = (char **)malloc(n * sizeof(char *));
    int *years = (int *)malloc(n * sizeof(int));
    int *quantities = (int *)malloc(n * sizeof(int));

    if (titles == NULL || authors == NULL || years == NULL || quantities == NULL)
    {
        return 1;
    }

    int totalLivros = 0;

    for (int i = 0; i < n; i++)
    {
        char *titulo = (char *)malloc(101 * sizeof(char));
        char *autor = (char *)malloc(51 * sizeof(char));
        int ano;

        scanf(" %[^,], %[^,], %d", titulo, autor, &ano);

        int index = verificarDuplicata(titles, authors, totalLivros, titulo, autor);

        if (index == -1)
        {
            titles[totalLivros] = titulo;
            authors[totalLivros] = autor;
            years[totalLivros] = ano;
            quantities[totalLivros] = 1;

           totalLivros++;
        }
        else
        {
            quantities[index]++;
            free(titulo);
            free(autor);
        }
    }

    printf("Catalogo de Livros:\n");
    for (int i = 0; i < totalLivros; i++)
    {
        printf("Livro %d:\n", i + 1);
        printf("Titulo: %s\n", titles[i]);
        printf("Autor: %s\n", authors[i]);
        printf("Ano: %d\n", years[i]);
        if( i == totalLivros - 1)
        {
            printf("Quantidade: %d\n", quantities[i]);
        } else {
            printf("Quantidade: %d\n\n", quantities[i]);
        }
    }

    for (int i = 0; i < totalLivros; i++)
    {
        free(titles[i]);
        free(authors[i]);
    }
    free(titles);
    free(authors);
    free(years);
    free(quantities);

    return 0;
}
