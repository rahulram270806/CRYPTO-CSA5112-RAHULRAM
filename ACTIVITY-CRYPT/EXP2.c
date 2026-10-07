#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char plaintext[1000];
    char key[27];

    printf("Enter substitution key (26 unique letters): ");
    scanf("%26s", key);

    if (strlen(key) != 26) {
        printf("Key must contain exactly 26 letters.\n");
        return 1;
    }

    // Check that all key characters are letters and unique
    int used[26] = {0};

    for (int i = 0; i < 26; i++) {
        if (!isalpha(key[i])) {
            printf("Key must contain only letters.\n");
            return 1;
        }

        key[i] = toupper(key[i]);

        if (used[key[i] - 'A']) {
            printf("Key must contain 26 unique letters.\n");
            return 1;
        }

        used[key[i] - 'A'] = 1;
    }

    getchar(); // consume newline

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isupper(plaintext[i])) {
            plaintext[i] = key[plaintext[i] - 'A'];
        }
        else if (islower(plaintext[i])) {
            plaintext[i] = tolower(key[plaintext[i] - 'a']);
        }
    }

    printf("Ciphertext: %s", plaintext);

    return 0;
}