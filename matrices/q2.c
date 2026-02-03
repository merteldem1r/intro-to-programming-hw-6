#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rowCount, colCount;
    printf("Enter number of rows: ");
    scanf("%d", &rowCount);
    printf("Enter number of columns: ");
    scanf("%d", &colCount);

    int **matrix = (int **)malloc(rowCount * sizeof(int *));
    for (int i = 0; i < rowCount; i++)
    {
        matrix[i] = (int *)malloc(colCount * sizeof(int));
    }

    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            printf("Enter value for element [%d][%d]: ", i + 1, j + 1);
            int value;
            scanf("%d", &value);
            matrix[i][j] = value;
        }
    }

    printf("\nMatrix:\n");
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nMax value from each row:\n");
    for (int i = 0; i < rowCount; i++)
    {
        int max = matrix[i][0];
        for (int j = 1; j < colCount; j++)
        {
            if (matrix[i][j] > max)
            {
                max = matrix[i][j];
            }
        }
        printf("Row %d: %d\n", i + 1, max);
    }

    for (int i = 0; i < rowCount; i++)
    {
        free(matrix[i]);
    }
    free(matrix);

    return 0;
}
