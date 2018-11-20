#include <stdio.h>
#include <stdlib.h>

int countHelper(int prevElem, int curElem, int *isAsceding);
int getCountIncreasingParts(FILE *file);

int main(void) {
    int isReadingFromFile;
    int countIncreasingParts;
    char *fileName = 0;
    char buffer;
    FILE *file;

    printf("If you want, that sequence is reading from keyboard, write 0\n"
           "If you want, that sequence is reading from file, write not 0\n");
    if (scanf("%d", &isReadingFromFile) != 1) {
        printf("Wrong request\n");
        return -1;
    } else if (isReadingFromFile) {
        printf("Give me file name\n");

        fileName = (char *) malloc (sizeof(char) * 100);
        int i = 0;
        scanf("%c", &buffer); // scan first \n
        while ((scanf("%c", &buffer) == 1) && (buffer != '\n') && (buffer != '\r')) {
            fileName[i++] = buffer;
            if (i >= 99) {
                printf("So long file name\n");
                free(fileName);
                return -2;
            }
        }
        fileName[i]='\0';
        printf("%s\n", fileName);

        if ((file = fopen(fileName, "r")) == 0) {
            printf("Wrong file name\n");
            free(fileName);
            return -3;
        }
    } else {
        file = 0;
    }
    countIncreasingParts = getCountIncreasingParts(file);

    printf("In your sequence %d asceding parts", countIncreasingParts);
    if (isReadingFromFile)
        fclose(file);
    free(fileName);
    return 0;
}

int getCountIncreasingParts(FILE *file) {
    int prevElem, curElem;
    int isAsceding = 0;
    int countAscedingParts = 0;

    if (file) {
        fscanf(file, "%d", &prevElem);
        while (fscanf(file, "%d", &curElem) && (!feof(file))) {
            countAscedingParts += countHelper(prevElem, curElem, &isAsceding);
            prevElem = curElem;
        }
    } else {
        scanf("%d", &prevElem);
        while (scanf("%d", &curElem)) {
            countAscedingParts += countHelper(prevElem, curElem, &isAsceding);
            prevElem = curElem;
        }
    }

    return countAscedingParts;
}

int countHelper(int prevElem, int curElem, int *isAsceding) {
    if (*isAsceding) {
        if (prevElem >= curElem) {
            *isAsceding = 0;
        }
        return 0;
    } else {
        if (prevElem < curElem) {
            *isAsceding = 1;
            return 1;
        }
        return 0;
    }
}