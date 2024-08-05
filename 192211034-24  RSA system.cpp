#include <stdio.h>

// Function to calculate the greatest common divisor
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Extended Euclidean Algorithm to find the multiplicative inverse
int extended_gcd(int a, int b, int *x, int *y) {
    if (b == 0) {
        *x = 1;
        *y = 0;
        return a;
    }
    int x1, y1;
    int gcd = extended_gcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return gcd;
}

// Function to calculate (base^exp) % mod
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

// RSA encryption function
long long rsa_encrypt(long long plaintext, long long e, long long n) {
    return mod_exp(plaintext, e, n);
}

// RSA decryption function
long long rsa_decrypt(long long ciphertext, long long d, long long n) {
    return mod_exp(ciphertext, d, n);
}

int main() {
    // Given public key
    long long e = 31;
    long long n = 3599;
    
    // Step 1: Determine p and q by trial-and-error factorization
    long long p = 59; // Found by factorization
    long long q = 61; // Found by factorization
    
    // Step 2: Calculate f(n)
    long long phi_n = (p - 1) * (q - 1); // f(n) = (p-1)*(q-1)

    // Step 3: Find the multiplicative inverse of e modulo f(n)
    int x, y;
    extended_gcd(e, phi_n, &x, &y);
    long long d = (x % phi_n + phi_n) % phi_n; // Make sure d is positive
    
    printf("Public Key: (e = %lld, n = %lld)\n", e, n);
    printf("Private Key: d = %lld\n", d);
    
    // Step 4: Test RSA encryption and decryption
    long long plaintext = 123; // Example plaintext
    long long ciphertext = rsa_encrypt(plaintext, e, n);
    long long decryptedtext = rsa_decrypt(ciphertext, d, n);
    
    printf("Plaintext: %lld\n", plaintext);
    printf("Ciphertext: %lld\n", ciphertext);
    printf("Decrypted text: %lld\n", decryptedtext);
    
    return 0;
}

