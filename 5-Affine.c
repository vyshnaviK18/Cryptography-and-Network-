#include <stdio.h>

// Function to calculate modular inverse of a under mod 26
int modInverse(int a) {
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1;  // No modular inverse found
}

// Encryption function: C = (aP + b) mod 26
void affineEncrypt(char text[], int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')  // Uppercase only
            text[i] = ((a * (text[i] - 'A') + b) % 26) + 'A';
    }
}

// Decryption function: P = a^-1 (C - b) mod 26
void affineDecrypt(char text[], int a, int b) {
    int a_inv = modInverse(a);
    if (a_inv == -1) {
        printf("Decryption not possible (invalid 'a' value).\n");
        return;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'A' && text[i] <= 'Z')
            text[i] = ((a_inv * (text[i] - 'A' - b + 26)) % 26) + 'A';
    }
}

int main() {
    char text[] = "HELLO";
    int a = 5, b = 8;  // Choose values of a and b

    affineEncrypt(text, a, b);
    printf("Encrypted: %s\n", text);

    affineDecrypt(text, a, b);
    printf("Decrypted: %s\n", text);

    return 0;
}

