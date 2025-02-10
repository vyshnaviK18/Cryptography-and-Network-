#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT_LEN 1000

// Standard English letter frequency order (most to least common)
const char ENGLISH_FREQ_ORDER[] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to calculate letter frequencies in ciphertext
void calculateFrequencies(char text[], int freq[]) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A']++;
        }
    }
}

// Function to find index of max frequency letter
int findMaxIndex(int freq[]) {
    int maxIndex = 0, maxFreq = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > maxFreq) {
            maxFreq = freq[i];
            maxIndex = i;
        }
    }
    freq[maxIndex] = 0; // Mark as used
    return maxIndex;
}

// Function to generate a decryption key mapping
void generateDecryptionKey(char decryptionKey[]) {
    int freq[ALPHABET_SIZE] = {0};
    calculateFrequencies(decryptionKey, freq);

    char cipherFreqOrder[ALPHABET_SIZE + 1]; // Stores letters sorted by frequency
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        cipherFreqOrder[i] = findMaxIndex(freq) + 'A';
    }
    cipherFreqOrder[ALPHABET_SIZE] = '\0';

    // Map ciphertext letters to guessed plaintext letters
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        decryptionKey[cipherFreqOrder[i] - 'A'] = ENGLISH_FREQ_ORDER[i];
    }
}

// Function to decrypt using the generated key
void decryptCiphertext(char ciphertext[], char decryptionKey[], char plaintext[]) {
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = base + (decryptionKey[toupper(ciphertext[i]) - 'A'] - 'A');
        } else {
            plaintext[i] = ciphertext[i]; // Keep spaces and punctuation
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char ciphertext[MAX_TEXT_LEN], decrypted[MAX_TEXT_LEN];
    char decryptionKey[ALPHABET_SIZE];

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline

    // Generate decryption key based on letter frequency analysis
    generateDecryptionKey(decryptionKey);

    // Decrypt the text
    decryptCiphertext(ciphertext, decryptionKey, decrypted);

    printf("\nPossible Plaintext (Based on Frequency Analysis):\n%s\n", decrypted);
    
    return 0;
}

