#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

char keyMatrix[SIZE][SIZE];

// Function to remove duplicate letters from a keyword and construct Playfair matrix
void generateKeyMatrix(char key[]) {
    int used[26] = {0};
    int index = 0;

    // Fill key matrix with keyword
    for (int i = 0; key[i] != '\0'; i++) {
        char letter = toupper(key[i]);
        if (letter == 'J') letter = 'I'; // Playfair treats I and J as the same letter
        if (!used[letter - 'A']) {
            keyMatrix[index / SIZE][index % SIZE] = letter;
            used[letter - 'A'] = 1;
            index++;
        }
    }

    // Fill remaining letters
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            keyMatrix[index / SIZE][index % SIZE] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}

// Function to find the position of a letter in the key matrix
void findPosition(char letter, int *row, int *col) {
    if (letter == 'J') letter = 'I';
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

// Function to decrypt a Playfair cipher text
void playfairDecrypt(char cipher[]) {
    int len = strlen(cipher);
    for (int i = 0; i < len; i += 2) {
        int r1, c1, r2, c2;
        findPosition(cipher[i], &r1, &c1);
        findPosition(cipher[i + 1], &r2, &c2);

        // Apply Playfair decryption rules
        if (r1 == r2) { // Same row
            cipher[i] = keyMatrix[r1][(c1 + 4) % SIZE];  // Move left
            cipher[i + 1] = keyMatrix[r2][(c2 + 4) % SIZE];
        } else if (c1 == c2) { // Same column
            cipher[i] = keyMatrix[(r1 + 4) % SIZE][c1];  // Move up
            cipher[i + 1] = keyMatrix[(r2 + 4) % SIZE][c2];
        } else { // Rectangle swap
            cipher[i] = keyMatrix[r1][c2];
            cipher[i + 1] = keyMatrix[r2][c1];
        }
    }
}

int main() {
    char key[] = "KEYWORD";
    char cipherText[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPO"; // Without spaces

    generateKeyMatrix(key);
    playfairDecrypt(cipherText);

    printf("Decrypted Text: %s\n", cipherText);
    return 0;
}

