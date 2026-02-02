#include <stdio.h>

void g(int *p)
{
    int *q = p;
    *q += 10;
    q++;
    *p += 5;
    *q += *p;
}

int main()
{
    int x[3] = {1, 2, 3};
    g(x);
    printf("%d %d %d\n", x[0], x[1], x[2]); // 16 18 3
    return 0;
}
