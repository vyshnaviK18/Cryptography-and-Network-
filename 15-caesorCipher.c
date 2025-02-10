#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LEN 1000

// Function to calculate letter frequencies
void calculateFrequencies(char text[], int freq[]) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to find the most frequent letter in the text
char findMostFrequentLetter(int freq[]) {
    int maxFreq = 0, maxIndex = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxIndex = i;
        }
    }
    return 'A' + maxIndex;
}

// Function to decrypt using a given shift value
void decryptWithKey(char ciphertext[], int key, char plaintext[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = base + ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE);
        } else {
            plaintext[i] = ciphertext[i]; // Keep spaces and punctuation
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to display the top N possible plaintexts
void displayTopPlaintexts(char ciphertext[], int topN) {
    int freq[ALPHABET_SIZE] = {0};
    calculateFrequencies(ciphertext, freq);
    
    char mostFreqLetter = findMostFrequentLetter(freq);
    int assumedKey = (mostFreqLetter - 'E' + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("Most frequent letter in ciphertext: %c (Assumed to be 'E')\n", mostFreqLetter);
    printf("Assumed Key: %d\n\n", assumedKey);

    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        char decrypted[MAX_TEXT_LEN];
        decryptWithKey(ciphertext, (assumedKey + i) % ALPHABET_SIZE, decrypted);
        printf("Key %2d: %s\n", (assumedKey + i) % ALPHABET_SIZE, decrypted);
    }
}

int main() {
    char ciphertext[MAX_TEXT_LEN];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline

    int topN;
    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &topN);

    displayTopPlaintexts(ciphertext, topN);

    return 0;
}

