#include <stdio.h>
#include <ctype.h>

void caesarCipher(char text[], int k) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - base + k) % 26 + base;
        }
    }
}

int main() {
    char text[] = "HELLO";
    int key = 3;
    caesarCipher(text, key);
    printf("Encrypted: %s\n", text);
    caesarCipher(text, 26 - key);
    printf("Decrypted: %s\n", text);
    return 0;
}

