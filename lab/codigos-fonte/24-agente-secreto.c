#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char *s = (char *)malloc(10001 * sizeof(char));
    char *t = (char *)malloc(10001 * sizeof(char));
    scanf("%10000s", s);
    scanf("%10000s", t);

    int maxPrefixLength = 0;
    char *prefix = NULL;

    for (int i = 1; i <= strlen(t); i++) {
        char *prefixo = (char*)malloc((i + 1) * sizeof(char));
        strncpy(prefixo, t, i);
        prefixo[i] = '\0';

        if (strstr(s, prefixo) != NULL) {
            if (i > maxPrefixLength) {
                maxPrefixLength = i;
                if (prefix != NULL) {
                    free(prefix);
                }
                prefix = prefixo;
            } else {
                free(prefixo);
            }
        } else {
            free(prefixo);
        }
    }

    if (maxPrefixLength > 0) {
        printf("%d %s\n", maxPrefixLength, prefix);
        free(prefix);
    } else {
        printf("0\n");
    }

    free(s);
    free(t);

    return 0;
}
