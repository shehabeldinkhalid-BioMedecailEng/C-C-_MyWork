#include <stdio.h>

int main() {
    int num, n;
    printf("Enter any number: ");
    scanf("%d", &num);
    printf("Enter nth bit to toggle (0-31): ");
    scanf("%d", &n);

    printf("Bit toggled successfully.\n\n");
    printf("Number before toggling %d bit: %d (in decimal)\n", n, num);

    num = num ^ (1 << n);   // flip only bit n

    printf("Number after toggling %d bit: %d (in decimal)\n", n, num);
    return 0;
}
