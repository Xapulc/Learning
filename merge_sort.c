#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int genArray(int total, int **array);
int mergeSort(int ((*compare)(int, int)), int *from, int begin, int end, int **res);
int merge(int ((*compare)(int, int)), int *array1, int *array2, int begin, int middle, int end, int **res);
int checking(int ((*compare)(int, int)), int* array, int total);
int simpleCompare(int a, int b);
void printArray(int *array, int total);

int main(void) {
    int total;
    int *array;
    int *res;
    time_t start, endGen, endSort;

    printf("What count of numbers do you want to sort?\n");
    if ((scanf("%d", &total) != 1) || (total < 1)) {
        printf("Incorrect enter\n");
        return -1;
    }

    time(&start);

    if (genArray(total, &array)) {
        printf("We have some problems with memory\n");
        return -1;
    }

    time(&endGen);

     if (mergeSort(simpleCompare, array, 0, total, &res)) {
         printf("You have problems with memory\n");
         free(array);
         return -1;
     }

    time(&endSort);

    if (checking(simpleCompare, res, total))
        printf("Array isn't sorted\n");
    else
        printf("Array is sorted\n");

    printf("Program wastes %d seconds on generation data\n", (int) (endGen - start));
    printf("Program wastes %d seconds on sorting data\n", (int) (endSort - endGen));

//    printArray(array, total);
//    printArray(res, total);
    free(array);
    free(res);
    return 0;
}

int genArray(int total, int **array) {
    int i;

    if ((*array = (int *) malloc (sizeof(int) * total)) == 0)
        return -1;

    for (i = 0; i < total; i++) {
        (*array)[i] = rand()/10 - 700;
    }

    return 0;
}

int simpleCompare(int a, int b) {
    return (a <= b);
}

int mergeSort(int ((*compare)(int, int)), int *from, int begin, int end, int **res) {
    int *leftPart, *rightPart;
    int middle = (end - begin)/2 + begin;
    int mergeRes;

    if (end - begin > 1) {
       if (mergeSort(compare, from, begin, middle, &leftPart))
           return -1;

       if (mergeSort(compare, from, middle, end, &rightPart)) {
           free(leftPart);
           return -1;
       }

       mergeRes = merge(compare, leftPart, rightPart, begin, middle, end, res);
       free(leftPart);
       free(rightPart);
       return mergeRes;
    } else {
        if (begin == end) {
            *res = 0;
            return 0;
        } else {
            if ((*res = (int *) malloc (sizeof(int) * 1)) == 0) {
                return -1;
            }
            (*res)[0] = from[begin];
            return 0;
        }
    }
}

int merge(int ((*compare)(int, int)), int *array1, int *array2, int begin, int middle, int end, int **res) {
    int i = 0, size1 = middle - begin;
    int j = 0, size2 = end - middle;

    if ((*res = (int *) malloc (sizeof(int) * (size1+size2))) == 0) {
        return -1;
    }

    while ((i < size1) && (j < size2)) {
        if ((*compare)(array1[i], array2[j])) {
            (*res)[i+j] = array1[i];
            i++;
        } else {
            (*res)[i+j] = array2[j];
            j++;
        }
    }

    for (; i < size1; i++)
        (*res)[i+j] = array1[i];
    for (; j < size2; j++)
        (*res)[i+j] = array2[j];

    return 0;
}

int checking(int ((*compare)(int, int)), int* array, int total) {
    int i;
    for (i = 1 ; i < total; i++)
        if (!(compare(array[i-1], array[i])))
            return -1;
    return 0;
}

void printArray(int *array, int total) {
    int i;
    for (i = 0; i < total; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}
