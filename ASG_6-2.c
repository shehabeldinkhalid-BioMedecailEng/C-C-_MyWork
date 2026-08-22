#include <stdio.h>

struct Complex {
    float real;
    float imag;
};

struct Complex add(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

int main() {
    struct Complex c1, c2, sum;

    printf("For 1st complex number\n");
    printf("Enter real and imaginary part respectively:\n");
    scanf("%f %f", &c1.real, &c1.imag);

    printf("\nFor 2nd complex number\n");
    printf("Enter real and imaginary part respectively:\n");
    scanf("%f %f", &c2.real, &c2.imag);

    sum = add(c1, c2);

    printf("Sum = %.1f + %.1fi\n", sum.real, sum.imag);
    return 0;
}
