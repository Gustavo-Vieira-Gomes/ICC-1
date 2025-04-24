#include <stdio.h>

int main(){
    double num1, num2;
    char operation;

    scanf("%lf %c %lf", &num1, &operation, &num2);

    switch (operation){
        case '+':
            printf("%.2lf", (num1 + num2));
            break;
        case '-':
            printf("%.2lf", (num1 - num2));
            break;
        case '*':
            printf("%.2lf", (num1 * num2));
            break;
        case '/':
            printf("%.2lf", (num1 / num2));
            break;
        default:
            printf("Operaçao Nao existente");
    }
}
