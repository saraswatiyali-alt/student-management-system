
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Student {
    int roll;
    char name[50];
    float marks[3];
    float total;
    float average;
    char grade;
};

struct Student students[MAX];
int count = 0;

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void calculateResult(struct Student *s);
void sortStudents();
void showTopper();
void saveToFile();
void loadFromFile();

// Calculate total, average and grade
void calculateResult(struct Student *s) {
    s->total = 0;

    for (int i = 0; i < 3; i++) {
        s->total += s->marks[i];
    }

    s->average = s->total / 3;

    if (s->average >= 90)
        s->grade = 'A';
    else if (s->average >= 75)
        s->grade = 'B';
    else if (s->average >= 60)
        s->grade = 'C';
    else if (s->average >= 40)
        s->grade = 'D';
    else
        s->grade = 'F';
}

// Add student
void addStudent() {
    if (count >= MAX) {
        printf("\nStudent limit reached!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &students[count].roll);

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", students[count].name);

    for (int i = 0; i < 3; i++) {
        printf("Enter marks for Subject %d: ", i + 1);
        scanf("%f", &students[count].marks[i]);
    }

    calculateResult(&students[count]);

    count++;

    printf("\nStudent added successfully!\n");
}

// Display all students
void displayStudents() {
    if (count == 0) {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");

    for (int i = 0; i < count; i++) {
        printf("\nRoll Number : %d", students[i].roll);
        printf("\nName        : %s", students[i].name);

        for (int j = 0; j < 3; j++) {
            printf("\nSubject %d   : %.2f",
                   j + 1, students[i].marks[j]);
        }

        printf("\nTotal       : %.2f", students[i].total);
        printf("\nAverage     : %.2f", students[i].average);
        printf("\nGrade       : %c\n", students[i].grade);
    }
}

// Search student
void searchStudent() {
    int roll, found = 0;

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nStudent Found!\n");
            printf("Name: %s\n", students[i].name);
            printf("Average: %.2f\n", students[i].average);
            printf("Grade: %c\n", students[i].grade);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Update student
void updateStudent() {
    int roll, found = 0;

    printf("\nEnter roll number to update: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            printf("\nEnter new name: ");
            scanf(" %49[^\n]", students[i].name);

            for (int j = 0; j < 3; j++) {
                printf("Enter new marks for Subject %d: ", j + 1);
                scanf("%f", &students[i].marks[j]);
            }

            calculateResult(&students[i]);

            printf("\nRecord updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Delete student
void deleteStudent() {
    int roll, found = 0;

    printf("\nEnter roll number to delete: ");
    scanf("%d", &roll);

    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }

            count--;
            found = 1;

            printf("\nStudent deleted successfully!\n");
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

// Sort students by average marks
void sortStudents() {
    struct Student temp;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].average <
                students[j + 1].average) {

                temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nStudents sorted by marks!\n");
}

// Find topper
void showTopper() {
    if (count == 0) {
        printf("\nNo records available!\n");
        return;
    }

    int top = 0;

    for (int i = 1; i < count; i++) {
        if (students[i].average > students[top].average) {
            top = i;
        }
    }

    printf("\n========== CLASS TOPPER ==========\n");
    printf("Roll Number: %d\n", students[top].roll);
    printf("Name       : %s\n", students[top].name);
    printf("Total      : %.2f\n", students[top].total);
    printf("Average    : %.2f\n", students[top].average);
    printf("Grade      : %c\n", students[top].grade);
}

// Save records to file
void saveToFile() {
    FILE *fp = fopen("students.dat", "wb");

    if (fp == NULL) {
        printf("\nUnable to open file!\n");
        return;
    }

    fwrite(&count, sizeof(int), 1, fp);
    fwrite(students, sizeof(struct Student), count, fp);

    fclose(fp);

    printf("\nRecords saved successfully!\n");
}

// Load records from file
void loadFromFile() {
    FILE *fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo previous records found.\n");
        return;
    }

    if (fread(&count, sizeof(int), 1, fp) != 1 ||
        count < 0 || count > MAX) {
        count = 0;
        fclose(fp);
        printf("\nInvalid data file!\n");
        return;
    }

    if (fread(students, sizeof(struct Student), count, fp)
        != (size_t)count) {
        count = 0;
        printf("\nUnable to read student records!\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    printf("\nRecords loaded successfully!\n");
}

// Main function
int main() {
    int choice;

    loadFromFile();

    do {
        printf("\n\n");
        printf("====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM    \n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Sort Students\n");
        printf("7. Show Class Topper\n");
        printf("8. Save Records\n");
        printf("9. Exit\n");

        printf("====================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input!\n");
            break;
        }

        switch (choice) {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                sortStudents();
                break;

            case 7:
                showTopper();
                break;

            case 8:
                saveToFile();
                break;

            case 9:
                saveToFile();
                printf("\nThank you for using the system!\n");
                break;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 9);

    return 0;
}
