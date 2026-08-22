#include <stdio.h>

int main() {
    char op;
    float num1, num2, result;

    printf("Enter the operator\n");
    scanf(" %c", &op);          // space before %c skips leftover newline
    printf("Enter Number_1\n");
    scanf("%f", &num1);
    printf("Enter Number_2\n");
    scanf("%f", &num2);

    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/':
            if (num2 == 0) {
                printf("Error: division by zero\n");
                return 1;
            }
            result = num1 / num2;
            break;
        default:
            printf("Invalid operator\n");
            return 1;
    }

    printf("The result = %.2f\n", result);
    return 0;
}
