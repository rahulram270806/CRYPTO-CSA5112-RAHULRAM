
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

int main()
{
    DES_cblock key1, key2, key3, iv;
    DES_key_schedule ks1, ks2, ks3;

    unsigned char plaintext[1024];
    unsigned char ciphertext[2048];
    unsigned char previous[8];

    int len, paddedLen;
    int i;

    printf("3DES CBC ENCRYPTION PROGRAM\n");

    printf("\nEnter plaintext: ");
    if (fgets((char *)plaintext, sizeof(plaintext), stdin) == NULL)
        return 1;

    len = (int)strlen((char *)plaintext);

    if (len > 0 && plaintext[len - 1] == '\n')
        plaintext[--len] = '\0';

    /* Example 3DES keys */
    const unsigned char k1[8] =
        {0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF};

    const unsigned char k2[8] =
        {0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01};

    const unsigned char k3[8] =
        {0x45,0x67,0x89,0xAB,0xCD,0xEF,0x01,0x23};

    const unsigned char initialIV[8] =
        {0x12,0x34,0x56,0x78,0x90,0xAB,0xCD,0xEF};

    memcpy(key1, k1, 8);
    memcpy(key2, k2, 8);
    memcpy(key3, k3, 8);
    memcpy(iv, initialIV, 8);

    DES_set_key_unchecked(&key1, &ks1);
    DES_set_key_unchecked(&key2, &ks2);
    DES_set_key_unchecked(&key3, &ks3);

    /* PKCS#7 padding */
    int padding = 8 - (len % 8);
    paddedLen = len + padding;

    for (i = 0; i < len; i++)
        ciphertext[i] = plaintext[i];

    for (i = len; i < paddedLen; i++)
        ciphertext[i] = (unsigned char)padding;

    memcpy(previous, iv, 8);

    /* CBC encryption */
    for (i = 0; i < paddedLen; i += 8)
    {
        unsigned char block[8];

        /* XOR plaintext with previous ciphertext */
        for (int j = 0; j < 8; j++)
            block[j] = ciphertext[i + j] ^ previous[j];

        /* 3DES EDE encryption */
        DES_ecb3_encrypt(
            (const_DES_cblock *)block,
            (DES_cblock *)(ciphertext + i),
            &ks1, &ks2, &ks3,
            DES_ENCRYPT
        );

        memcpy(previous, ciphertext + i, 8);
    }

    printf("\nPlaintext: %s\n", plaintext);

    printf("Ciphertext (HEX): ");
    for (i = 0; i < paddedLen; i++)
        printf("%02X", ciphertext[i]);

    printf("\n");

    printf("CBC IV: ");
    for (i = 0; i < 8; i++)
        printf("%02X", iv[i]);

    printf("\nEncryption completed successfully.\n");

    return 0;
}
