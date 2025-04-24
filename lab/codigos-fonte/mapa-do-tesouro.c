#include <stdio.h>

int main() {
    int tesouro, *map, **mapToMap;

    scanf("%d", &tesouro);

    map = &tesouro;
    mapToMap = &map;

    printf("Valor inicial do tesouro: %d\n", tesouro);
    printf("Valor do tesouro usando mapa: %d\n", *map);

    *map += 10;

    printf("Valor do tesouro usando mapa depois de adicionarmos 10 moedas: %d\n", *map);

    printf("Valor do tesouro usando mapa para o mapa: %d\n", **mapToMap);

    **mapToMap += 10;

    printf("Valor do tesouro usando mapa para o mapa depois de adicionarmos 10 moedas: %d\n", **mapToMap);
   
    return 0;
} 