#include <stdio.h>

struct Student {
    char name[30];
    int age;
    int degree;
    int section;
};

void print(struct Student *s) {   // pointer to array of structs
    for (int i = 0; i < 5; i++) {
        printf("Student %d\n\n", i + 1);
        printf("Name    : %s\n", (s + i)->name);   // same as s[i].name
        printf("Age     : %d\n", (s + i)->age);
        printf("Degree  : %d\n", (s + i)->degree);
        printf("Section : %d\n\n", (s + i)->section);
    }
}

int main() {
    struct Student students[5];

    for (int i = 0; i < 5; i++) {
        printf("Enter data for student %d\n", i + 1);
        printf("Name: ");     scanf("%s", students[i].name);
        printf("Age: ");      scanf("%d", &students[i].age);
        printf("Degree: ");   scanf("%d", &students[i].degree);
        printf("Section: ");  scanf("%d", &students[i].section);
    }

    print(students);   // array name decays to address of first element

    return 0;
}
