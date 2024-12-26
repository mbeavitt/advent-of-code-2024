#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global so that both read_matrix and free_matrix can access
int matrix_size = 0;

void print_matrix(char **matrix, int size);

// frees the memory allocated for the matrix
void free_matrix(char **matrix, int matrix_size);

// reads in a matrix of text from a file, allocating memory as needed
// returns the number of columns/rows read (assumes square matrix)
int read_matrix(FILE *fp, char ***matrix);

// solve xmas search using a traversal approach - 
// north/south, east/west, NE/SW, NW/SE
// roughly O(n^8)... Not fantastic!
int solve_traversal(char **matrix, int data_size);

// solve xmas search using a dynamic programming
// approach
int solve_traversal(char **matrix, int data_size);

int main(int argv, char **argc)
{
    if (argv != 2) {
        fprintf(stderr, "Usage: %s <input.txt>\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    char **matrix = NULL;
    int data_size;
    int xmasses = 0;

    // get a file descriptor for the input data
    fp = fopen(argc[1], "r");

    // check that opening the file actually worked 
    // (e.g. misspelled filename will trigger this)
    if (fp == NULL) {
        fprintf(stderr, "Unable to open file %s\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    // read in matrix to a dynamically resized array
    data_size = read_matrix(fp, &matrix);

    // (for debug) print the matrix to see what's going on
//    print_matrix(matrix, data_size);

    // get number of xmasses using traversal method
    xmasses = solve_traversal(matrix, data_size);

    // free up the memory for the matrix before exit
    printf("Xmasses: %d\n", xmasses);
    free_matrix(matrix, matrix_size);
}

int solve_traversal(char **matrix, int data_size)
{
    // initialise buffer and buffer pointer to
    // reverse strings etc
    char buffer[data_size+1];
    char *ptr = buffer;
    char window[5];
    int xmasses = 0;
    int x, y;

    // checking rows for XMAS (forward direction)
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < data_size-3; j++) {
            strncpy(window, matrix[i] + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        // reset the buffer pointer
        ptr = buffer;
    }

    // checking columns for XMAS (forward direction)
    for (int i = 0; i < data_size; i++) {

        // use inverted indexing to load column
        for (int j = 0; j < data_size; j++) {
            *ptr++ = matrix[j][i];
        }
        buffer[data_size] = '\0';

        // check the buffer for XMAS
        for (int j = 0; j < data_size-3; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        // reset the buffer pointer
        ptr = buffer;
    }

    
    ptr = buffer;
    // iterate through north-east corner & center line
    for (int i = 3; i < data_size; i++) {
        // read diagonal into buffer
        for (int j = 0; j <= i; j++) {
            x = j;
            y = (j - i) + data_size - 1;
            *ptr++ = matrix[x][y];
        }

        // check buffer for hits
        for (int j = 0; j < i-2; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        ptr = buffer;
    }

    // iterate through south-west corner, same deal
    for (int i = data_size - 2; i >= 3; i--) {
        for (int j = i; j >= 0; j--) {
            x = (j - data_size + 1) * -1;
            y = (i - j);
            *ptr++ = matrix[x][y];
        }
        for (int j = 0; j < i-2; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        ptr = buffer;
    }

    // iterate through north-west corner & center line
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j <= i; j++) {
            y = i - j;
            x = j;
            *ptr++ = matrix[x][y];
        }
        for (int j = 0; j < i-2; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        ptr = buffer;
    }

    // iterate through south-east corner
    for (int i = data_size - 2; i >= 0; i--) {
        for (int j = 0; j <= i; j++) {
            x = j - i + data_size - 1;
            y = data_size - j - 1;
            *ptr++ = matrix[x][y];
        }
        for (int j = 0; j < i-2; j++) {
            strncpy(window, buffer + j, 4);
            window[4] = '\0';
            if (strcmp(window, "XMAS") == 0) {
                xmasses++;
            }
            if (strcmp(window, "SAMX") == 0) {
                xmasses++;
            }
        }
        ptr = buffer;
    }

    return xmasses;
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
