#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define LANE_SIZE 64
#define WIDTH 25
#define RATE 1600 // 1024-bit block size + 576-bit capacity
#define CAPACITY 576

bool lane_has_nonzero(uint64_t lane) {
    return lane != 0;
}

int main() {
    uint64_t state[WIDTH] = {0}; // Initialize state with capacity portion zeroed

    uint64_t message_block[RATE / LANE_SIZE] = {
        0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
        0x100, 0x200, 0x400, 0x800, 0x1000, 0x2000, 0x4000, 0x8000,
        0x10000, 0x20000, 0x40000, 0x80000, 0x100000, 0x200000, 0x400000, 0x800000,
    };

    // Absorb the message block (simplified - just XOR for demonstration)
    for (int i = 0; i < RATE / LANE_SIZE; i++) {
        state[i] ^= message_block[i];
    }

    int round = 0;
    bool capacity_full = false;
    bool capacity_nonzero[WIDTH]; // Track if capacity lanes have nonzero bits
    for (int i = CAPACITY / LANE_SIZE; i < WIDTH; i++) {
        capacity_nonzero[i] = false; // Initialize to false
    }

    while (!capacity_full) {
        round++;

        // Simulate a round of SHA-3 (simplified - just XOR with round number for demonstration)
        for (int i = CAPACITY / LANE_SIZE; i < WIDTH; i++) { // Only affect the capacity portion
            state[i] ^= round;
        }

        capacity_full = true;
        for (int i = CAPACITY / LANE_SIZE; i < WIDTH; i++) {
            if (!capacity_nonzero[i] && lane_has_nonzero(state[i])) { // If lane was zero and now is not.
                capacity_nonzero[i] = true; // Mark as nonzero
            }
            if (!capacity_nonzero[i]) {
                capacity_full = false; // If any capacity lane is still zero, continue
            }
        }
    }

    printf("All capacity lanes have at least one non-zero bit after %d rounds.\n", round);

    return 0;
}
