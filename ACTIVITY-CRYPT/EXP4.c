#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[1000];
    char key[1000];
    char ciphertext[1000];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline from key
    key[strcspn(key, "\n")] = '\0';

    int keyLen = strlen(key);

    if (keyLen == 0) {
        printf("Key cannot be empty.\n");
        return 1;
    }

    int j = 0;

    for (int i = 0; plaintext[i] != '\0'; i++) {

        if (isalpha(plaintext[i])) {
            char p = toupper(plaintext[i]);
            char k = toupper(key[j % keyLen]);

            if (!isalpha(k)) {
                printf("Key must contain only letters.\n");
                return 1;
            }

            ciphertext[i] =
                (p - 'A' + (k - 'A')) % 26 + 'A';

            j++;
        }
        else {
            // Keep spaces and punctuation unchanged
            ciphertext[i] = plaintext[i];
        }
    }

    ciphertext[strlen(plaintext)] = '\0';

    printf("Ciphertext: %s", ciphertext);

    return 0;
}