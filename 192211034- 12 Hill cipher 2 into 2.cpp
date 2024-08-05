#include <stdio.h>
#include <string.h>

int charToNum(char c) {
    return c - 'a';
}

char numToChar(int n) {
    return n + 'a';
}

void hillCipherEncrypt(char *message, int key[2][2], char *ciphertext) {
    int i, j;
    int messageLength = strlen(message);
    
    if (messageLength % 2 != 0) {
        strcat(message, "x");
        messageLength++;
    }
    
    for (i = 0; i < messageLength; i += 2) {
        int x = charToNum(message[i]);
        int y = charToNum(message[i + 1]);
        
        ciphertext[i] = numToChar((key[0][0] * x + key[0][1] * y) % 26);
        ciphertext[i + 1] = numToChar((key[1][0] * x + key[1][1] * y) % 26);
    }
    ciphertext[messageLength] = '\0';
}

int main() {
    char message[] = "meetmeattheusualplaceattenratherthaneightoclock";
    char ciphertext[100];
    
    int key[2][2] = {
        {9, 4},
        {5, 7}
    };
    
    hillCipherEncrypt(message, key, ciphertext);
    
    printf("Original message: %s\n", message);
    printf("Encrypted message: %s\n", ciphertext);
    
    return 0;
}

