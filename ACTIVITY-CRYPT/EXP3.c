#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

void createMatrix(char key[]) {
    int used[26] = {0};
    int row = 0, col = 0;

    used['J' - 'A'] = 1;  // I and J share a cell

    // Insert key
    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);

        if (!isalpha(ch))
            continue;

        if (ch == 'J')
            ch = 'I';

        if (!used[ch - 'A']) {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Insert remaining alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J')
            continue;

        if (!used[ch - 'A']) {
            matrix[row][col] = ch;
            used[ch - 'A'] = 1;

            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

void printMatrix() {
    printf("\nPlayfair Matrix:\n");

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void findPosition(char ch, int *row, int *col) {
    if (ch == 'J')
        ch = 'I';

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void prepareText(char input[], char output[]) {
    int k = 0;

    // Remove spaces and convert to uppercase
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            char ch = toupper(input[i]);

            if (ch == 'J')
                ch = 'I';

            output[k++] = ch;
        }
    }

    output[k] = '\0';

    // Insert X between repeated letters
    char temp[1000];
    int j = 0;

    for (int i = 0; i < k; i++) {
        temp[j++] = output[i];

        if (i + 1 < k && output[i] == output[i + 1]) {
            temp[j++] = 'X';
        }
    }

    // Add X if length is odd
    if (j % 2 != 0)
        temp[j++] = 'X';

    temp[j] = '\0';

    strcpy(output, temp);
}

void encrypt(char text[], char cipher[]) {
    int len = strlen(text);
    int k = 0;

    for (int i = 0; i < len; i += 2) {
        char a = text[i];
        char b = text[i + 1];

        int r1, c1, r2, c2;

        findPosition(a, &r1, &c1);
        findPosition(b, &r2, &c2);

        if (r1 == r2) {
            // Same row
            cipher[k++] = matrix[r1][(c1 + 1) % 5];
            cipher[k++] = matrix[r2][(c2 + 1) % 5];
        }
        else if (c1 == c2) {
            // Same column
            cipher[k++] = matrix[(r1 + 1) % 5][c1];
            cipher[k++] = matrix[(r2 + 1) % 5][c2];
        }
        else {
            // Rectangle
            cipher[k++] = matrix[r1][c2];
            cipher[k++] = matrix[r2][c1];
        }
    }

    cipher[k] = '\0';
}

int main() {
    char key[100];
    char plaintext[1000];
    char prepared[1000];
    char ciphertext[1000];

    printf("Enter keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0';

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    createMatrix(key);
    printMatrix();

    prepareText(plaintext, prepared);

    printf("\nPrepared plaintext: %s\n", prepared);

    encrypt(prepared, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}