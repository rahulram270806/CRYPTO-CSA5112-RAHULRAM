
#include <stdio.h>
#include <ctype.h>
#include <string.h>

char matrix[5][5] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};

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
    char message[] =
        "Must see you over Cadogan West. Coming at once.";
    char text[200], encrypted[200];
    int i, j, r1, c1, r2, c2, n = 0;

    // Remove spaces and punctuation
    for (i = 0; message[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)message[i]))
        {
            char ch = toupper((unsigned char)message[i]);

            if (ch == 'J')
                ch = 'I';

            text[n++] = ch;
        }
    }
    text[n] = '\0';

    // Prepare letter pairs
    char pairs[200];
    int k = 0;

    for (i = 0; i < n;)
    {
        pairs[k++] = text[i++];

        if (i < n)
        {
            if (text[i] == pairs[k - 1])
                pairs[k++] = 'X';
            else
                pairs[k++] = text[i++];
        }
        else
        {
            pairs[k++] = 'X';
        }
    }
    pairs[k] = '\0';

    // Encrypt each pair
    for (i = 0; i < k; i += 2)
    {
        findPosition(pairs[i], &r1, &c1);
        findPosition(pairs[i + 1], &r2, &c2);

        if (r1 == r2)
        {
            encrypted[i] = matrix[r1][(c1 + 1) % 5];
            encrypted[i + 1] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2)
        {
            encrypted[i] = matrix[(r1 + 1) % 5][c1];
            encrypted[i + 1] = matrix[(r2 + 1) % 5][c2];
        }
        else
        {
            encrypted[i] = matrix[r1][c2];
            encrypted[i + 1] = matrix[r2][c1];
        }
    }
    encrypted[k] = '\0';

    printf("Plaintext: %s\n", message);
    printf("Prepared text: %s\n", pairs);
    printf("Encrypted text: ");

    for (i = 0; i < k; i++)
    {
        printf("%c", encrypted[i]);
        if (i % 2 == 1)
            printf(" ");
    }

    printf("\n");

    return 0;
}
