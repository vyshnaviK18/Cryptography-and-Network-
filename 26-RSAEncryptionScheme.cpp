#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// Extended Euclidean Algorithm
int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }
    int64_t x1, y1;
    int64_t gcd = extended_gcd(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Modular Inverse
int64_t mod_inverse(int64_t a, int64_t m) {
    int64_t x, y;
    int64_t gcd = extended_gcd(a, m, &x, &y);
    if (gcd != 1) {
        return -1; // Inverse doesn't exist
    }
    int64_t result = (x % m + m) % m; // Ensure positive result
    return result;
}

// Greatest Common Divisor
uint64_t gcd(uint64_t a, uint64_t b) {
    while (b) {
        uint64_t temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Simplified Prime Number Generation (for demonstration)
uint64_t generate_prime(uint64_t min, uint64_t max) {
    uint64_t num;
    int is_prime;
    do {
        num = (rand() % (max - min + 1)) + min;
        is_prime = 1;
        for (uint64_t i = 2; i * i <= num; i++) {
            if (num % i == 0) {
                is_prime = 0;
                break;
            }
        }
    } while (!is_prime);
    return num;
}

int main() {
    srand(time(NULL));

    uint64_t n = 3599; // Example n (remains the same)

    // Bob's old (leaked) keys
    uint64_t old_e = 31;
    uint64_t old_d = 2351;

    // Bob's new keys
    uint64_t new_p, new_q;
    uint64_t new_phi_n;
    uint64_t new_e, new_d;

    // Generate new p and q (different from the old ones)
    do {
        new_p = generate_prime(50, 100);
        new_q = generate_prime(50, 100);
    } while (new_p == new_q || new_p * new_q != n);

    // Calculate new phi(n)
    new_phi_n = (new_p - 1) * (new_q - 1);

    // Generate new e (coprime with new_phi_n)
    do {
        new_e = (rand() % (new_phi_n - 2)) + 2;
    } while (gcd(new_e, new_phi_n) != 1);

    // Calculate new d
    new_d = mod_inverse(new_e, new_phi_n);
    if (new_d == -1) {
        printf("Error: Modular inverse does not exist for new e.\n");
        return 1;
    }

    printf("Old e: %lu, d: %lu\n", old_e, old_d);
    printf("New p: %lu, q: %lu\n", new_p, new_q);
    printf("New e: %lu, d: %lu\n", new_e, new_d);

    return 0;
}
