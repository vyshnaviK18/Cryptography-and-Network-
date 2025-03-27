#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16 

void encrypt_block(uint8_t *in, uint8_t *out, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        out[i] = in[i] ^ key[i]; // XOR for demonstration
    }
}

// CBC MAC Calculation
void cbc_mac(uint8_t *message, size_t message_len, uint8_t *key, uint8_t *mac) {
    uint8_t current_block[BLOCK_SIZE];
    uint8_t previous_mac[BLOCK_SIZE];
    memset(previous_mac, 0, BLOCK_SIZE); // Initial IV (all zeros)

    for (size_t i = 0; i < message_len; i += BLOCK_SIZE) {
        size_t block_len = (i + BLOCK_SIZE <= message_len) ? BLOCK_SIZE : message_len - i;
        memcpy(current_block, message + i, block_len);

        // Pad with zeros if the last block is shorter
        if (block_len < BLOCK_SIZE) {
            memset(current_block + block_len, 0, BLOCK_SIZE - block_len);
        }

        // XOR with previous MAC
        for (int j = 0; j < BLOCK_SIZE; j++) {
            current_block[j] ^= previous_mac[j];
        }

        // Encrypt the block
        encrypt_block(current_block, mac, key);

        // Update previous MAC
        memcpy(previous_mac, mac, BLOCK_SIZE);
    }
}

void print_hex(uint8_t *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10};
    uint8_t message_x[BLOCK_SIZE] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff, 0x00};
    uint8_t mac_t[BLOCK_SIZE];

    // Calculate MAC for X
    cbc_mac(message_x, BLOCK_SIZE, key, mac_t);
    printf("MAC(K, X): ");
    print_hex(mac_t, BLOCK_SIZE);

    // Construct X || (X XOR T)
    uint8_t message_xt[2 * BLOCK_SIZE];
    memcpy(message_xt, message_x, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_SIZE; i++) {
        message_xt[BLOCK_SIZE + i] = message_x[i] ^ mac_t[i];
    }

    // Calculate MAC for X || (X XOR T)
    uint8_t mac_xt[BLOCK_SIZE];
    cbc_mac(message_xt, 2 * BLOCK_SIZE, key, mac_xt);
    printf("MAC(K, X || (X XOR T)): ");
    print_hex(mac_xt, BLOCK_SIZE);

    // Demonstrate the vulnerability: MAC(K, X || (X XOR T)) == MAC(K,X)
    printf("MAC(K, X) == MAC(K, X || (X XOR T)): %s\n", memcmp(mac_t, mac_xt, BLOCK_SIZE) == 0 ? "True" : "False");

    return 0;
}
