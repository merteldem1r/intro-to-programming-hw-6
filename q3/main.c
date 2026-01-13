#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Working with 2D Arrays using Dynamic Memory Allocation

void fillMatris(int **matris)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            matris[i][j] = rand() % 10;
        }
    }
}

void printMatris(int **matris)
{
    for (int i = 0; i < 3; ++i)
    {
        printf("[ ");
        for (int j = 0; j < 5; ++j)
        {
            printf("%d ", matris[i][j]);
        }
        printf("]\n");
    }
}

int main()
{
    srand(time(NULL));

    int rowCount = 3, colCount = 5;
    int **matris = (int **)calloc(rowCount, sizeof(int *));

    for (int i = 0; i < rowCount; ++i)
    {
        matris[i] = (int *)calloc(colCount, sizeof(int));
    }

    fillMatris(matris);
    printMatris(matris);

    for (int i = 0; i < rowCount; i++)
    {
        free(matris[i]);
    }
    free(matris);

    return 0;
}
