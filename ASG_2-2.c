#include <stdio.h>
#include <math.h>

int main() {
    int n, original, digit, digitCount = 0;
    long sum = 0;

    printf("enter the number=");
    scanf("%d", &n);
    original = n;

    // Step 1: count digits
    int temp = n;
    while (temp != 0) {
        temp /= 10;
        digitCount++;
    }

    // Step 2: sum each digit raised to digitCount
    temp = n;
    while (temp != 0) {
        digit = temp % 10;
        sum += (long)pow(digit, digitCount);
        temp /= 10;
    }

    // Step 3: compare
    if (sum == original)
        printf("armstrong  number\n");
    else
        printf("not armstrong number\n");

    return 0;
}
