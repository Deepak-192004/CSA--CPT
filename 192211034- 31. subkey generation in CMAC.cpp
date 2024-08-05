#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16
#define CONST_64 0x1B
#define CONST_128 0x87

void generate_subkey(uint8_t *key, int block_size, uint8_t constant) {
    int carry = key[0] & 0x80;
    for (int i = 0; i < block_size - 1; i++) {
        key[i] = (key[i] << 1) | (key[i + 1] >> 7);
    }
    key[block_size - 1] <<= 1;
    if (carry) key[block_size - 1] ^= constant;
}

void print_key(const char *label, const uint8_t *key, int block_size) {
    printf("%s: ", label);
    for (int i = 0; i < block_size; i++) printf("%02x", key[i]);
    printf("\n");
}

int main() {
    uint8_t key_64[BLOCK_SIZE_64] = {0};
    uint8_t key_128[BLOCK_SIZE_128] = {0};

    generate_subkey(key_64, BLOCK_SIZE_64, CONST_64);
    print_key("Subkey 1 (64-bit)", key_64, BLOCK_SIZE_64);
    generate_subkey(key_64, BLOCK_SIZE_64, CONST_64);
    print_key("Subkey 2 (64-bit)", key_64, BLOCK_SIZE_64);

    generate_subkey(key_128, BLOCK_SIZE_128, CONST_128);
    print_key("Subkey 1 (128-bit)", key_128, BLOCK_SIZE_128);
    generate_subkey(key_128, BLOCK_SIZE_128, CONST_128);
    print_key("Subkey 2 (128-bit)", key_128, BLOCK_SIZE_128);

    return 0;
}

