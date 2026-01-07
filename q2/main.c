#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char name[50];
    int midtermNote;
    int finalNote;
};

void fillStudentsArray(struct Student *students, int count)
{
    for (int i = 0; i < count; ++i)
    {
        printf("Enter name of student %d: ", i + 1);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;

        printf("Enter midterm note of student %d: ", i + 1);
        scanf("%d", &students[i].midtermNote);

        printf("Enter final note of student %d: ", i + 1);
        scanf("%d", &students[i].finalNote);

        getchar();
    }
}

void printStudentsAverage(const char *filePath)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL)
    {
        printf("Error while opening %s for reading!\n", filePath);
        return;
    }

    char line[128];
    char name[50];
    int midterm;
    int final;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (sscanf(line, "%49[^0-9]%d %d", name, &midterm, &final) == 3)
        {
            size_t len = strcspn(name, "\n");
            name[len] = '\0';
            while (len > 0 && name[len - 1] == ' ')
            {
                name[len - 1] = '\0';
                --len;
            }

            double average = midterm * 0.4 + final * 0.6;
            printf("Student: %s, Average: %.2f\n", name, average);
        }
    }

    fclose(file);
}

int main()
{
    int studentCount = 2;

    FILE *studentsFile = fopen("students.txt", "w");
    if (studentsFile == NULL)
    {
        printf("Error while opening and creating students.txt file!\n");
        return 1;
    }

    struct Student *students = (struct Student *)malloc(studentCount * sizeof(struct Student));
    if (students == NULL)
    {
        printf("Memory allocation failed!\n");
        fclose(studentsFile);
        return 1;
    }

    fillStudentsArray(students, studentCount);

    for (int i = 0; i < studentCount; ++i)
    {
        fprintf(studentsFile, "%s %d %d\n", students[i].name, students[i].midtermNote, students[i].finalNote);
    }

    fclose(studentsFile);

    printStudentsAverage("students.txt");

    free(students);

    return 0;
}