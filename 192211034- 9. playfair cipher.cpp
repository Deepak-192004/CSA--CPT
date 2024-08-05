#include <stdio.h>
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

void preprocessText(char input[], char output[]) {
    int len = strlen(input);
    int j = 0;
    
    for (int i = 0; i < len; i++) {
        if (input[i] == 'j') input[i] = 'i'; 
        if (isalpha(input[i])) {
            output[j++] = tolower(input[i]);
        }
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

void decrypt(char ciphertext[], char plaintext[], char matrix[SIZE][SIZE]) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        int row1, col1, row2, col2;
        findPosition(ciphertext[i], matrix, &row1, &col1);
        findPosition(ciphertext[i + 1], matrix, &row2, &col2);
        
        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 - 1 + SIZE) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 - 1 + SIZE) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 - 1 + SIZE) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 - 1 + SIZE) % SIZE][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "keyword"; 
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONECUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char matrix[SIZE][SIZE];
    char preparedText[200], plaintext[200];
    
    prepareMatrix(key, matrix);
    preprocessText(ciphertext, preparedText);
    decrypt(preparedText, plaintext, matrix);
    
    printf("Ciphertext: %s\n", ciphertext);
    printf("Prepared Text: %s\n", preparedText);
    printf("Decrypted Text: %s\n", plaintext);
    
    return 0;
}

