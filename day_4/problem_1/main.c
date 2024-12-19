#include <stdio.h>
#include <stdlib.h>

int main(int argv, char **argc)
{
    if (argv != 2) {
        fprintf(stderr, "Usage: %s <input.txt>\n", argc[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    char ch;

    fp = fopen(argc[1], "r");

    if (fp == NULL) {
        printf("Unable to open file %s\n", argc[1]);
        exit(EXIT_FAILURE);
    }

    while ((ch = getc(fp)) > 0) {
        printf("%c", ch);
    }
}
