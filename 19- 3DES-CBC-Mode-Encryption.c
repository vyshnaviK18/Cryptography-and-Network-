#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to perform 3DES CBC encryption
void encrypt_3des_cbc(const char *plaintext, const char *key, const char *iv, unsigned char *ciphertext) {
    DES_cblock key1, key2, key3, ivec;
    DES_key_schedule ks1, ks2, ks3;

    // Copy keys and IV from input
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);
    memcpy(ivec, iv, 8);

    // Set up key schedules
    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    // Encrypt using 3DES CBC
    DES_ede3_cbc_encrypt((unsigned char *)plaintext, ciphertext, strlen(plaintext) + 1, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
}

int main() {
    // Input plaintext
    char plaintext[] = "HELLO CBC MODE";

    // 3DES Key (24 bytes) and IV (8 bytes)
    char key[24] = "0123456789abcdef01234567";  // Example key
    char iv[8] = "12345678";                    // Example IV

    // Ciphertext buffer
    unsigned char ciphertext[128];

    // Perform encryption
    encrypt_3des_cbc(plaintext, key, iv, ciphertext);

    // Print encrypted output in hex format
    printf("Ciphertext: ");
    for (int i = 0; i < strlen(plaintext) + 1; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
