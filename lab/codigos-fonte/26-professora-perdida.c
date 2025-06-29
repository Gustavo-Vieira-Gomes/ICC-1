#include <stdio.h>

struct Task
{
    char day[3], month[3], year[5], hour[3], minute[3], seconds[3], description[100];
};


int main(void) {
    int quantity;

    scanf("%d", &quantity);

    struct Task tasks[quantity];

    for (int i = 0; i < quantity; i++) {
        scanf("%s", tasks[i].day);
        scanf("%s", tasks[i].month);
        scanf("%s", tasks[i].year);
        scanf("%s", tasks[i].hour);
        scanf("%s", tasks[i].minute);
        scanf("%s", tasks[i].seconds);
        getchar();
        scanf("%[^\n]", tasks[i].description);
    }

    for (int i = 0; i < quantity; i++)  {
        printf("%s/%s/%s - %s:%s:%s\n", tasks[i].day, tasks[i].month, tasks[i].year, tasks[i].hour, tasks[i].minute, tasks[i].seconds);
        if (i != quantity - 1) {
            printf("%s\n", tasks[i].description);
        } else {
            printf("%s", tasks[i].description);
        }
    }
}