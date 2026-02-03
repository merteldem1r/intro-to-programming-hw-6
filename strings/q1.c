#include <stdio.h>

// Function to convert uppercase letters to lowercase and vice versa

void lowerUpper(char *str)
{
    int dif = 'a' - 'A';
    while (*str != '\0')
    {
        if (*str >= 'A' && *str <= 'Z')
        {
            *str += dif;
        }
        else if (*str >= 'a' && *str <= 'z')
        {
            *str -= dif;
        }

        ++str;
    }
}

int main()
{
    char str[] = "HeLlo wOrlD";
    printf("%s\n", str);
    lowerUpper(str);
    printf("%s", str);

    return 0;
}