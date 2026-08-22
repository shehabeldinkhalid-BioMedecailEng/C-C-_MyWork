#include <stdio.h>

int main() {
    int arr_1[5];
    int maxVal, minVal, maxPos = 0, minPos = 0;

    for (int i = 0; i < 5; i++) {
        scanf("%d", &arr_1[i]);
    }

    // Print elements
    for (int i = 0; i < 5; i++) {
        printf("%d\t", arr_1[i]);
    }
    printf("\n");

    // Find max and min with positions
    maxVal = minVal = arr_1[0];
    for (int i = 1; i < 5; i++) {
        if (arr_1[i] > maxVal) { maxVal = arr_1[i]; maxPos = i; }
        if (arr_1[i] < minVal) { minVal = arr_1[i]; minPos = i; }
    }

    printf("The maximum Number is %d in position %d\n", maxVal, maxPos);
    printf("The minimum Number is %d in position %d\n", minVal, minPos);

    // +Point: sort ascending (bubble sort)
    for (int i = 0; i < 5 - 1; i++) {
        for (int j = 0; j < 5 - 1 - i; j++) {
            if (arr_1[j] > arr_1[j + 1]) {
                int temp = arr_1[j];
                arr_1[j] = arr_1[j + 1];
                arr_1[j + 1] = temp;
            }
        }
    }

    printf("Sorted array: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr_1[i]);
    printf("\n");

    return 0;
}
