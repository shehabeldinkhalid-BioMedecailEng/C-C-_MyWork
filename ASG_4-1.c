#include <stdio.h>

void edit(int *p) {
    *p = *p + 1;   // dereference: go to the address and change the value there
}

int main() {
    int x;
    printf("Enter the value of x\n");
    scanf("%d", &x);

    printf("Before calling edit x = %d\n", x);
    edit(&x);        // pass the ADDRESS of x
    printf("After  calling edit x = %d\n", x);

    /* +POINT: Store [5, 20, 80] inside x without overwriting, then print them.
       Since a single int can't hold 3 values at once, we use pointer
       arithmetic over separate memory slots (an array) so nothing
       gets overwritten. */
    int values[3];
    int *ptr = values;   // ptr points to values[0]

    *ptr = 5;
    ptr++;                // move pointer to next memory slot (values[1])
    *ptr = 20;
    ptr++;                // move to values[2]
    *ptr = 80;

    ptr = values;          // reset pointer to the start
    printf("\nStored values:\n");
    for (int i = 0; i < 3; i++) {
        printf("%d\n", *ptr);
        ptr++;
    }

    return 0;
}
