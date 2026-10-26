
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char plain[] = "send more money";
    char target[] = "cash not needed";
    int key[] = {9, 0, 1, 7, 23, 15, 21,
                 14, 11, 11, 2, 8, 9};
    char cipher[100], newKey[100];
    int i, j = 0, n = 0;

    // Encrypt "send more money"
    for (i = 0; plain[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)plain[i]))
        {
            int p = tolower((unsigned char)plain[i]) - 'a';
            cipher[n++] = (p + key[j++]) % 26 + 'A';
        }
    }
    cipher[n] = '\0';

    printf("Ciphertext: %s\n", cipher);

    // Find a key that makes the same ciphertext
    // decrypt to "cash not needed"
    j = 0;
    n = 0;

    for (i = 0; target[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)target[i]))
        {
            int p = tolower((unsigned char)target[i]) - 'a';
            int c = cipher[n] - 'A';

            newKey[j++] = (c - p + 26) % 26;
            n++;
        }
    }

    printf("New key for target plaintext: ");
    for (i = 0; i < j; i++)
        printf("%d ", newKey[i]);

    printf("\n");
    return 0;
}
