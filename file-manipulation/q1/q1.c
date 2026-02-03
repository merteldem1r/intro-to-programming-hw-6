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

void getStudentsInfo(FILE *filePtr, int studentCount);
void saveStudent(struct Student *st, FILE *filePtr);
void printStudentAverages(FILE *filePtr);

void getStudentsInfo(FILE *filePtr, int studentCount)
{
    for (int i = 0; i < studentCount; ++i)
    {
        struct Student newStudent;

        char buffer[100];

        printf("Enter student name for student %d: ", i + 1);
        fgets(newStudent.name, sizeof(newStudent.name), stdin);
        newStudent.name[strcspn(newStudent.name, "\n")] = '\0';

        printf("Enter student ID for student %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%d", &newStudent.studentID);

        printf("Enter midterm note for student %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%f", &newStudent.midtermNote);
        printf("Enter final note for student %d: ", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        sscanf(buffer, "%f", &newStudent.finalNote);

        saveStudent(&newStudent, filePtr);
    }
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

void printStudentAverages(FILE *filePtr)
{
    if (filePtr == NULL)
    {
        printf("Error: File pointer is NULL.\n");
        return;
    }

    char line[128];
    char name[50];
    int studentID;
    float midtermNote;
    float finalNote;

    int i = 1;
    printf("\nStudent Averages:\n");
    while (fgets(line, sizeof(line), filePtr) != NULL)
    {
        if (sscanf(line, "%49s %d %f %f", name, &studentID, &midtermNote, &finalNote) == 4)
        {
            float average = midtermNote * 0.4f + finalNote * 0.6f;
            printf("\tStudent %d:\n", i++);
            printf("\t\tName: %s\n\t\tNumber: %d\n\t\tMidterm: %.2f\n\t\tFinal: %.2f\n\t\tAverage: %.2f\n", name, studentID, midtermNote, finalNote, average);
        }
    }
}

int main(void)
{
    FILE *filePtr = fopen("students.txt", "a");

    if (filePtr == NULL)
    {
        printf("Error while opening file for writing!\n");
        return 1;
    }

    char buffer[50];
    int studentCount;

    printf("Enter number of students to save (press 0 to finish): ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%d", &studentCount);

    if (studentCount > 0)
    {
        getStudentsInfo(filePtr, studentCount);
    }

    fclose(filePtr);

    filePtr = fopen("students.txt", "r");
    printStudentAverages(filePtr);
    fclose(filePtr);

    return 0;
}