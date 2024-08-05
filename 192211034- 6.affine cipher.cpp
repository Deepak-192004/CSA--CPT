#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

char decrypt(char c, int a, int b) {
    if (isalpha(c)) {
        c = toupper(c);
        int a_inv = modInverse(a, 26);
        if (a_inv == -1) {
            fprintf(stderr, "Error: 'a' has no modular inverse. Decryption impossible.\n");
            exit(1);
        }
        return (char)((a_inv * (c - 'A' - b + 26) % 26) + 'A');
    }
    return c;
}

int main() {
    int a, b;
    int P1 = 4;  // E
    int P2 = 19; // T
    int C1 = 1;  // B
    int C2 = 20; // U


    int x1 = P1;
    int y1 = C1;
    int x2 = P2;
    int y2 = C2;

    int a_inverse = modInverse((x1 - x2 + 26) % 26, 26);
    if (a_inverse == -1) {
        fprintf(stderr, "Error: No modular inverse found.\n");
        return 1;
    }

    a = (a_inverse * (y1 - y2 + 26) % 26) % 26;
    b = (y1 - a * x1 + 26) % 26;

    printf("Values of a and b are: a = %d, b = %d\n", a, b);

    char ciphertext[] = "BU...."; 
    char decrypted_text[sizeof(ciphertext)];

    for (size_t i = 0; i < sizeof(ciphertext) - 1; i++) {
        decrypted_text[i] = decrypt(ciphertext[i], a, b);
    }
    decrypted_text[sizeof(ciphertext) - 1] = '\0';

    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

