#include <stdio.h>
#include <stdint.h>
#include <string.h>

// S-DES Key Generation (same as before)
void generate_subkeys(uint16_t key, uint8_t *subkey1, uint8_t *subkey2);

// S-DES Feistel Function (same as before)
uint8_t sdes_f(uint8_t right, uint8_t subkey);

// S-DES Encryption/Decryption (same as before)
uint16_t sdes_encrypt(uint16_t plaintext, uint16_t key);
uint16_t sdes_decrypt(uint16_t ciphertext, uint16_t key);

// CBC Mode Encryption
void cbc_encrypt(uint16_t *plaintext, uint16_t *ciphertext, size_t length, uint16_t key, uint16_t iv) {
    uint16_t previous_ciphertext = iv;
    for (size_t i = 0; i < length; i++) {
        uint16_t block = plaintext[i] ^ previous_ciphertext;
        ciphertext[i] = sdes_encrypt(block, key);
        previous_ciphertext = ciphertext[i];
    }
}

// CBC Mode Decryption
void cbc_decrypt(uint16_t *ciphertext, uint16_t *plaintext, size_t length, uint16_t key, uint16_t iv) {
    uint16_t previous_ciphertext = iv;
    for (size_t i = 0; i < length; i++) {
        uint16_t decrypted_block = sdes_decrypt(ciphertext[i], key);
        plaintext[i] = decrypted_block ^ previous_ciphertext;
        previous_ciphertext = ciphertext[i];
    }
}

// Print binary representation (same as before)
void print_binary(const char *label, uint16_t num);

int main() {
    uint16_t plaintext[] = {0x0001, 0x0003}; // Binary: 0000 0001 0010 0011
    size_t length = sizeof(plaintext) / sizeof(plaintext[0]);
    uint16_t ciphertext[length];
    uint16_t decrypted_text[length];

    uint16_t key = 0x07FD; // Binary: 01111 11101
    uint16_t iv = 0xAAAA;  // Binary: 1010 1010 1010 1010

    // Encrypt
    cbc_encrypt(plaintext, ciphertext, length, key, iv);

    // Decrypt
    cbc_decrypt(ciphertext, decrypted_text, length, key, iv);

    // Print results
    for (size_t i = 0; i < length; i++) {
        print_binary("Plaintext", plaintext[i]);
        print_binary("Ciphertext", ciphertext[i]);
        print_binary("Decrypted", decrypted_text[i]);
        printf("\n");
    }

    return 0;
}

// S-DES Key Scheduling
void generate_subkeys(uint16_t key, uint8_t *subkey1, uint8_t *subkey2) {
    *subkey1 = (key >> 5) & 0x1F; // First 5 bits
    *subkey2 = key & 0x1F;        // Last 5 bits
}

// S-DES Feistel function (simple XOR with key)
uint8_t sdes_f(uint8_t right, uint8_t subkey) {
    return right ^ subkey;  // Simple XOR for demonstration
}

// S-DES Encryption (simplified for CBC mode)
uint16_t sdes_encrypt(uint16_t plaintext, uint16_t key) {
    uint8_t left = (plaintext >> 8) & 0xFF;
    uint8_t right = plaintext & 0xFF;

    uint8_t subkey1, subkey2;
    generate_subkeys(key, &subkey1, &subkey2);

    uint8_t round1 = sdes_f(right, subkey1);
    uint8_t round2 = sdes_f(round1, subkey2);

    return (round2 << 8) | round1;
}

// S-DES Decryption (reverse process)
uint16_t sdes_decrypt(uint16_t ciphertext, uint16_t key) {
    uint8_t left = (ciphertext >> 8) & 0xFF;
    uint8_t right = ciphertext & 0xFF;

    uint8_t subkey1, subkey2;
    generate_subkeys(key, &subkey1, &subkey2);

    uint8_t round1 = sdes_f(right, subkey2);
    uint8_t round2 = sdes_f(round1, subkey1);

    return (round2 << 8) | round1;
}

// Print binary representation of 16-bit number
void print_binary(const char *label, uint16_t num) {
    printf("%s: ", label);
    for (int i = 15; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
    printf("\n");
}
