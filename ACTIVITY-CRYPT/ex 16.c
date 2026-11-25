#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define ALPHABET 26
#define MAX_TEXT 10000
#define MAX_TOP 50
#define RESTARTS 20
#define ITERATIONS 100000

double quadgram[26][26][26][26];
double floorScore;
char cipher[MAX_TEXT];
int cipherLength;

typedef struct {
    double score;
    char key[26];
    char plaintext[MAX_TEXT];
} Candidate;

Candidate top[MAX_TOP];
int topCount = 0;

/* Convert four letters into a quadgram index */
int indexOf(char a, char b, char c, char d)
{
    return (((a * 26 + b) * 26 + c) * 26 + d);
}

/* Load English quadgram statistics */
int loadQuadgrams(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: Cannot open %s\n", filename);
        printf("Download the English quadgram file first.\n");
        return 0;
    }

    char gram[10];
    long count;
    long total = 0;

    while (fscanf(fp, "%9s %ld", gram, &count) == 2) {
        if (strlen(gram) != 4)
            continue;

        for (int i = 0; i < 4; i++)
            gram[i] = (char)toupper((unsigned char)gram[i]);

        int valid = 1;
        for (int i = 0; i < 4; i++) {
            if (gram[i] < 'A' || gram[i] > 'Z')
                valid = 0;
        }

        if (!valid)
            continue;

        int a = gram[0] - 'A';
        int b = gram[1] - 'A';
        int c = gram[2] - 'A';
        int d = gram[3] - 'A';

        quadgram[a][b][c][d] = (double)count;
        total += count;
    }

    fclose(fp);

    if (total == 0) {
        printf("Invalid quadgram file.\n");
        return 0;
    }

    floorScore = log10(0.01 / (double)total);

    for (int a = 0; a < 26; a++)
        for (int b = 0; b < 26; b++)
            for (int c = 0; c < 26; c++)
                for (int d = 0; d < 26; d++) {
                    if (quadgram[a][b][c][d] > 0)
                        quadgram[a][b][c][d] =
                            log10(quadgram[a][b][c][d] / total);
                    else
                        quadgram[a][b][c][d] = floorScore;
                }

    return 1;
}

/* Decrypt using the substitution key */
void decrypt(char *key, char *output)
{
    int j = 0;

    for (int i = 0; cipher[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)cipher[i];

        if (isalpha(ch)) {
            int upper = isupper(ch);
            char result = key[toupper(ch) - 'A'];
            output[j++] = upper ? result : (char)tolower(result);
        } else {
            output[j++] = (char)ch;
        }
    }

    output[j] = '\0';
}

/* Calculate English quadgram score */
double calculateScore(char *text)
{
    char letters[MAX_TEXT];
    int n = 0;

    for (int i = 0; text[i] != '\0'; i++) {
        unsigned char ch = (unsigned char)text[i];

        if (isalpha(ch))
            letters[n++] = (char)toupper(ch);
    }

    if (n < 4)
        return -1e9;

    double score = 0;

    for (int i = 0; i <= n - 4; i++) {
        int a = letters[i] - 'A';
        int b = letters[i + 1] - 'A';
        int c = letters[i + 2] - 'A';
        int d = letters[i + 3] - 'A';

        score += quadgram[a][b][c][d];
    }

    return score;
}

/* Generate a random substitution key */
void generateKey(char *key)
{
    for (int i = 0; i < 26; i++)
        key[i] = 'A' + i;

    for (int i = 25; i > 0; i--) {
        int j = rand() % (i + 1);

        char temp = key[i];
        key[i] = key[j];
        key[j] = temp;
    }
}

/* Insert a candidate into the top results */
void saveCandidate(char *key, double score)
{
    char plaintext[MAX_TEXT];

    decrypt(key, plaintext);

    for (int i = 0; i < topCount; i++) {
        if (strcmp(top[i].plaintext, plaintext) == 0) {
            if (score > top[i].score)
                top[i].score = score;
            return;
        }
    }

    int position = topCount;

    if (topCount < MAX_TOP)
        topCount++;
    else if (score <= top[topCount - 1].score)
        return;
    else
        position = topCount - 1;

    while (position > 0 && top[position - 1].score < score) {
        top[position] = top[position - 1];
        position--;
    }

    top[position].score = score;
    strcpy(top[position].key, key);
    strcpy(top[position].plaintext, plaintext);
}

/* Simulated annealing attack */
void attack()
{
    char key[26];
    char bestKey[26];
    char plaintext[MAX_TEXT];

    for (int restart = 0; restart < RESTARTS; restart++) {

        generateKey(key);
        decrypt(key, plaintext);

        double currentScore = calculateScore(plaintext);

        memcpy(bestKey, key, 26);
        double bestScore = currentScore;

        for (int iter = 0; iter < ITERATIONS; iter++) {

            double temperature =
                20.0 * pow(0.01, (double)iter / ITERATIONS);

            int a = rand() % 26;
            int b = rand() % 26;

            while (a == b)
                b = rand() % 26;

            char temp = key[a];
            key[a] = key[b];
            key[b] = temp;

            decrypt(key, plaintext);
            double newScore = calculateScore(plaintext);

            double difference = newScore - currentScore;

            if (difference > 0 ||
                ((double)rand() / RAND_MAX) <
                exp(difference / temperature)) {

                currentScore = newScore;

                if (currentScore > bestScore) {
                    bestScore = currentScore;
                    memcpy(bestKey, key, 26);
                }
            } else {
                temp = key[a];
                key[a] = key[b];
                key[b] = temp;
            }
        }

        saveCandidate(bestKey, bestScore);

        printf("Attack %d/%d completed.\n",
               restart + 1, RESTARTS);
    }
}

int main()
{
    int requested;

    srand((unsigned int)time(NULL));

    printf("========================================\n");
    printf(" MONOALPHABETIC FREQUENCY ATTACK\n");
    printf("========================================\n");

    if (!loadQuadgrams("english_quadgrams.txt"))
        return 1;

    printf("\nEnter ciphertext:\n");

    if (fgets(cipher, sizeof(cipher), stdin) == NULL)
        return 1;

    cipher[strcspn(cipher, "\n")] = '\0';

    cipherLength = (int)strlen(cipher);

    if (cipherLength < 4) {
        printf("Ciphertext must contain at least 4 characters.\n");
        return 1;
    }

    printf("\nHow many possible plaintexts do you want? ");
    if (scanf("%d", &requested) != 1)
        return 1;

    if (requested < 1 || requested > MAX_TOP) {
        printf("Enter a number between 1 and %d.\n", MAX_TOP);
        return 1;
    }

    printf("\nStarting automatic attack...\n\n");

    attack();

    printf("\n========================================\n");
    printf(" TOP %d POSSIBLE PLAINTEXTS\n", requested);
    printf("========================================\n");

    int display = requested < topCount ? requested : topCount;

    for (int i = 0; i < display; i++) {
        printf("\nRank: %d\n", i + 1);
        printf("Score: %.2f\n", top[i].score);
        printf("Key: ");

        for (int j = 0; j < 26; j++)
            printf("%c", top[i].key[j]);

        printf("\nPlaintext: %s\n", top[i].plaintext);
    }

    printf("\nAttack completed successfully.\n");

    return 0;
}