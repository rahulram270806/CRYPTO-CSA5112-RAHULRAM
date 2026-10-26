
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];
char key[] = "PLAYFAIR";

void generateMatrix()
{
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i] != '\0'; i++)
    {
        ch = toupper((unsigned char)key[i]);

        if (ch == 'J')
            ch = 'I';

        if (ch >= 'A' && ch <= 'Z' &&
            !used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            k++;
        }
    }
}

void findPosition(char ch, int *row, int *col)
{
    int i, j;

    if (ch == 'J')
        ch = 'I';

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 5; j++)
        {
            if (matrix[i][j] == ch)
            {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

int main()
{
    char cipher[] =
        "KXJEYUREBEZWEHEWRYTUHEYFS"
        "KREHEGOYFIWTTTUOLKSYCAJPO"
        "BOTEIZONTXBYBNTGONE YCUZWR"
        "GDSONSXBOUYWRHEBAAHYUSEDQ";

    int i, r1, c1, r2, c2;
    int len;

    char clean[200];
    char plain[200];

    int n = 0;

    for (i = 0; cipher[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)cipher[i]))
            clean[n++] = toupper((unsigned char)cipher[i]);
    }
    clean[n] = '\0';
    len = n;

    generateMatrix();

    printf("Playfair Key Matrix:\n");
    for (i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
            printf("%c ", matrix[i][j]);
        printf("\n");
    }

    if (len % 2 != 0)
    {
        printf("Invalid ciphertext length.\n");
        return 1;
    }

    for (i = 0; i < len; i += 2)
    {
        findPosition(clean[i], &r1, &c1);
        findPosition(clean[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            plain[i] = matrix[r1][(c1 + 4) % 5];
            plain[i + 1] = matrix[r2][(c2 + 4) % 5];
        }
        else if (c1 == c2)
        {
            plain[i] = matrix[(r1 + 4) % 5][c1];
            plain[i + 1] = matrix[(r2 + 4) % 5][c2];
        }
        else
        {
            plain[i] = matrix[r1][c2];
            plain[i + 1] = matrix[r2][c1];
        }
    }

    plain[len] = '\0';

    printf("\nCiphertext:\n%s\n", clean);
    printf("\nDecrypted text:\n%s\n", plain);

    return 0;
}
