#include "matrix.h"

extern char xmas_array[4];

// solve xmas search using a traversal approach - 
// north/south, east/west, NE/SW, NW/SE
// roughly O(n^8)... Not fantastic!
int solve_traversal(char **matrix, int data_size);

// solve xmas search using a dynamic programming
// approach - find all the 'X's, and extend out to search for 'MAS'
int solve_dp(char **matrix, int data_size);
