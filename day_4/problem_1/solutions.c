#include <string.h>
#include <stdio.h>

char xmas_array[4] = {'X', 'M', 'A', 'S'};

enum CompassDirection {
    NW = 0,   // Northwest
    NN,       // North
    NE,       // Northeast
    WW,       // West
    EE,       // East
    SW,       // Southwest
    SS,       // South
    SE,       // Southeast
    NUM_DIRECTIONS
};

// Direction vectors as offsets
int directions[8][2] = {
    {-1, -1}, // NW
    { 0, -1}, // NN
    { 1, -1}, // NE
    {-1,  0}, // WW
    { 1,  0}, // EE
    {-1,  1}, // SW
    { 0,  1}, // SS
    { 1,  1}  // SE
};


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

int solve_dp(char **matrix, int data_size)
{
    int xmasses = 0;

    // solve xmas search using a dynamic programming
    // approach - find all the 'X's, and extend out to search for 'MAS'
    for (int i = 0; i < data_size; i++) {
        for (int j = 0; j < data_size; j++) {
            if (matrix[i][j] == 'X') {

                // dummies for i and j so we don't lose our place
                int k = i;
                int l = j;

                // iterate through compass directions
                for (int dir = NW; dir < NUM_DIRECTIONS; dir++) {

                    // iterate through the 'MAS' of 'XMAS'. We can also nicely use the counter
                    // as a multiplier for our 'direction' offset, stretching further and further
                    // into the matrix each iteration
                    for (int trace_counter = 1; trace_counter < 4; trace_counter++) {

                        // write direction offset to new variable for tidiness
                        signed int x_offset = directions[dir][0] * trace_counter;
                        signed int y_offset = directions[dir][1] * trace_counter;

                        // check matrix bounds
                        if (k + x_offset >= 0 &&
                            k + x_offset < data_size &&
                            l + y_offset >= 0 &&
                            l + y_offset < data_size) {

                            // we look in a direction (given by dir) and see if it
                            // links to the expected next letter in the sequence 'MAS'
                            if (matrix[i + x_offset][j + y_offset] == xmas_array[trace_counter]) {
                            } else {
                                break; // the chain was broken
                            }

                            if (trace_counter == 3) {
                                xmasses++;
                            }
                        }
                    }
                }
                // do DP solution
            }
        }
    }

    return xmasses;
}
