#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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
int generate_new_e(long long phi_n) {
    int e;
    do {
        e = rand() % phi_n;
    } while (gcd(e, phi_n) != 1);
    return e;
}

int main() {
    srand(time(0));
    long long p = 59;
    long long q = 61;
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);

    int e = generate_new_e(phi_n);

    int x, y;
    extended_gcd(e, phi_n, &x, &y);
    long long d = (x % phi_n + phi_n) % phi_n; 

    printf("New Public Key: e = %d\n", e);
    printf("New Private Key: d = %lld\n", d);

    return 0;
}

