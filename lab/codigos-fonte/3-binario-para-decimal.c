#include <stdio.h>

int main(){
    char binario[5];
    int base10 = 0;
    scanf("%4s", binario);
    if (binario[0] == '1'){
        base10 = base10 + 8;
    }
    if (binario[1] == '1') {
        base10 = base10 + 4;
    }
    if (binario[2] == '1') {
        base10 = base10 + 2;
    }
    if (binario[3] == '1') {
        base10 = base10 + 1;
    }
    printf("%d", base10);
}
