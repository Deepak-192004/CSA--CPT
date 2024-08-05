#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void caesarCipher(char* text, int shift) {
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + shift) % 26 + offset;
        }
    }
}

int main() {
    char text[100];
    int shift;

    printf("Enter a string to encrypt: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0';

    printf("Enter shift value (1-25): ");
    scanf("%d", &shift);

    if (shift < 1 || shift > 25) {
        printf("Invalid shift value. Please enter a value between 1 and 25.\n");
        return 1;
    }

    caesarCipher(text, shift);

    printf("Encrypted text: %s\n", text);

    return 0;
}

