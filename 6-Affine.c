#include <stdio.h>

// Function to calculate modular inverse of a under mod 26
int modInverse(int a) {
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1;
}

// Affine decryption function
void affineDecrypt(char cipher[], int a, int b) {
    int a_inv = modInverse(a);
    for (int i = 0; cipher[i] != '\0'; i++) {
        if (cipher[i] >= 'A' && cipher[i] <= 'Z') {
            cipher[i] = ((a_inv * (cipher[i] - 'A' - b + 26)) % 26) + 'A';
        }
    }
}

int main() {
    char cipher[] = "BUWAAIBUKL";  // Sample ciphertext
    int a = 9, b = 1;  // Solved using frequency analysis

    affineDecrypt(cipher, a, b);
    printf("Decrypted Text: %s\n", cipher);
    return 0;
}

