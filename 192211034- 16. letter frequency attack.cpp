#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

const double englishFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094,
    6.966, 0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929,
    0.095, 5.987, 6.327, 9.056, 2.758, 0.978, 2.360, 0.150,
    1.974, 0.074
};

void computeFrequency(const char *text, double freq[ALPHABET_SIZE]) {
    int count[ALPHABET_SIZE] = {0};
    int length = strlen(text);

    for (int i = 0; i < length; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            count[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
        }
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i] = (double)count[i] / length * 100;
    }
}

double chiSquaredStatistic(const double observed[ALPHABET_SIZE], int shift) {
    double chiSquared = 0.0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        int shiftedIndex = (i + shift) % ALPHABET_SIZE;
        double expected = englishFrequencies[shiftedIndex];
        double diff = observed[i] - expected;
        chiSquared += (diff * diff) / expected;
    }

    return chiSquared;
}

void decrypt(const char *ciphertext, char *plaintext, int shift) {
    int length = strlen(ciphertext);
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = ((ciphertext[i] - 'a' - shift + ALPHABET_SIZE) % ALPHABET_SIZE) + 'a';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[length] = '\0';
}

void letterFrequencyAttack(const char *ciphertext, int topN) {
    double observed[ALPHABET_SIZE];
    computeFrequency(ciphertext, observed);

    double chiSquaredValues[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        chiSquaredValues[i] = chiSquaredStatistic(observed, i);
    }
    int topShifts[topN];
    for (int i = 0; i < topN; i++) {
        topShifts[i] = -1;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; j < topN; j++) {
            if (topShifts[j] == -1 || chiSquaredValues[i] < chiSquaredValues[topShifts[j]]) {
                for (int k = topN - 1; k > j; k--) {
                    topShifts[k] = topShifts[k - 1];
                }
                topShifts[j] = i;
                break;
            }
        }
    }
    for (int i = 0; i < topN; i++) {
        char plaintext[256];
        decrypt(ciphertext, plaintext, topShifts[i]);
        printf("Shift %2d: %s\n", topShifts[i], plaintext);
    }
}

int main() {
    char ciphertext[256];
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;  

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);

    letterFrequencyAttack(ciphertext, topN);

    return 0;
}

