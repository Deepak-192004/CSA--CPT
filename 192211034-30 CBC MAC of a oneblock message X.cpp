#include <stdio.h>
#include <stdint.h>

#define BLOCK_SIZE 16

void xor_encrypt(uint8_t *output, const uint8_t *input, const uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i];
    }
}

void cbc_mac(uint8_t *T, const uint8_t *K, const uint8_t *X) {
    uint8_t IV[BLOCK_SIZE] = {0}; 
    uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = X[i] ^ IV[i];
    }
    xor_encrypt(T, temp, K);
}

void print_block(const char *label, const uint8_t *block) {
    printf("%s: ", label);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02x", block[i]);
    }
    printf("\n");
}

int main() {
    uint8_t K[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 
                             0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
    uint8_t X[BLOCK_SIZE] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 
                             0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20};

    uint8_t T[BLOCK_SIZE];
    cbc_mac(T, K, X);
    print_block("T = MAC(K, X)", T);

    uint8_t X_XOR_T[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        X_XOR_T[i] = X[i] ^ T[i];
    }
    print_block("X ? T", X_XOR_T);

    uint8_t T_two_block[BLOCK_SIZE];
    uint8_t temp[BLOCK_SIZE];

    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = X[i] ^ 0; 
    }
    xor_encrypt(temp, temp, K);

    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] = X_XOR_T[i] ^ temp[i];
    }
    xor_encrypt(T_two_block, temp, K);

    print_block("CBC-MAC for X || (X ? T)", T_two_block);

    return 0;
}

