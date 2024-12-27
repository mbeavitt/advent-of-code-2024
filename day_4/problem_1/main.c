#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "solutions.h"

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
    //print_matrix(matrix, data_size);

    // get number of xmasses using dynamic programming method
    xmasses = solve_dp(matrix, data_size);

    // free up the memory for the matrix before exit
    printf("Xmasses: %d\n", xmasses);

    // old traversal method
    //xmasses = solve_traversal(matrix, data_size);
    //printf("Xmasses: %d\n", xmasses);

    free_matrix(matrix, matrix_size);
}
