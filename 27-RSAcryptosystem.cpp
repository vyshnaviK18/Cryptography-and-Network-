#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Simplified RSA encryption (for demonstration - use a proper library for real RSA)
uint64_t rsa_encrypt(uint64_t plaintext, uint64_t e, uint64_t n) {
    uint64_t ciphertext = 1;
    while (e > 0) {
        if (e & 1) {
            ciphertext = (ciphertext * plaintext) % n;
        }
        plaintext = (plaintext * plaintext) % n;
        e >>= 1;
    }
    return ciphertext;
}

int main() {
    uint64_t n = 3599; // Example large n (replace with a truly large n)
    uint64_t e = 31;    // Example large e

    char message[] = "HELLO";
    int message_len = strlen(message);
    uint64_t ciphertext[message_len];

    // Encrypt each character
    for (int i = 0; i < message_len; i++) {
        uint64_t plaintext = message[i] - 'A';
        ciphertext[i] = rsa_encrypt(plaintext, e, n);
        printf("Plaintext: %c (%lu), Ciphertext: %lu\n", message[i], plaintext, ciphertext[i]);
    }

    // ... (Attacker's attempt to break the code - see explanation below)

    return 0;
}
