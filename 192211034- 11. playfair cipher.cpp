#include <stdio.h>
#include <math.h>
unsigned long long factorial(int n) {
    if (n == 0) return 1;
    unsigned long long fact = 1;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    int num_letters = 25; 
    
    unsigned long long total_permutations = factorial(num_letters);
    
    double log2_total_permutations = log2(total_permutations);
    
    unsigned long long symmetric_divisor = factorial(4);
    unsigned long long unique_keys = total_permutations / symmetric_divisor;
    
    double log2_unique_keys = log2(unique_keys);
    
    printf("Total possible keys (25!): %llu\n", total_permutations);
    printf("Approximate power of 2 (total keys): 2^%.2f\n", log2_total_permutations);
    printf("Effectively unique keys: %llu\n", unique_keys);
    printf("Approximate power of 2 (unique keys): 2^%.2f\n", log2_unique_keys);
    
    return 0;
}

