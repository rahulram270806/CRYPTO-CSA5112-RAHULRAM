
#include <stdio.h>

int main()
{
    int P[2][2] = {{0, 1}, {1, 0}};
    int C[2][2] = {{9, 5}, {4, 7}};
    int K[2][2];
    int i, j, k;

    

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
        {
            K[i][j] = 0;

            for (k = 0; k < 2; k++)
                K[i][j] += C[i][k] * P[k][j];

            K[i][j] %= 26;
        }
    }

    printf("Recovered Hill Cipher Key:\n");

    for (i = 0; i < 2; i++)
    {
        for (j = 0; j < 2; j++)
            printf("%d ", K[i][j]);

        printf("\n");
    }

    return 0;
}
