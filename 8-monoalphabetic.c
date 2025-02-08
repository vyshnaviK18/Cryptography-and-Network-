#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to create a monoalphabetic cipher map using a keyword
void generateCipherAlphabet(char key[], char cipherAlphabet[]) {
    int used[26] = {0}; // Track used letters
    int index = 0;

    // Insert keyword letters first
    for (int i = 0; key[i] != '\0'; i++) {
        char letter = toupper(key[i]);
        if (!used[letter - 'A']) {
            cipherAlphabet[index++] = letter;
            used[letter - 'A'] = 1;
        }
    }

    // Insert remaining letters in order
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipherAlphabet[index++] = ch;
        }
    }
    cipherAlphabet[26] = '\0'; // Null terminate
}

// Function to encrypt using the monoalphabetic cipher
void monoEncrypt(char text[], char cipherAlphabet[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = toupper(text[i]);
            text[i] = cipherAlphabet[letter - 'A'];
        }
    }
}

// Function to decrypt using the monoalphabetic cipher
void monoDecrypt(char text[], char cipherAlphabet[]) {
    char plainAlphabet[26];
    for (int i = 0; i < 26; i++)
        plainAlphabet[cipherAlphabet[i] - 'A'] = 'A' + i;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char letter = toupper(text[i]);
            text[i] = plainAlphabet[letter - 'A'];
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char cipherAlphabet[27];
    generateCipherAlphabet(keyword, cipherAlphabet);

    char text[] = "HELLO WORLD";
    printf("Original: %s\n", text);

    monoEncrypt(text, cipherAlphabet);
    printf("Encrypted: %s\n", text);

    monoDecrypt(text, cipherAlphabet);
    printf("Decrypted: %s\n", text);

    return 0;
}

