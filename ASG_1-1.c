#include <stdio.h>

int main() {
    int n;
    printf("Enter the number\n");
    scanf("%d", &n);

    if ((n / 2) * 2 == n) {
        printf("The number is odd = 0\n");
        printf("The number is even = 1\n");
    } else {
        printf("The number is odd = 1\n");
        printf("The number is even = 0\n");
    }
    return 0;
}
