#include <stdio.h>

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

int main() {
    long long e = 31;
    long long n = 3599;
    
    long long common_factor = 59; 
    long long p = common_factor;
    long long q = n / p;
    
    long long phi_n = (p - 1) * (q - 1);
    
    int x, y;
    extended_gcd(e, phi_n, &x, &y);
    long long d = (x % phi_n + phi_n) % phi_n; 
    
    printf("Private Key: d = %lld\n", d);
    
    return 0;
}

