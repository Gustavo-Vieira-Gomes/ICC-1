#include <stdio.h>

unsigned long long fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    unsigned long long a = 0, b = 1, temp;
    for (int i = 2; i <= n; i++) {
        temp = a + b;
        a = b;
        b = temp;
    }
    return b;
}

int main() {
    int nivel;

    while (1) {
        scanf("%d", &nivel);
        if (nivel == 0) break;
        printf("%llu\n", fibonacci(nivel));
    }

    return 0;
}
