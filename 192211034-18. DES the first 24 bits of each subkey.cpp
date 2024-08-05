#include <stdio.h>
#include <stdint.h>

void leftShift(uint32_t *half, int shifts) {
    *half = ((*half << shifts) | (*half >> (28 - shifts))) & 0x0FFFFFFF;
}

void generateSubkeys(uint64_t key, uint64_t subkeys[16]) {
 
    int PC1[56] = {
        57, 49, 41, 33, 25, 17, 9,
        1, 58, 50, 42, 34, 26, 18,
        10, 2, 59, 51, 43, 35, 27,
        19, 11, 3, 60, 52, 44, 36,
        63, 55, 47, 39, 31, 23, 15,
        7, 62, 54, 46, 38, 30, 22,
        14, 6, 61, 53, 45, 37, 29,
        21, 13, 5, 28, 20, 12, 4
    };

    int PC2[48] = {
        14, 17, 11, 24, 1, 5, 3, 28,
        15, 6, 21, 10, 23, 19, 12, 4,
        26, 8, 16, 7, 27, 20, 13, 2,
        41, 52, 31, 37, 47, 55, 30, 40,
        51, 45, 33, 48, 44, 49, 39, 56,
        34, 53, 46, 42, 50, 36, 29, 32
    };

    int shifts[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    uint64_t permutedKey = 0;
    for (int i = 0; i < 56; i++) {
        permutedKey <<= 1;
        permutedKey |= (key >> (64 - PC1[i])) & 1;
    }

    uint32_t C = (permutedKey >> 28) & 0x0FFFFFFF;
    uint32_t D = permutedKey & 0x0FFFFFFF;

    for (int round = 0; round < 16; round++) {
        leftShift(&C, shifts[round]);
        leftShift(&D, shifts[round]);

        uint64_t combined = ((uint64_t)C << 28) | D;
        subkeys[round] = 0;
        for (int i = 0; i < 48; i++) {
            subkeys[round] <<= 1;
            subkeys[round] |= (combined >> (56 - PC2[i])) & 1;
        }
    }
}

void printSubkeys(uint64_t subkeys[16]) {
    for (int i = 0; i < 16; i++) {
        printf("Subkey %2d: %012llx\n", i + 1, subkeys[i]);
    }
}

int main() {
    uint64_t key = 0x133457799BBCDFF1; 
    uint64_t subkeys[16];
    generateSubkeys(key, subkeys);
    printSubkeys(subkeys);
    return 0;
}

