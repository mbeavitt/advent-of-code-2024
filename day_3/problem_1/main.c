#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s <input.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *fp;
    char ch;

    fp = fopen(argv[1], "r");

    while ((ch = fgetc(fp)) != EOF) {
        printf("%c", ch);
    }
}
