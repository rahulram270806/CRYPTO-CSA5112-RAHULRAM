#include <stdio.h>
#include <ctype.h>
#include <string.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    char plaintext[1000];
    int a, b;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter value of a: ");
    scanf("%d", &a);

    printf("Enter value of b: ");
    scanf("%d", &b);

    // a must be relatively prime to 26
    if (gcd(a, 26) != 1) {
        printf("Invalid value of a!\n");
        printf("a must be relatively prime to 26.\n");
        return 1;
    }

    // Keep b between 0 and 25
    b = ((b % 26) + 26) % 26;

    for (int i = 0; plaintext[i] != '\0'; i++) {

        if (isupper(plaintext[i])) {
            int p = plaintext[i] - 'A';

            int c = (a * p + b) % 26;

            plaintext[i] = c + 'A';
        }
        else if (islower(plaintext[i])) {
            int p = plaintext[i] - 'a';

            int c = (a * p + b) % 26;

            plaintext[i] = c + 'a';
        }
    }

    printf("Ciphertext: %s", plaintext);

    return 0;
}