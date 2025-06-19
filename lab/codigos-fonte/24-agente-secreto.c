#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void computeLPSArray(const char *pat, int M, int *lps) {
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int substringSearch(const char *txt, const char *pat) {
    int N = strlen(txt);
    int M = strlen(pat);

    if (M == 0) return 1;

    int *lps = (int *)malloc(M * sizeof(int));

    computeLPSArray(pat, M, lps);

    int i = 0, j = 0;
    while (i < N) {
        if (pat[j] == txt[i]) {
            i++; j++;
        }

        if (j == M) {
            free(lps);
            return 1;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }

    free(lps);
    return 0;
}

int main() {
    char *s = (char *)malloc(10001);
    char *t = (char *)malloc(10001);
    scanf("%10000s", s);
    scanf("%10000s", t);

    int t_len = strlen(t);
    char *prefix = (char *)malloc(t_len + 1);
    int maxPrefixLength = 0;

    for (int i = t_len; i >= 1; i--) {
        strncpy(prefix, t, i);
        prefix[i] = '\0';

        if (substringSearch(s, prefix)) {
            maxPrefixLength = i;
            break;
        }
    }

    if (maxPrefixLength > 0) {
        printf("%d %.*s\n", maxPrefixLength, maxPrefixLength, t);
    } else {
        printf("0\n");
    }

    free(prefix);
    free(s);
    free(t);

    return 0;
}
