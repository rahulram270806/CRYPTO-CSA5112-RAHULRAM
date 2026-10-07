#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char text[1000];
    int k;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    printf("Enter key k (1-25): ");
    scanf("%d", &k);

    if (k < 1 || k > 25) {
        printf("Invalid key! k must be between 1 and 25.\n");
        return 1;
    }

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' + k) % 26 + 'A';
        } 
        else if (islower(text[i])) {
            text[i] = (text[i] - 'a' + k) % 26 + 'a';
        }
    }

    printf("Ciphertext: %s", text);

    return 0;
}