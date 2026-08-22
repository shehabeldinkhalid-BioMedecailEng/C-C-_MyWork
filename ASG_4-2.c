#include <stdio.h>
#include <string.h>

int main() {
    char sentence[100];
    char *words[50];
    int count = 0;

    printf("Enter a sentence: ");
    fgets(sentence, sizeof(sentence), stdin);
    sentence[strcspn(sentence, "\n")] = '\0'; // remove trailing newline

    // Split sentence into words
    char *token = strtok(sentence, " ");
    while (token != NULL) {
        words[count] = token;
        count++;
        token = strtok(NULL, " ");
    }

    // Print words in reverse order
    for (int i = count - 1; i >= 0; i--) {
        printf("%s ", words[i]);
    }
    printf("\n");

    return 0;
}
