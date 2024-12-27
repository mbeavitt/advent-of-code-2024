#include <stdio.h>

// global so that both read_matrix and free_matrix can access
extern int matrix_size;

// prints the matrix using its size, assumes square matrix
void print_matrix(char **matrix, int size);

// frees the memory allocated for the matrix
void free_matrix(char **matrix, int matrix_size);

// reads in a matrix of text from a file, allocating memory as needed
// returns the number of columns/rows read (assumes square matrix)
int read_matrix(FILE *fp, char ***matrix);
