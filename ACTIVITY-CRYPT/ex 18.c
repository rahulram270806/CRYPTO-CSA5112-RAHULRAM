
#include <stdio.h>
#include <stdint.h>

int PC1[56] = {
    57,49,41,33,25,17,9,
    1,58,50,42,34,26,18,
    10,2,59,51,43,35,27,
    19,11,3,60,52,44,36,
    63,55,47,39,31,23,15,
    7,62,54,46,38,30,22,
    14,6,61,53,45,37,29,
    21,13,5,28,20,12,4
};

int PC2[48] = {
    14,17,11,24,1,5,
    3,28,15,6,21,10,
    23,19,12,4,26,8,
    16,7,27,20,13,2,
    41,52,31,37,47,55,
    30,40,51,45,33,48,
    44,49,39,56,34,53,
    46,42,50,36,29,32
};

int shifts[16] = {
    1,1,2,2,2,2,2,2,
    1,2,2,2,2,2,2,1
};

/* Permutation function */
uint64_t permute(uint64_t input, int table[],
                 int outputBits, int inputBits)
{
    uint64_t output = 0;

    for (int i = 0; i < outputBits; i++) {
        output <<= 1;
        output |= (input >> (inputBits - table[i])) & 1;
    }

    return output;
}

/* Circular left shift of 28-bit value */
uint32_t leftShift(uint32_t value, int count)
{
    return ((value << count) |
            (value >> (28 - count))) & 0x0FFFFFFF;
}

/* Generate DES subkeys */
void generateKeys(uint64_t key)
{
    uint64_t permutedKey;
    uint32_t C, D;
    uint64_t subkey;

    permutedKey = permute(key, PC1, 56, 64);

    C = (permutedKey >> 28) & 0x0FFFFFFF;
    D = permutedKey & 0x0FFFFFFF;

    printf("\nInitial 28-bit subsets:\n");
    printf("C0 = %07X\n", C);
    printf("D0 = %07X\n", D);

    printf("\nDES GENERATED SUBKEYS:\n");

    for (int round = 0; round < 16; round++) {

        C = leftShift(C, shifts[round]);
        D = leftShift(D, shifts[round]);

        /*
          PC-2 selects 24 bits from C
          and 24 bits from D.
        */
        uint64_t combined = ((uint64_t)C << 28) | D;

        subkey = permute(combined, PC2, 48, 56);

        printf("K%-2d = %012llX\n",
               round + 1,
               (unsigned long long)subkey);
    }
}

int main()
{
    uint64_t key;

    printf("DES KEY GENERATION PROGRAM\n");

    printf("\nEnter 64-bit hexadecimal key: ");

    if (scanf("%16llx", (unsigned long long *)&key) != 1) {
        printf("Invalid key!\n");
        return 1;
    }

    generateKeys(key);

    return 0;
}
