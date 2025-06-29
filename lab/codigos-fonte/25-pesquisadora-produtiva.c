#include <stdio.h>
#include <stdlib.h>


int main(void){
    FILE *file;
    char character, filename[11];
    int contador = 0;

    scanf("%s", filename);
    file = fopen(filename, "r");

    while (character = fgetc(file) != EOF)
    {
        contador++;
    }

    fclose(file);

    printf("%d\n", contador);

    return 0;
}