#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26

// Key matrix
int key[2][2] = {
    {9, 4},
    {5, 7}
};

// Function to find modular inverse
int modInverse(int a, int m) {
    for (int i = 1; i < m; i++)
        if ((a * i) % m == 1)
            return i;
    return -1;
}

// Function to find inverse matrix for decryption
void inverseKeyMatrix(int invKey[2][2]) {
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    det = (det % MOD + MOD) % MOD;  // Ensure positive mod
    int detInv = modInverse(det, MOD);

    if (detInv == -1) {
        printf("Key matrix is not invertible!\n");
        return;
    }

    // Compute inverse key matrix
    invKey[0][0] = (key[1][1] * detInv) % MOD;
    invKey[0][1] = (-key[0][1] * detInv + MOD) % MOD;
    invKey[1][0] = (-key[1][0] * detInv + MOD) % MOD;
    invKey[1][1] = (key[0][0] * detInv) % MOD;
}

// Function to perform Hill cipher encryption
void hillEncrypt(char text[]) {
    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        int p1 = text[i] - 'A', p2 = text[i + 1] - 'A';
        int c1 = (key[0][0] * p1 + key[0][1] * p2) % MOD;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % MOD;
        text[i] = c1 + 'A';
        text[i + 1] = c2 + 'A';
    }
}

// Function to perform Hill cipher decryption
void hillDecrypt(char text[]) {
    int invKey[2][2];
    inverseKeyMatrix(invKey);
    int len = strlen(text);

    for (int i = 0; i < len; i += 2) {
        int c1 = text[i] - 'A', c2 = text[i + 1] - 'A';
        int p1 = (invKey[0][0] * c1 + invKey[0][1] * c2) % MOD;
        int p2 = (invKey[1][0] * c1 + invKey[1][1] * c2) % MOD;
        text[i] = (p1 + MOD) % MOD + 'A';
        text[i + 1] = (p2 + MOD) % MOD + 'A';
    }
}

int main() {
    char text[] = "MEETMEATTHEUSUALPLACEATTENRATHERTHANEIGHTOCLOCK";

    hillEncrypt(text);
    printf("Encrypted Text: %s\n", text);

    hillDecrypt(text);
    printf("Decrypted Text: %s\n", text);

    return 0;
}

