#include <stdio.h>

int main(void) {
    int number1, number2, number3;

    scanf("%d", &number1);
    scanf("%d", &number2);
    scanf("%d", &number3);

    if (number1 > number2){
        if (number1 > number3){
            printf("%d", number1);
        } else {
            printf("%d", number3);
        }
    } else {
        if (number2 > number3){
            printf("%d", number2);
        } else {
            printf("%d", number3);
        }
    }

    return 0;
}
