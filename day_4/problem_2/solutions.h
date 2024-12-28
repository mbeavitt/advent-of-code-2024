#include "matrix.h"

extern char xmas_array[3];

// solve xmas search using a dynamic programming
// approach - find all the 'X's, and extend out to search for 'MAS'
int solve_dp(char **matrix, int data_size);
