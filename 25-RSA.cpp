#include <stdio.h>
#include <stdint.h>

// Title: Greatest Common Divisor (GCD)
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Title: RSA Encryption (Simplified)
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

// Title: Main RSA Attack with Common Factor
int main() {
    uint64_t n = 3599; // Example n = p*q (59 * 61)
    uint64_t e = 31;    // Example public key

    uint64_t plaintext_blocks[] = {123, 456, 789, 1771}; // Example plaintext blocks
    size_t num_blocks = sizeof(plaintext_blocks) / sizeof(plaintext_blocks[0]);
    uint64_t ciphertext_blocks[num_blocks];

    // Encrypt the blocks
    for (size_t i = 0; i < num_blocks; i++) {
        ciphertext_blocks[i] = rsa_encrypt(plaintext_blocks[i], e, n);
        printf("Plaintext %lu: %lu, Ciphertext: %lu\n", plaintext_blocks[i], ciphertext_blocks[i]);
    }

    // Simulate someone telling us a plaintext block has a common factor with n
    uint64_t known_plaintext_block = 1771; //Let's assume this block has a common factor with n.
    uint64_t common_factor = gcd(known_plaintext_block, n);

    if (common_factor != 1 && common_factor != n) {
        printf("Common factor found: %lu\n", common_factor);
        uint64_t q = n / common_factor; //We now know p and q
        uint64_t phi_n = (common_factor - 1) * (q - 1); // Euler's totient
        printf("p = %lu, q = %lu\n", common_factor, q);
        //Now find d using mod inverse.
        //Place code for finding d here if needed.
    } else {
        printf("No common factor found.\n");
    }

    return 0;
}
