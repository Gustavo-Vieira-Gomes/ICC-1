#include <stdio.h>
#include <stdlib.h>


int main() {
    int *p1, *p2;

    p1 = (int *) malloc(sizeof(int));
    p2 = (int *) malloc(sizeof(int));

    scanf("%d %d", p1, p2);

    printf("%d %d\n", *p1, *p2);

    *p1 = *p1 + *p2;
    *p2 = *p1 - *p2;
    *p1 = *p1 - *p2;

    printf("%d %d", *p1, *p2);

    free(p1);
    free(p2);
}