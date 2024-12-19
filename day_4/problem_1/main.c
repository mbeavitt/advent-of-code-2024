#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_matrix(char **matrix, int matrix_size);
void free_matrix(char **matrix, int matrix_size);

// reads in a matrix of text from a file, allocating memory as needed
char **read_matrix(FILE *fp);

int main(int argv, char **argc)
{
    if (argv != 2) {
        fprintf(stderr, "Usage: %s <input.txt>\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    char ch;
    char **matrix = NULL;
    char window[5];
    int i, j;
    int matrix_size = 0;
    int data_size;
    int xmasses = 0;

    fp = fopen(argc[1], "r");

    if (fp == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    i = j = 0;
    while ((ch = getc(fp)) > 0) {
        if (i == matrix_size || j == matrix_size) {

            fprintf(stderr, "Reallocating\n");
            // allocate rows
            size_t newnum = (matrix_size + 2) * 2;
            char **newptr = (char **) realloc(matrix, newnum * sizeof(char*));
            if (newptr == NULL) {
                fprintf(stderr, "Realloc failed!\n");
                exit(EXIT_FAILURE);
            }

            // allocate columns
            for (int i = 0; i < newnum; i++) {
                if (i < matrix_size) {
                    // reallocate if column exists already
                    char *temp_row = realloc(newptr[i], newnum * sizeof(char));
                    if (temp_row == NULL) {
                        fprintf(stderr, "Realloc failed!\n");
                        exit(EXIT_FAILURE);
                    }
                    newptr[i] = temp_row;
                } else {
                    newptr[i] = malloc(newnum * sizeof(char));
                    if (newptr[i] == NULL) {
                        fprintf(stderr, "Malloc failed!\n");
                        exit(EXIT_FAILURE);
                    }
                }
            }

            matrix_size = newnum;
            matrix = newptr;
        }

        if (ch == '\n') {
            i++;
            j = 0;
            continue;
        } else {
            matrix[i][j++] = ch;
        }
    }

    data_size = i;

    print_matrix(matrix, data_size);

    // checking rows
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < data_size-3; j++) {
            strncpy(window, matrix[i] + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                printf("XMAS found! (row)\n");
                xmasses++;
            }
        }
    }
    // checking columns
    char buffer[data_size+1];
    char *ptr = buffer;
    for (int i = 0; i < data_size; i++) {

        // invert the matrix and put it into a buffer
        for (int j = 0; j < data_size; j++) {
            *ptr++ = matrix[j][i];
        }
        buffer[data_size] = '\0';

        // same approach as before
        for (int j = 0; j < data_size-3; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                printf("XMAS found! (column)\n");
                xmasses++;
            }
        }

        // reset the buffer
        ptr = buffer;
    }

    free_matrix(matrix, matrix_size);
}

void print_matrix(char **matrix, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void free_matrix(char **matrix, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        free(matrix[i]);
    }
    free(matrix);
}
