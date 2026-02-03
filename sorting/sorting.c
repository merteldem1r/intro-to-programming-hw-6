#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Insertion Sort */
void insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

/* Bubble Sort */
void bubbleSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int isSwapped = 0;
        for (int j = 0; j < n - 1 - i; ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
                isSwapped = 1;
            }
        }
        if (!isSwapped)
        {
            break;
        }
    }
}

/* Selection Sort */
void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; ++i)
    {
        int minIdx = i;

        for (int j = i + 1; j < n; ++j)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }

        if (minIdx != i)
        {
            swap(&arr[i], &arr[minIdx]);
        }
    }
}

void printArr(int arr[], int n)
{
    printf("{ ");
    for (int i = 0; i < n; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("}\n");
}

int main()
{
    int arr[] = {9, 5, 6, 4, 3, 1, 2, 7, 8, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printArr(arr, n);

    insertionSort(arr, n);
    // bubbleSort(arr, n);
    // selectionSort(arr, n);

    printArr(arr, n);

    return 0;
}
