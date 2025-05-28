#include <stdio.h>
#include <math.h>


int main() {
    int line_extension;
    double distance = 0.0;

    scanf("%d", &line_extension);

    float positions[line_extension][2];

    for(int i = 0; i < line_extension; i++){
        scanf("%f %f", &positions[i][0], &positions[i][1]);
        if (i != 0){
            distance += sqrt(pow(positions[i][0]-positions[i-1][0], 2) + pow(positions[i][1]-positions[i-1][1], 2));
        }
    }

    printf("%.4f", distance);

}