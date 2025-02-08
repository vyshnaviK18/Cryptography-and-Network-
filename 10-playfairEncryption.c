#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

// Function to find the position of a letter in the matrix
void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I';  // Playfair treats I and J as the same
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == letter) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt a Playfair cipher text
void playfairEncrypt(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(text[i], &r1, &c1);
        findPosition(text[i + 1], &r2, &c2);

        // Apply Playfair encryption rules
        if (r1 == r2) {  // Same row
            text[i] = keyMatrix[r1][(c1 + 1) % SIZE]; 
            text[i + 1] = keyMatrix[r2][(c2 + 1) % SIZE];
        } else if (c1 == c2) {  // Same column
            text[i] = keyMatrix[(r1 + 1) % SIZE][c1]; 
            text[i + 1] = keyMatrix[(r2 + 1) % SIZE][c2];
        } else {  // Rectangle swap
            text[i] = keyMatrix[r1][c2];
            text[i + 1] = keyMatrix[r2][c1];
        }
    }
}

int main() {
    char text[] = "MUSTSEEYOUOVERCADOGANWESTCOMINGATONCE";
    playfairEncrypt(text);
    printf("Encrypted Text: %s\n", text);
    return 0;
}

