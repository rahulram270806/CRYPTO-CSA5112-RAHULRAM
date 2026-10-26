
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char text[200], cipher[200], decrypted[200];
    int K[2][2] = {{9, 4}, {5, 7}};
    int D[2][2] = {{5, 12}, {15, 25}};
    int i, n = 0, a, b, x, y;

    printf("Enter plaintext: ");
    fgets(text, sizeof(text), stdin);

    for (i = 0; text[i] != '\0'; i++)
        if (isalpha((unsigned char)text[i]))
            text[n++] = toupper((unsigned char)text[i]);

    text[n] = '\0';

    if (n % 2 != 0)
        text[n++] = 'X';

    text[n] = '\0';

    for (i = 0; i < n; i += 2)
    {
        a = text[i] - 'A';
        b = text[i + 1] - 'A';

        x = (K[0][0] * a + K[0][1] * b) % 26;
        y = (K[1][0] * a + K[1][1] * b) % 26;

        cipher[i] = x + 'A';
        cipher[i + 1] = y + 'A';
    }
    cipher[n] = '\0';

    for (i = 0; i < n; i += 2)
    {
        a = cipher[i] - 'A';
        b = cipher[i + 1] - 'A';

        x = (D[0][0] * a + D[0][1] * b) % 26;
        y = (D[1][0] * a + D[1][1] * b) % 26;

        decrypted[i] = x + 'A';
        decrypted[i + 1] = y + 'A';
    }
    decrypted[n] = '\0';

    printf("Ciphertext: %s\n", cipher);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}
