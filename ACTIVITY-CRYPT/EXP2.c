
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char plaintext[100], ciphertext[100];
    char key[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
    int i;

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (i = 0; plaintext[i] != '\0'; i++) {
        char ch = plaintext[i];

        if (isupper(ch)) {
            ciphertext[i] = key[ch - 'A'];
        }
        else if (islower(ch)) {
            ciphertext[i] = tolower(key[ch - 'a']);
        }
        else {
            ciphertext[i] = ch;
        }
    }

    ciphertext[i] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}
