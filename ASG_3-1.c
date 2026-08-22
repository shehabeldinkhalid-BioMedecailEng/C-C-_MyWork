#include <stdio.h>

void swap(int x, int y) {
    printf("befor swapping\n");
    printf("x = %d   y = %d\n", x, y);

    x = x + y;   // x now holds sum of both
    y = x - y;   // y becomes original x
    x = x - y;   // x becomes original y

    printf("after swapping\n");
    printf("x = %d   y = %d\n", x, y);
}

int main() {
    int a, b;
    printf("Enter first number\n");
    scanf("%d", &a);
    printf("Enter second number\n");
    scanf("%d", &b);

    swap(a, b);
    return 0;
}
