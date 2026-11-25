
#include <stdio.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8
#define BLOCKS 4

void printBlocks(char *title, unsigned char data[][8])
{
    printf("\n%s\n", title);

    for (int i = 0; i < BLOCKS; i++)
    {
        printf("Block P%d: ", i + 1);

        for (int j = 0; j < BLOCK_SIZE; j++)
            printf("%02X ", data[i][j]);

        printf("\n");
    }
}

int main()
{
    DES_cblock key = {
        0x13,0x34,0x57,0x79,
        0x9B,0xBC,0xDF,0xF1
    };

    DES_cblock iv = {
        0x12,0x34,0x56,0x78,
        0x90,0xAB,0xCD,0xEF
    };

    DES_key_schedule ks;

    unsigned char plaintext[BLOCKS][8] = {
        "ABCDEFGH",
        "IJKLMNOP",
        "QRSTUVWX",
        "YZ123456"
    };

    unsigned char ecb[BLOCKS][8];
    unsigned char ecbResult[BLOCKS][8];

    unsigned char cbc[BLOCKS][8];
    unsigned char cbcResult[BLOCKS][8];

    unsigned char sourceError[BLOCKS][8];
    unsigned char sourceCipher[BLOCKS][8];
    unsigned char sourceResult[BLOCKS][8];

    DES_set_key_unchecked(&key, &ks);

    /* ECB Encryption */
    for (int i = 0; i < BLOCKS; i++)
        DES_ecb_encrypt(
            (const_DES_cblock *)plaintext[i],
            (DES_cblock *)ecb[i],
            &ks, DES_ENCRYPT
        );

    /* Introduce error in transmitted ECB C1 */
    ecb[0][0] ^= 0x01;

    /* ECB Decryption */
    for (int i = 0; i < BLOCKS; i++)
        DES_ecb_encrypt(
            (const_DES_cblock *)ecb[i],
            (DES_cblock *)ecbResult[i],
            &ks, DES_DECRYPT
        );

    printBlocks("ECB: Decryption after C1 error", ecbResult);

    /* CBC Encryption */
    DES_ncbc_encrypt(
        (const unsigned char *)plaintext,
        (unsigned char *)cbc,
        sizeof(plaintext),
        &ks, &iv, DES_ENCRYPT
    );

    /* Introduce error in transmitted CBC C1 */
    cbc[0][0] ^= 0x01;

    /* CBC Decryption */
    DES_ncbc_encrypt(
        (const unsigned char *)cbc,
        (unsigned char *)cbcResult,
        sizeof(cbc),
        &ks, &iv, DES_DECRYPT
    );

    printBlocks("CBC: Decryption after C1 error", cbcResult);

    /* Introduce error in source plaintext P1 */
    memcpy(sourceError, plaintext, sizeof(plaintext));
    sourceError[0][0] ^= 0x01;

    /* Encrypt modified plaintext using CBC */
    DES_ncbc_encrypt(
        (const unsigned char *)sourceError,
        (unsigned char *)sourceCipher,
        sizeof(sourceError),
        &ks, &iv, DES_ENCRYPT
    );

    /* Decrypt modified ciphertext */
    DES_ncbc_encrypt(
        (const unsigned char *)sourceCipher,
        (unsigned char *)sourceResult,
        sizeof(sourceCipher),
        &ks, &iv, DES_DECRYPT
    );

    printBlocks("CBC: Result after source P1 error",
                sourceResult);

    return 0;
}
