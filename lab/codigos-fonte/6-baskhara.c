#include <stdio.h>
#include <math.h>

int main(){
    int a, b, c, delta;

    scanf("%d", &a);
    scanf("%d", &b);
    scanf("%d", &c);

    delta = pow(b, 2) - 4 * a * c;

    if (delta <0){
        printf("NAO EXISTE RAIZ REAL");
    } else if (delta == 0) {
        float x1;
        x1 = -b /(2.0*a);
        printf("%.3f", x1);
    } else {
        float x1, x2;
        x2 = (sqrt(delta) - b) / (2*a);
        x1 = (-sqrt(delta) - b) / (2*a);
        printf("%.3f %.3f", x1, x2);
    }
}
