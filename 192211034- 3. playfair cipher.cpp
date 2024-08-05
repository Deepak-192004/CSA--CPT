#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareMatrix(char key[], char matrix[SIZE][SIZE]) {
    int len = strlen(key);
    int used[26] = {0};
    int x = 0, y = 0;
    
    for (int i = 0; i < len; i++) {
        if (key[i] == 'j') key[i] = 'i'; 
        if (!used[key[i] - 'a']) {
            matrix[x][y] = key[i];
            used[key[i] - 'a'] = 1;
            y++;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
    
    for (char ch = 'a'; ch <= 'z'; ch++) {
        if (ch == 'j') continue; 
        if (!used[ch - 'a']) {
            matrix[x][y] = ch;
            used[ch - 'a'] = 1;
            y++;
            if (y == SIZE) {
                y = 0;
                x++;
            }
        }
    }
}

void prepareText(char input[], char output[]) {
    int len = strlen(input);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        if (input[i] == 'j') input[i] = 'i'; 
        if (isalpha(input[i])) {
            if (j > 0 && output[j-1] == input[i] && j % 2 != 0) {
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

void findPosition(char ch, char matrix[SIZE][SIZE], int *row, int *col) {
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

void encrypt(char plaintext[], char ciphertext[], char matrix[SIZE][SIZE]) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(plaintext[i], matrix, &row1, &col1);
        findPosition(plaintext[i+1], matrix, &row2, &col2);
        
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
    char key[SIZE*SIZE], plaintext[100], preparedText[200], ciphertext[200];
    char matrix[SIZE][SIZE];
    
    printf("Enter the key: ");
    scanf("%s", key);
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);
    
    prepareMatrix(key, matrix);
    prepareText(plaintext, preparedText);
    encrypt(preparedText, ciphertext, matrix);
    
    printf("Prepared Text: %s\n", preparedText);
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

