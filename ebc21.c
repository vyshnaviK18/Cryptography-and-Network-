#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 16

// Placeholder encryption function (REPLACE with a real crypto library like AES)
void encrypt_block(unsigned char *plaintext, unsigned char *ciphertext, unsigned char *key) {
    int i; // Declare i outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        ciphertext[i] = plaintext[i] ^ key[i]; // Simple XOR for demonstration
    }
}

// Placeholder decryption function (REPLACE with a real crypto library like AES)
void decrypt_block(unsigned char *ciphertext, unsigned char *plaintext, unsigned char *key) {
    int i; // Declare i outside the loop
    for (i = 0; i < BLOCK_SIZE; i++) {
        plaintext[i] = ciphertext[i] ^ key[i]; // Simple XOR for demonstration
    }
}

// Padding function (PKCS#7 style)
void pad_data(unsigned char *data, int data_len, int block_size) {
    int padding_len = block_size - (data_len % block_size);
    if (padding_len == block_size) padding_len = 0; //Pad even if full
    unsigned char padding_value = padding_len; // Value of padding byte is the padding length
    int i; // Declare i outside the loop
    for (i = 0; i < padding_len; i++) {
        data[data_len + i] = padding_value;
    }
}

// ECB Mode
void ecb_mode(unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len, unsigned char *key) {
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE; //Number of blocks after padding
    int i; // Declare i outside the loop
    for (i = 0; i < num_blocks; i++) {
        encrypt_block(plaintext + i * BLOCK_SIZE, ciphertext + i * BLOCK_SIZE, key);
    }
}

// CBC Mode
void cbc_mode(unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE; //Number of blocks after padding
    unsigned char previous_ciphertext[BLOCK_SIZE];
    memcpy(previous_ciphertext, iv, BLOCK_SIZE);

    int i, j; // Declare i and j outside the loops
    for (i = 0; i < num_blocks; i++) {
        unsigned char block[BLOCK_SIZE];
        for(j = 0; j<BLOCK_SIZE; j++){
            block[j] = plaintext[i * BLOCK_SIZE + j] ^ previous_ciphertext[j];
        }
        encrypt_block(block, ciphertext + i * BLOCK_SIZE, key);
        memcpy(previous_ciphertext, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

// CFB Mode
void cfb_mode(unsigned char *plaintext, unsigned char *ciphertext, int plaintext_len, unsigned char *key, unsigned char *iv) {
    int num_blocks = (plaintext_len + BLOCK_SIZE - 1) / BLOCK_SIZE; //Number of blocks after padding
    unsigned char shift_register[BLOCK_SIZE];
    memcpy(shift_register, iv, BLOCK_SIZE);

    int i, j; // Declare i and j outside the loops
    for (i = 0; i < num_blocks; i++) {
        unsigned char encrypted_shift_register[BLOCK_SIZE];
        encrypt_block(shift_register, encrypted_shift_register, key);

        for (j = 0; j < BLOCK_SIZE; j++) {
            ciphertext[i * BLOCK_SIZE + j] = plaintext[i * BLOCK_SIZE + j] ^ encrypted_shift_register[j];
        }

        memcpy(shift_register, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void print_hex(unsigned char *data, int len) {
    int i; // Declare i outside the loop
    for (i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    unsigned char key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    unsigned char iv[BLOCK_SIZE] = {0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20};

    unsigned char plaintext[48] = "This is a test message. This is a test message."; //32-byte message
    int plaintext_len = strlen((char*)plaintext);

    unsigned char ciphertext_ecb[48], decrypted_ecb[48];
    unsigned char ciphertext_cbc[48], decrypted_cbc[48];
    unsigned char ciphertext_cfb[48], decrypted_cfb[48];

    pad_data(plaintext, plaintext_len, BLOCK_SIZE); //Pad the plaintext

    printf("Plaintext: ");
    print_hex(plaintext, strlen((char*)plaintext));

    ecb_mode(plaintext, ciphertext_ecb, strlen((char*)plaintext), key);
    printf("ECB Ciphertext: ");
    print_hex(ciphertext_ecb, strlen((char*)plaintext));

    cbc_mode(plaintext, ciphertext_cbc, strlen((char*)plaintext), key, iv);
    printf("CBC Ciphertext: ");
    print_hex(ciphertext_cbc, strlen((char*)plaintext));

    cfb_mode(plaintext, ciphertext_cfb, strlen((char*)plaintext), key, iv);
    printf("CFB Ciphertext: ");
    print_hex(ciphertext_cfb, strlen((char*)plaintext));


    // ... (Add decryption and print decrypted text if needed)

    return 0;
}
