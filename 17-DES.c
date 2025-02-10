#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define NUM_ROUNDS 16

// Initial and Final Permutations (IP, FP)
int IP[] = { 58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
             62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
             57, 49, 41, 33, 25, 17,  9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
             61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7 };

int FP[] = { 40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
             38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
             36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
             34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41,  9, 49, 17, 57, 25 };

// Example S-boxes, P-boxes, and Expansion functions
void applyPermutation(uint8_t *data, const int *table, int n) {
    uint8_t temp[BLOCK_SIZE] = {0};
    for (int i = 0; i < n; i++) {
        int bitPos = table[i] - 1;
        int bytePos = bitPos / 8;
        int bitOffset = bitPos % 8;
        int newBytePos = i / 8;
        int newBitOffset = i % 8;
        if (data[bytePos] & (1 << (7 - bitOffset))) {
            temp[newBytePos] |= (1 << (7 - newBitOffset));
        }
    }
    memcpy(data, temp, BLOCK_SIZE);
}

// DES Key Generation (Reverse Order for Decryption)
void generateKeys(uint8_t keys[NUM_ROUNDS][BLOCK_SIZE]) {
    for (int i = 0; i < NUM_ROUNDS; i++) {
        for (int j = 0; j < BLOCK_SIZE; j++) {
            keys[NUM_ROUNDS - 1 - i][j] = rand() % 256;  // Random keys for testing
        }
    }
}

// DES Decryption Function
void DESDecrypt(uint8_t *block, uint8_t keys[NUM_ROUNDS][BLOCK_SIZE]) {
    applyPermutation(block, IP, 64);
    
    for (int round = 0; round < NUM_ROUNDS; round++) {
        // Feistel function (simplified for demonstration)
        uint8_t temp = block[0];
        for (int i = 0; i < BLOCK_SIZE - 1; i++)
            block[i] = block[i + 1] ^ keys[round][i];
        block[BLOCK_SIZE - 1] = temp;
    }

    applyPermutation(block, FP, 64);
}

// Main Function
int main() {
    uint8_t data[BLOCK_SIZE] = "DESDATA"; // Example 8-byte encrypted data
    uint8_t keys[NUM_ROUNDS][BLOCK_SIZE];

    generateKeys(keys);

    printf("Encrypted Data: %s\n", data);
    DESDecrypt(data, keys);
    printf("Decrypted Data: %s\n", data);

    return 0;
}

