#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char name[50];
    int studentID;
    float midtermNote;
    float finalNote;
};

void getStudentInfo(struct Student *student, int index)
{
    char buffer[100];

    printf("Enter student name for student %d: ", index + 1);
    fgets(student->name, sizeof(student->name), stdin);
    student->name[strcspn(student->name, "\n")] = '\0';

    printf("Enter student ID for student %d: ", index + 1);
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &student->studentID);

    printf("Enter midterm note for student %d: ", index + 1);
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &student->midtermNote);

    printf("Enter final note for student %d: ", index + 1);
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &student->finalNote);
}

void saveStudent(struct Student *st, FILE *filePtr)
{
    char buffer[128];

    fprintf(filePtr, "%s %d %.2f %.2f\n",
            st->name,
            st->studentID,
            st->midtermNote,
            st->finalNote);
}

int main(void)
{
    FILE *filePtr = fopen("students.txt", "w");

    if (filePtr == NULL)
    {
        printf("Error while opening file for writing!\n");
        return 1;
    }

    char buffer[50];
    int studentCount;

    printf("Enter number of students: ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &studentCount);

    for (int i = 0; i < studentCount; ++i)
    {
        struct Student newStudent;
        getStudentInfo(&newStudent, i);
        saveStudent(&newStudent, filePtr);
    }

    fclose(filePtr);

    return 0;
}