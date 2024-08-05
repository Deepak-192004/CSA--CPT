#include <stdio.h>
#include <stdlib.h>
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

int main() {
    long long q = 23; 
    long long a = 5;  
    long long xA = 6; 
    long long yA = mod_exp(a, xA, q);

    long long xB = 15;
    long long yB = mod_exp(a, xB, q);

    long long KA = mod_exp(yB, xA, q);

    long long KB = mod_exp(yA, xB, q);

    printf("Alice's computed key: %lld\n", KA);
    printf("Bob's computed key: %lld\n", KB);

    if (KA == KB) {
        printf("Key exchange successful!\n");
    } else {
        printf("Key exchange failed.\n");
    }

    return 0;
}

