#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *file, *tempFile;
    char command[100], filename[15], helper[100];

    scanf("%s", filename);
    getchar();

    while (fgets(command, sizeof(command), stdin)) {
        command[strcspn(command, "\n")] = 0;

        if (strstr(command, "ADD") != NULL) {
            file = fopen(filename, "a+");
            char *info = &command[4];

            fseek(file, -1, SEEK_END);
            char lastChar = fgetc(file);
            if (lastChar != '\n' && lastChar != EOF) {
                fputc('\n', file);
            }

            fputs(info, file);
            fputc('\n', file);
            fclose(file);
        } else if (strstr(command, "DEL") != NULL) {
            file = fopen(filename, "r");
            tempFile = fopen("helper.txt", "w");
            int rowCounter = 0;
            int deletedRowNumber = atoi(&command[4]);

            while (fgets(helper, sizeof(helper), file)) {
                if (rowCounter != deletedRowNumber) {
                    fputs(helper, tempFile);
                }
                rowCounter++;
            }

            fclose(file);
            fclose(tempFile);
            remove(filename);
            rename("helper.txt", filename);
        }
    }

    file = fopen(filename, "r");
    while (fgets(helper, sizeof(helper), file)) {
        printf("%s", helper);
    }
    fclose(file);
}
