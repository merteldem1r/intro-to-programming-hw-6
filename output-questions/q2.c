#include <stdio.h>
#include <string.h>

int f(char *s)
{
    char *p = s;

    while (*p)
    {
        if (*p == 'a')
            *p = 'A';
        p++;
    }

    return (int)(p - s);
}

int main()
{
    char s[] = "ananas";
    int r = f(s);

    printf("%s %d\n", s, r); // AnAnAs 6

    return 0;
}
