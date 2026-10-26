
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a) {
    int i;
    for (i = 1; i < 26; i++) {
        if ((a * i) % 26 == 1)
            return i;
    }
    return -1;
}

int main() {
    char cipher[1000];
    int a, b, i, inv;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    printf("\nPossible decrypted texts:\n");

    for (a = 1; a < 26; a++) {
        if (gcd(a, 26) != 1)
            continue;

        inv = modInverse(a);

        for (b = 0; b < 26; b++) {
            printf("\na = %d, b = %d: ", a, b);

            for (i = 0; cipher[i] != '\0'; i++) {
                char ch = cipher[i];

                if (isupper((unsigned char)ch)) {
                    int y = ch - 'A';
                    int x = (inv * (y - b + 26)) % 26;
                    putchar(x + 'A');
                }
                else if (islower((unsigned char)ch)) {
                    int y = ch - 'a';
                    int x = (inv * (y - b + 26)) % 26;
                    putchar(x + 'a');
                }
                else {
                    putchar(ch);
                }
            }
        }
    }

    return 0;
}
