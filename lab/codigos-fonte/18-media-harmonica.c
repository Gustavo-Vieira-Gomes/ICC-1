#include <stdio.h>

int readInt(){
    int number;
    scanf("%d", &number);
    return number;
}

double readDouble(){
    double number;
    scanf("%lf", &number);
    return number;
}

void printDouble(double val){
    printf("%.2lf", val);
}

int main() {
    int activities_number;
    double grade, sum=0, average;
    activities_number = readInt();

    for (int i=0; i < activities_number; i++){
        grade = readDouble();
        sum += 1/(grade+1);
    }

    average = (activities_number / sum) - 1;

    printDouble(average);
}