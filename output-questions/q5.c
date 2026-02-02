#include <stdio.h>

int h(int x)
{
    x = x + 2;
    return x;
}

int g(int *p)
{
    *p = *p + 1;
    return h(*p) - 1;
}

int f(int x)
{
    x = x * 2;
    return g(&x) + x;
}

int main(void)
{
    int a = 3;

    int t1 = f(a);
    int t2 = g(&a);
    int t3 = h(a++);

    int sonuc = t1 + t2 + t3;

    printf("%d %d\n", sonuc, a); // "26 5"
    return 0;
}
