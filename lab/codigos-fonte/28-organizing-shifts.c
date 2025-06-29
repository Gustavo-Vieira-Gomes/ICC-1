#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[101], subject[101];
    int uspNumber;
} Person;

int main(void) {
    int inicialDocentNumber, newDocentNumber;
    Person *docents;
    char buffer[120];

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &inicialDocentNumber);

    docents = malloc(sizeof(Person) * inicialDocentNumber);

    for (int i = 0; i < inicialDocentNumber; i++) {
        fgets(docents[i].name, sizeof(docents[i].name), stdin);
        docents[i].name[strcspn(docents[i].name, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &docents[i].uspNumber);

        fgets(docents[i].subject, sizeof(docents[i].subject), stdin);
        docents[i].subject[strcspn(docents[i].subject, "\n")] = '\0';
    }

    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &newDocentNumber);

    docents = realloc(docents, sizeof(Person) * (inicialDocentNumber + newDocentNumber));

    for (int i = 0; i < newDocentNumber; i++) {
        int index = inicialDocentNumber + i;

        fgets(docents[index].name, sizeof(docents[index].name), stdin);
        docents[index].name[strcspn(docents[index].name, "\n")] = '\0';

        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &docents[index].uspNumber);

        fgets(docents[index].subject, sizeof(docents[index].subject), stdin);
        docents[index].subject[strcspn(docents[index].subject, "\n")] = '\0';
    }

    for (int i = 0; i < inicialDocentNumber + newDocentNumber; i++) {
        printf("Discente %d:\n", i + 1);
        printf("Nome: %s\n", docents[i].name);
        printf("Número USP: %d\n", docents[i].uspNumber);
        printf("Assunto: %s\n", docents[i].subject);
        printf("\n");
    }

    free(docents);
    return 0;
}
