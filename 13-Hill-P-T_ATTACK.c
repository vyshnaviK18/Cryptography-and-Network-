#include <stdio.h>
#include <stdlib.h>

#define MOD 26

// Function to calculate modular inverse of a number under mod 26
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1; // No modular inverse exists
}

// Function to compute the inverse of a 2x2 matrix under mod 26
void inverseMatrix(int key[2][2], int invKey[2][2]) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % MOD;
    if (det < 0) det += MOD; // Ensure positive determinant

    int detInv = modInverse(det, MOD);
    if (detInv == -1) {
        printf("Inverse does not exist!\n");
        exit(1);
    }

    // Compute inverse matrix
    invKey[0][0] = (key[1][1] * detInv) % MOD;
    invKey[1][1] = (key[0][0] * detInv) % MOD;
    invKey[0][1] = (-key[0][1] * detInv + MOD) % MOD;
    invKey[1][0] = (-key[1][0] * detInv + MOD) % MOD;
}

// Function to decrypt ciphertext using known plaintext attack
void decryptHill(int plaintext[2], int ciphertext[2], int key[2][2]) {
    int invKey[2][2];
    inverseMatrix(key, invKey);

    int recoveredKey[2];
    recoveredKey[0] = (invKey[0][0] * ciphertext[0] + invKey[0][1] * ciphertext[1]) % MOD;
    recoveredKey[1] = (invKey[1][0] * ciphertext[0] + invKey[1][1] * ciphertext[1]) % MOD;

    printf("Recovered plaintext: %c%c\n", recoveredKey[0] + 'A', recoveredKey[1] + 'A');
}

int main() {
    int plaintext[2] = {7, 4};  // Example plaintext "HE" -> H=7, E=4
    int ciphertext[2] = {19, 2}; // Example ciphertext "TC" -> T=19, C=2
    int key[2][2] = { {9, 4}, {5, 7} }; // Example key matrix

    decryptHill(plaintext, ciphertext, key);
    return 0;
}

