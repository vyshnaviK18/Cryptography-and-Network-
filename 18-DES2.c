#include <stdio.h>
#include <stdint.h>

#define KEY_SIZE 64
#define SUBKEY_SIZE 48
#define NUM_ROUNDS 16

// Permuted Choice 1 (PC-1) - 56-bit key (removes parity bits)
int PC1_Left[] = { 57, 49, 41, 33, 25, 17,  9,
                    1, 58, 50, 42, 34, 26, 18,
                   10,  2, 59, 51, 43, 35, 27,
                   19, 11,  3, 60, 52, 44, 36 };
                   
int PC1_Right[] = { 63, 55, 47, 39, 31, 23, 15,
                     7, 62, 54, 46, 38, 30, 22,
                    14,  6, 61, 53, 45, 37, 29,
                    21, 13,  5, 28, 20, 12,  4 };

// Left shifts per round
int keyShifts[NUM_ROUNDS] = { 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };

// Permuted Choice 2 (PC-2) - Generates 48-bit subkeys
int PC2[] = { 14, 17, 11, 24,  1,  5,  3, 28, 15,  6, 21, 10,
               23, 19, 12,  4, 26,  8, 16,  7, 27, 20, 13,  2,
               41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
               44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };

// Function to apply a permutation table
void applyPermutation(uint8_t *input, uint8_t *output, int *table, int size) {
    for (int i = 0; i < size; i++) {
        int bitPos = table[i] - 1;
        int bytePos = bitPos / 8;
        int bitOffset = bitPos % 8;
        int newBytePos = i / 8;
        int newBitOffset = i % 8;
        
        if (input[bytePos] & (1 << (7 - bitOffset))) {
            output[newBytePos] |= (1 << (7 - newBitOffset));
        }
    }
}

// Left circular shift
void leftShift28(uint8_t *half, int shifts) {
    uint32_t val = ((half[0] << 20) | (half[1] << 12) | (half[2] << 4) | (half[3] >> 4)) & 0x0FFFFFFF;
    val = ((val << shifts) | (val >> (28 - shifts))) & 0x0FFFFFFF;

    half[0] = (val >> 20) & 0xFF;
    half[1] = (val >> 12) & 0xFF;
    half[2] = (val >> 4)  & 0xFF;
    half[3] = (half[3] & 0x0F) | ((val & 0x0F) << 4);
}

// Key scheduling function
void generateSubkeys(uint8_t initialKey[8], uint8_t subkeys[NUM_ROUNDS][6]) {
    uint8_t C[4] = {0}, D[4] = {0};
    uint8_t permutedKey[7] = {0};

    applyPermutation(initialKey, permutedKey, PC1_Left, 28);
    memcpy(C, permutedKey, 4);
    applyPermutation(initialKey, permutedKey, PC1_Right, 28);
    memcpy(D, permutedKey, 4);

    for (int i = 0; i < NUM_ROUNDS; i++) {
        leftShift28(C, keyShifts[i]);
        leftShift28(D, keyShifts[i]);

        uint8_t combined[7] = {0};
        memcpy(combined, C, 4);
        memcpy(combined + 3, D, 4);

        applyPermutation(combined, subkeys[i], PC2, 48);
    }
}

// Main function
int main() {
    uint8_t initialKey[8] = { 0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1 };
    uint8_t subkeys[NUM_ROUNDS][6] = {0};

    generateSubkeys(initialKey, subkeys);

    printf("Generated DES Subkeys:\n");
    for (int i = 0; i < NUM_ROUNDS; i++) {
        printf("K%d: ", i + 1);
        for (int j = 0; j < 6; j++) {
            printf("%02X ", subkeys[i][j]);
        }
        printf("\n");
    }

    return 0;
}

