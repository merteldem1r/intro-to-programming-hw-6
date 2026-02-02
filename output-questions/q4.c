#include <stdio.h>

char *find_and_next(char *s, char c)
{
    while (*s && *s != c)
        s++;

    if (*s)
        return s + 1;

    return s;
}

int main(void)
{
    char metin[] = "programlama";
    char *ptr = metin;

    printf("1: %s\n", find_and_next(ptr, 'g')); // ramlama
    printf("2: %s\n", find_and_next(ptr, 'a')); // mlama

    char *sonuc1 = find_and_next(ptr, 'r'); // ogramlama
    ptr++;
    char *sonuc2 = find_and_next(ptr, 'm'); // lama

    printf("3: %s\n", sonuc1);              // ogramlama
    printf("4: %s\n", sonuc2);              // lama
    printf("5: ptr now shows: %c\n", *ptr); // r

    return 0;
}
