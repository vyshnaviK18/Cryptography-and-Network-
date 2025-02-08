#include <stdio.h>
#include <math.h>

// Function to compute log2(n!) using Stirling's approximation
double log2_factorial(int n) {
    if (n == 0 || n == 1) return 0;
    return n * log2(n) - (n / log(2));  // Using log2(n!) ˜ n log2(n) - n
}

int main() {
    int n = 25;  // Number of unique letters in Playfair (A-Z, but I/J combined)
    int row_col_permutations = 5;  // Each row and column can be rearranged

    // Compute log2(25!)
    double log2_25_factorial = log2_factorial(n);

    // Compute log2(5! * 5!)
    double log2_5_factorial = 2 * log2_factorial(row_col_permutations);

    // Total Playfair keys (ignoring identical encryption results)
    double total_keys = log2_25_factorial;

    // Effectively unique keys (accounting for row/column swaps)
    double unique_keys = log2_25_factorial - log2_5_factorial;

    // Print results in power-of-2 format
    printf("Total possible Playfair cipher keys (ignoring redundancy): 2^%.1f\n", total_keys);
    printf("Effectively unique Playfair cipher keys: 2^%.1f\n", unique_keys);

    return 0;
}

