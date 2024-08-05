#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long rsa_encrypt(long long plaintext, long long e, long long n) {
    return mod_exp(plaintext, e, n);
}

long long rsa_decrypt(long long ciphertext, long long d, long long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {

    long long n = 3599; 
    long long e = 31; 
    long long d = 71;

    char message[] = "HELLO";
    int len = strlen(message);

    long long encrypted[len];
    for (int i = 0; i < len; i++) {
        long long plaintext = message[i] - 'A'; 
        encrypted[i] = rsa_encrypt(plaintext, e, n);
        printf("Encrypted %c: %lld\n", message[i], encrypted[i]);
    }

    char decrypted[len + 1];
    for (int i = 0; i < len; i++) {
        long long decrypted_num = rsa_decrypt(encrypted[i], d, n);
        decrypted[i] = (char)(decrypted_num + 'A');
    }
    decrypted[len] = '\0';

    printf("Decrypted message: %s\n", decrypted);

    return 0;
}

