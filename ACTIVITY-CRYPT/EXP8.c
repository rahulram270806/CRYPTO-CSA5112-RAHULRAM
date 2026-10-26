
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char plain[] = "abcdefghijklmnopqrstuvwxyz";
    char cipher[] = "CIPHERABDFGJKLMNOQSTUVWXYZ";
    char text[200], encrypted[200], decrypted[200];
    int i, j;

    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);

    // Encryption
    for (i = 0; text[i] != '\0'; i++)
    {
        char ch = tolower((unsigned char)text[i]);

        if (ch >= 'a' && ch <= 'z')
        {
            for (j = 0; j < 26; j++)
            {
                if (ch == plain[j])
                {
                    encrypted[i] = cipher[j];
                    break;
                }
            }
        }
        else
        {
            encrypted[i] = text[i];
        }
    }
    encrypted[i] = '\0';

    // Decryption
    for (i = 0; encrypted[i] != '\0'; i++)
    {
        char ch = encrypted[i];

        if (ch >= 'A' && ch <= 'Z')
        {
            for (j = 0; j < 26; j++)
            {
                if (ch == cipher[j])
                {
                    decrypted[i] = plain[j];
                    break;
                }
            }
        }
        else
        {
            decrypted[i] = ch;
        }
    }
    decrypted[i] = '\0';

    printf("Encrypted text: %s", encrypted);
    printf("Decrypted text: %s", decrypted);

    return 0;
}
