
#include <stdio.h>
#include <math.h>

int main()
{
    double possibleKeys, uniqueKeys;
    double log2Possible, log2Unique;

   
    log2Possible = 0;

    for (int i = 1; i <= 25; i++)
        log2Possible += log2((double)i);

   
    log2Unique = log2Possible - 2 * log2(120.0);

    printf("Playfair Cipher Key Space\n");
    printf("-------------------------\n");

    printf("Possible keys = 25!\n");
    printf("Approximate power of 2 = 2^%.2f\n",
           log2Possible);

    printf("\nEffectively unique keys:\n");
    printf("Approximate power of 2 = 2^%.2f\n",
           log2Unique);

    return 0;
}
