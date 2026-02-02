#include <stdio.h>

int main()
{
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int *p = &a[0][0];
    int *q = a[1];

    printf("1: %d\n", a[1][0]);         // 4
    printf("2: %d\n", a[1][2]);         // 6
    printf("3: %d\n", (*(a + 1))[2]);   // 6
    printf("4: %d\n", p[3]);            // 4
    printf("5: %d\n", q[0]);            // 4
    printf("6: %d\n", *(*(a + 1) + 1)); // 5

    if (*(p + 1) < 3)
        p[3] = p[2] + 1;

    printf("7: %d %d %d %d %d %d\n",
           a[0][0], a[0][1], a[0][2],
           a[1][0], a[1][1], a[1][2]); // 1 2 3 4 5 6

    return 0;
}
