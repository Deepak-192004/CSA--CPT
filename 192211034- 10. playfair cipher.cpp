#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char matrix[SIZE][SIZE] = {
    {'m', 'f', 'h', 'i', 'k'},
    {'u', 'n', 'o', 'p', 'q'},
    {'z', 'v', 'w', 'x', 'y'},
    {'e', 'l', 'a', 'r', 'g'},
    {'d', 's', 't', 'b', 'c'}
};
void preprocessText(char input[], char output[]) {
    int len = strlen(input);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (input[i] == 'j') input[i] = 'i'; 
        if (isalpha(input[i])) {
            if (j > 0 && output[j-1] == tolower(input[i]) && j % 2 != 0) {
                output[j++] = 'x';
            }
            output[j++] = tolower(input[i]);
        }
    }

    if (j % 2 != 0) {
        output[j++] = 'x'; 
    }

    output[j] = '\0';
}

void findPosition(char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void encrypt(char plaintext[], char ciphertext[]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(plaintext[i], &row1, &col1);
        findPosition(plaintext[i+1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i+1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i+1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i+1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once";
    char preparedText[200], ciphertext[200];

    preprocessText(plaintext, preparedText);
    encrypt(preparedText, ciphertext);

    printf("Plaintext: %s\n", plaintext);
    printf("Prepared Text: %s\n", preparedText);
    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

