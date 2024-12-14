#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argv, char **argc)
{
    if (argv != 2) {
        printf("Usage: %s <input.txt>\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    int a[5];
    int safe_reports = 0;
    int diff;

    fp = fopen(argc[1], "r");

    if (fp == NULL) {
        printf("Could not open file %s\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    while (fscanf(fp, "%d %d %d %d %d", &a[0], &a[1], &a[2], &a[3], &a[4]) == 5) {
        bool lt         = false;
        bool gt         = false;
        bool eq         = false;
        bool over_three = false;

        for (int i = 1; i < 5; i++) {
            if (a[i] > a[i-1]) {
                lt = true;
            } else if (a[i] == a[i-1]) {
                eq = true;
            } else {
                gt = true;
            }

            diff = a[i] - a[i-1];
            diff = diff < 0 ? diff * -1 : diff;

            if (diff > 3) {
                over_three = true;
            }

        }

        if (!(over_three || (lt && gt) || eq)) {
            safe_reports++;
        }
    }    

    printf("Safe reports: %d\n", safe_reports);
}
