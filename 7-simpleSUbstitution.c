#include <stdio.h>
#include <string.h>

// Sample mapping (must be derived by analyzing frequency)
char cipherToPlain[256];

// Function to decrypt the text
void decrypt(char text[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (cipherToPlain[(unsigned char)text[i]])
            text[i] = cipherToPlain[(unsigned char)text[i]];
    }
}

int main() {
    char cipherText[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83";
    
    // Manually derived mappings (based on frequency analysis)
    cipherToPlain['‡'] = 'E';
    cipherToPlain['8'] = 'T';
    cipherToPlain[';'] = 'H';
    cipherToPlain['4'] = 'O';
    cipherToPlain['*'] = 'A';
    cipherToPlain['5'] = 'N';
    cipherToPlain['6'] = 'D';
    cipherToPlain[')'] = 'I';
    cipherToPlain['3'] = 'R';
    cipherToPlain['0'] = 'S';

    decrypt(cipherText);
    printf("Decrypted Text: %s\n", cipherText);

    return 0;
}

