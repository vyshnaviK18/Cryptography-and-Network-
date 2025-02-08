#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[], char ciphertext[]) {
    int i, j = 0, keyLen = strlen(key);
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                ciphertext[i] = 'a' + (plaintext[i] - 'a' + tolower(key[j % keyLen]) - 'a') % 26;
            } else {
                ciphertext[i] = 'A' + (plaintext[i] - 'A' + toupper(key[j % keyLen]) - 'A') % 26;
            }
            j++;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0';
}

void decrypt(char ciphertext[], char key[], char plaintext[]) {
    int i, j = 0, keyLen = strlen(key);
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                plaintext[i] = 'a' + (ciphertext[i] - 'a' - (tolower(key[j % keyLen]) - 'a') + 26) % 26;
            } else {
                plaintext[i] = 'A' + (ciphertext[i] - 'A' - (toupper(key[j % keyLen]) - 'A') + 26) % 26;
            }
            j++;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100];
    printf("Enter the plaintext: ");
    scanf(" %[^\n]s", plaintext);
    printf("Enter the key: ");
    scanf(" %[^\n]s", key);
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);
    decrypt(ciphertext, key, plaintext);
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}

