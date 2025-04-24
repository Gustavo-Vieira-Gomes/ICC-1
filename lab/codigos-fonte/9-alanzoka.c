#include <stdio.h>

void main() {
    int index=1,position=0, distancia=0, alan, contador=1, sinal=-1, i= 0, lastposition;

    scanf("%d %d", &position, &alan);
    lastposition = position;
    while (i != 1){
        sinal *= -1;
        position = position + sinal*index;
        if (sinal > 0){
            if (lastposition <= alan && alan <= position){
                distancia += alan - lastposition;
                printf("%d", distancia);
                i = 1;
            }
        } else {
            if (position <= alan && alan <= lastposition){
                distancia += lastposition - alan;
                printf("%d", distancia);
                i = 1;
            }
        }
        distancia += index;
        if (contador == 1){
            index = index * 3;
        } else {
            index = index * 2;
        }
        contador += 1;
        lastposition = position;
    }
}
