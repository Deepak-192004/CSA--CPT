#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void vigenereEncrypt(char* plaintext, char* ciphertext, char* key) {
    int lenText = strlen(plaintext);
    int lenKey = strlen(key);

    for (int i = 0, j = 0; i < lenText; i++) {
        char c = plaintext[i];
        if (isalpha(c)) {
            char offset = isupper(c) ? 'A' : 'a';
            ciphertext[i] = (c + toupper(key[j]) - 2 * offset) % 26 + offset;
            j = (j + 1) % lenKey;
        } else {
            ciphertext[i] = c;
        }
    }
    ciphertext[lenText] = '\0';
}

int main() {
    char key[100];
    char plaintext[100];
    char ciphertext[100];

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = 0;  

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0;  

    vigenereEncrypt(plaintext, ciphertext, key);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

