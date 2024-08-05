#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void monoalphabeticEncrypt(char* plaintext, char* ciphertext, char* key) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            if (isupper(plaintext[i])) {
                ciphertext[i] = toupper(key[index]);
            } else {
                ciphertext[i] = key[index];
            }
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

int main() {
    char key[27] = "QWERTYUIOPLKJHGFDSAZXCVBNM";
    char plaintext[100];
    char ciphertext[100];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = 0; 

    monoalphabeticEncrypt(plaintext, ciphertext, key);

    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

