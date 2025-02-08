#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char plaintext[], char key[]) {
	int i;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            if (islower(plaintext[i])) {
                plaintext[i] = key[plaintext[i] - 'a'];
            } else {
                plaintext[i] = toupper(key[plaintext[i] - 'A']);
            }
        }
    }
}

void decrypt(char ciphertext[], char key[]) {
    char reverse_key[26];
    int i;
    for (i = 0; i < 26; i++) {
        reverse_key[key[i] - 'a'] = 'a' + i;
    }
    for (i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            if (islower(ciphertext[i])) {
                ciphertext[i] = reverse_key[ciphertext[i] - 'a'];
            } else {
                ciphertext[i] = toupper(reverse_key[ciphertext[i] - 'A']);
            }
        }
    }
}

int main() {
    char key[27], text[100];
    printf("Enter the 26-letter key: ");
    scanf("%s", key);
    printf("Enter the text: ");
    scanf(" %[^\n]s", text);
    encrypt(text, key);
    printf("Encrypted text: %s\n", text);
    decrypt(text, key);
    printf("Decrypted text: %s\n", text);
    return 0;
}

