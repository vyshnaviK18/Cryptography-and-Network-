#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

uint64_t mod_exp(uint64_t a, uint64_t x, uint64_t q) {
    uint64_t result = 1;
    a = a % q; // Handle large a
    while (x > 0) {
        if (x & 1) {
            result = (result * a) % q;
        }
        a = (a * a) % q;
        x >>= 1;
    }
    return result;
}

int main() {
    uint64_t q = 23; // Public prime number
    uint64_t a = 5;  // Public generator

    // Alice's secret
    uint64_t alice_x = 6;
    uint64_t alice_A = mod_exp(a, alice_x, q); // Alice sends this to Bob

    // Bob's secret
    uint64_t bob_x = 15;
    uint64_t bob_B = mod_exp(a, bob_x, q); // Bob sends this to Alice

    // Alice calculates shared key
    uint64_t alice_shared_key = mod_exp(bob_B, alice_x, q);

    // Bob calculates shared key
    uint64_t bob_shared_key = mod_exp(alice_A, bob_x, q);

    printf("Alice's A: %lu\n", alice_A);
    printf("Bob's B: %lu\n", bob_B);
    printf("Alice's shared key: %lu\n", alice_shared_key);
    printf("Bob's shared key: %lu\n", bob_shared_key);

    return 0;
}
