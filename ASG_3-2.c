#include <stdio.h>

// Recursive version
int fibRecursive(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibRecursive(n - 1) + fibRecursive(n - 2);
}

// Iterative version
void fibIterative(int n) {
    int a = 0, b = 1, next;
    printf("The Fibonacci Series will be: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        next = a + b;
        a = b;
        b = next;
    }
    printf("\n");
}

int main() {
    int terms;

    printf("Enter the number of terms: ");
    scanf("%d", &terms);
    printf("Fibonacci Series: ");
    for (int i = 0; i < terms; i++) {
        printf("%d, ", fibRecursive(i));
    }
    printf("\n\n");

    printf("Please enter your preferred number of elements here: ");
    scanf("%d", &terms);
    fibIterative(terms);

    return 0;
}
