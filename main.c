#include <stdio.h>

int main()
{
    // Create and write to a file
    FILE *myFile = fopen("example.txt", "w");

    if (myFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char name[] = "Mert";

    fprintf(myFile, "Hello, World! My name is %s\n", name);
    fputs("This is a test file.\n", myFile);
    fclose(myFile);

    // Read from the file and display its contents
    myFile = fopen("example.txt", "r");

    if (myFile == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    char ch;
    printf("File contents:\n");

    // while ((ch = fgetc(myFile)) != EOF)
    // {
    //     putchar(ch);
    // }

    char line[100];
    while (fgets(line, sizeof(line), myFile) != NULL)
    {
        printf("%s", line);
    }

    fclose(myFile);

    return 0;
}