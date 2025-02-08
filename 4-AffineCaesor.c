#include <stdio.h>

int modInverse(int a) {
    for (int i = 1; i < 26; i++)
        if ((a * i) % 26 == 1)
            return i;
    return -1;
}

void affineCipher(char text[], int a, int b) {
    for (int i = 0; text[i] != '\0'; i++)
        if (isalpha(text[i]))
            text[i] = ((a * (text[i] - 'A') + b) % 26) + 'A';
}

void affineDecipher(char text[], int a, int b) {
    int a_inv = modInverse(a);
    for (int i = 0; text[i] != '\0'; i++)
        if (isalpha(text[i]))
            text[i] = ((a_inv * ((text[i] - 'A' - b + 26)) % 26) + 26) % 26 + 'A';
}

int main() {
    char text[] = "HELLO";
    int a = 5, b = 8;
    affineCipher(text, a, b);
    printf("Encrypted: %s\n", text);
    affineDecipher(text, a, b);
    printf("Decrypted: %s\n", text);
    return 0;
}

