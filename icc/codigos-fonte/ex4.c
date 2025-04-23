#include <stdio.h>

int main() {
    char digit=0;
    int count_num=0, count_letra=0;
    while (digit!=64)
    {
        scanf("%c", &digit);
        if (48 <= digit && digit <= 57)
        {
            count_num++;
        } else {
            if (97 <= digit && digit <= 122)
            {
                count_letra++;
            }
        }
    }
    printf("Numeros: %d\n", count_num);
    printf("Letras Minusculas %d\n", count_letra);
    
    return 0;
}