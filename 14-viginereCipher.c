#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Function to convert a character to its numerical equivalent (A=0, B=1, ..., Z=25)
int charToNum(char c) {
    return toupper(c) - 'A';
}

// Function to convert a numerical equivalent back to a character
char numToChar(int n) {
    return (n % MOD) + 'A';
}

// Function to encrypt plaintext using the given key stream
void encryptOTP(char plaintext[], int key[], char ciphertext[], int length) {
    for (int i = 0; i < length; i++) {
        if (plaintext[i] != ' ') {
            int p = charToNum(plaintext[i]);
            ciphertext[i] = numToChar((p + key[i]) % MOD);
        } else {
            ciphertext[i] = ' '; // Preserve spaces
        }
    }
    ciphertext[length] = '\0'; // Null-terminate string
}

// Function to find an alternative key so ciphertext decrypts to a new plaintext
void findAlternateKey(char ciphertext[], char newPlaintext[], int altKey[], int length) {
    for (int i = 0; i < length; i++) {
        if (ciphertext[i] != ' ') {
            int c = charToNum(ciphertext[i]);
            int p = charToNum(newPlaintext[i]);
            altKey[i] = (p - c + MOD) % MOD; // Compute the new key value
        } else {
            altKey[i] = -1; // Placeholder for spaces
        }
    }
}

// Function to print the key stream
void printKeyStream(int key[], int length) {
    for (int i = 0; i < length; i++) {
        if (key[i] != -1) {
            printf("%d ", key[i]);
        } else {
            printf("  "); // Maintain spacing
        }
    }
    printf("\n");
}

int main() {
    char plaintext[] = "SEND MORE MONEY";
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Given key stream
    int length = strlen(plaintext);

    char ciphertext[length + 1];
    encryptOTP(plaintext, key, ciphertext, length);

    printf("Plaintext:  %s\n", plaintext);
    printf("Key Stream: ");
    printKeyStream(key, length);
    printf("Ciphertext: %s\n\n", ciphertext);

    // Part (b): Find an alternative key for new plaintext "CASH NOT NEEDED"
    char newPlaintext[] = "CASH NOT NEEDED";
    int altKey[length];

    findAlternateKey(ciphertext, newPlaintext, altKey, length);

    printf("New Plaintext: %s\n", newPlaintext);
    printf("Alternative Key Stream: ");
    printKeyStream(altKey, length);

    return 0;
}

