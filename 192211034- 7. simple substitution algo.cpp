#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 500
void calculateFrequency(const char *ciphertext, int *freq) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            freq[ciphertext[i]]++;
        }
    }
}
void printFrequency(int *freq) {
    for (int i = 0; i < 128; i++) {
        if (freq[i] > 0) {
            printf("Character '%c' : %d times\n", i, freq[i]);
        }
    }
}

void decrypt(const char *ciphertext, char *plaintext, const char *substitution) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isprint(ciphertext[i])) {
            plaintext[i] = substitution[ciphertext[i]];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                                "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                                ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 (‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    int freq[128] = {0};
    calculateFrequency(ciphertext, freq);
    printFrequency(freq);
    
    char substitution[128];
    for (int i = 0; i < 128; i++) {
        substitution[i] = i;
    }
    
    substitution['‡'] = 'e';
    substitution['5'] = 't';
    substitution['3'] = 'h';
    
    char plaintext[MAX_TEXT];
    decrypt(ciphertext, plaintext, substitution);
    
    printf("Decrypted message: %s\n", plaintext);
    
    return 0;
}

