
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main()
{
    char cipher[1000], plain[1000];
    int top, shift, i, j, len;

    printf("Enter ciphertext: ");
    fgets(cipher, sizeof(cipher), stdin);

    printf("Enter number of top plaintexts: ");
    scanf("%d", &top);

    len = strlen(cipher);

    if (len > 0 && cipher[len - 1] == '\n')
        cipher[--len] = '\0';

    if (top < 1)
        return 0;

    if (top > 26)
        top = 26;

    printf("\nPossible plaintexts in order:\n");

    for (shift = 0; shift < top; shift++)
    {
        for (i = 0; i < len; i++)
        {
            char ch = cipher[i];

            if (isalpha((unsigned char)ch))
            {
                char base = isupper((unsigned char)ch)
                            ? 'A' : 'a';

                plain[i] = (ch - base - shift + 26) % 26
                           + base;
            }
            else
            {
                plain[i] = ch;
            }
        }

        plain[len] = '\0';

        printf("Shift %2d: %s\n", shift, plain);
    }

    return 0;
}
