#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_STR_LEN 100
#define ARRAY_LEN 20

// Reads a line from the file pointed to by fp.
// Returns number of entries written to array.
int read_line(int *a, int len, FILE *fp);

// reads the array, returning true if it's 'safe', false if 'unsafe'
bool check_line(int *a, int len);

int main(int argv, char **argc)
{
    // check that an input file was given
    if (argv != 2) {
        printf("Usage: %s <input.txt>\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    int a[ARRAY_LEN];
    int nums_read;

    int safe_lines = 0;

    fp = fopen(argc[1], "r");

    if (fp == NULL) {
        printf("Could not open file %s\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    // read lines in one at a time from the file, and if
    // they are valid 'safe' lines, increment safe_lines.
    for (;;) {
        nums_read = read_line(a, ARRAY_LEN, fp);

        if (nums_read == 0) {
            break;
        }

        for (int i = 0; i < nums_read; i++) {
            printf("%d ", a[i]);
        }

        if (check_line(a, nums_read) == true) {
            safe_lines++;
        }

        printf("\n");
    }

    printf("\nSafe levels: %d\n", safe_lines);

}

bool check_line(int *a, int len)
{
    bool lt         = false;
    bool gt         = false;
    bool eq         = false;
    bool over_three = false;

    int diff;

    for (int i = 1; i < len; i++) {

        if (a[i] > a[i-1]) {
            lt = true;
        } else if (a[i] == a[i-1]) {
            eq = true;
        } else {
            gt = true;
        }

        // difference between current and last number
        diff = a[i] - a[i-1];
        // converting to absolute difference
        diff = diff < 0 ? diff * -1 : diff;

        if (diff > 3) {
            over_three = true;
        }
    }

    if (!(over_three || (lt && gt) || eq)) {
        return true;
    } else {
        return false;
    }

}

int read_line(int *a, int len, FILE *fp)
{
    char str[MAX_STR_LEN];
    char *p = str;
    int i = 0;

    // read in line from file pointer
    if (fgets(str, sizeof(str), fp) == NULL) {
        return 0;
    }

    // deal with any whitespace at beginning of line
    while (isspace(*p)) {
        p++;
    }

    // scan line into array, then increment string ptr to next digit
    while (sscanf(p, "%d", &a[i]) != EOF) {
        i++;
        // p is still pointing at old digit
        while (isdigit(*p)) {
            p++;
        }
        while (isspace(*p)) {
            p++;
        }
        // p should now point to next digit
    }

    return i;
}
