#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

int matrix_size = 0;

void print_matrix(char **matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
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

int read_matrix(FILE *fp, char ***matrix)
{

    int i, j;
    signed char ch;

    // read the file into a matrix, resizing the matrix's memory as we go
    // (should put this in a function...)
    i = j = 0;
    while ((ch = getc(fp)) != EOF) {
        if (i == matrix_size || j == matrix_size) {

            // starting from a matrix size of 0, rescale matrix if data gets too big
            // allocate memory for rows
            // fprintf(stderr, "Reallocating\n");
            size_t newnum = (matrix_size + 2) * 2;
            char **newptr = (char **) realloc((*matrix), newnum * sizeof(char*));
            if (newptr == NULL) {
                fprintf(stderr, "Realloc failed!\n");
                exit(EXIT_FAILURE);
            }

            // allocate memory for columns
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
            // finishing rescaling
            matrix_size = newnum;
            (*matrix) = newptr;
        }

        // actually input the data
        if (ch == '\n') {
            i++;
            j = 0;
            continue;
        } else {
            (*matrix)[i][j++] = ch;
        }
    }

    // assigning final matrix size to 'data_size'
    return i;
}
