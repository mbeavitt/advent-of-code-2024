#include <string.h>
#include <stdio.h>
#include <stdbool.h>

enum CompassDirection {
    NW = 0,   // Northwest
    NE,       // Northeast
    SW,       // Southwest
    SE,       // Southeast
    NUM_DIRECTIONS
};

char letter_sequence[4] = {'M','M','S','S'};

// Direction vectors as offsets (only diagonal now)
int directions[4][2] = {
    {-1, -1}, // NW
    { 1, -1}, // NE
    { 1,  1}, // SE
    {-1,  1}  // SW
};

int solve_dp(char **matrix, int data_size)
{
    int xmasses = 0;
    bool cross_found;

    // solve xmas search using a dynamic programming
    // approach - find all the 'A's, and extend out to search for 'MAS'
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < data_size; j++) {
            if (matrix[i][j] == 'A') {
                for (int cycle = 0; cycle < 4; cycle++) {

                    cross_found = true;

                    for (int dir = 0; dir < NUM_DIRECTIONS; dir++) {

                        //printf("dir: %d, cycle: %d\t", dir, cycle);
                        //printf(" O:%d\n", dir_offset);

                        // wrap orientation of cross search using 'cycle' counter
                        // this lets us cycle through the diagonals searching for
                        // different MAS crosses, e.g. both of these should be a hit
                        //
                        // M M   M S
                        //  A     A 
                        // S S   M S
                        //
                        int dir_offset = (dir + cycle) % 4;

                        int x_offset = directions[dir_offset][0];
                        int y_offset = directions[dir_offset][1];

                        // check bounds
                        if (i + x_offset >= 0 &&
                            i + x_offset < data_size &&
                            j + y_offset >= 0 &&
                            j + y_offset < data_size) {
                            if (matrix[i + x_offset][j + y_offset] != letter_sequence[dir]) {
                                cross_found = false;
                                //break;
                            }

                            //printf("Target: %c  ", letter_sequence[dir]);
                            //printf("%c ", matrix[i + x_offset][j + y_offset]);
                            //printf("(%d:%d)  ", i + x_offset, j + y_offset);

                            if (dir == 3 && cross_found) {
                                //printf("Found crossed mas!\n");
                                xmasses++;
                            }
                        } else {
                            break;
                        }
                    }
                    //printf("\n");
                }
            }
        }
    }

    return xmasses;
}

// check matrix[i + directions[0][0]][j + directions[0][1]] for M
// check matrix[i + directions[1][0]][j + directions[1][1]] for M
// check matrix[i + directions[2][0]][j + directions[2][1]] for M
// check matrix[i + directions[3][0]][j + directions[3][1]] for M
//
// check NE for M
// check SE for M
// check SW for S
// check NW for S
//
// check SE for M
// check SW for M
// check NW for S
// check NE for S
//
// check SW for M
// check NW for M
// check NE for S
// check SE for S
