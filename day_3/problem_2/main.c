#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <input.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // regex variables
    regex_t    regex;
    regmatch_t pmatch[1];
    regoff_t   off, len;
    char *re = "mul\\([0-9]+,[0-9]+\\)|do\\(\\)|don't\\(\\)";

    // file read variables
    char *line = NULL;
    size_t line_len = 0;
    ssize_t nread;
    FILE *fp = fopen(argv[1], "r");

    // other variables
    int val_1, val_2;
    int result = 0;
    char match[20];
    bool mul_switch = true;

    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((nread = getline(&line, &line_len, fp)) != -1) {

        char *s =  line;

        if (regcomp(&regex, re, REG_EXTENDED))
            exit(EXIT_FAILURE);

        printf("String = \"%s\"\n", line);
        printf("Matches:\n");

        for (unsigned int i = 0; ; i++) {
            if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0))
                break;

            off = pmatch[0].rm_so + (s - line);
            line_len = pmatch[0].rm_eo - pmatch[0].rm_so;

            strncpy(match, s + pmatch[0].rm_so, line_len);
            match[line_len] = '\0'; // I thought strncpy did this but apparently not

            if (strcmp(match, "do()") == 0) {
                printf("Setting switch to on\n");
                mul_switch = true;
            } else if (strcmp(match, "don't()") == 0) {
                printf("Setting switch to off\n");
                mul_switch = false;
            } else {
                if (mul_switch) {

                sscanf(match, "mul(%d,%d)", &val_1, &val_2);
                printf("%d, %d\n", val_1, val_2);
                result += (int) (val_1 * val_2);

                }
            }

            // advance input string
            s += pmatch[0].rm_eo;
        }
    }

    free(line);
    fclose(fp);

    printf("Result: %d\n", result);
}
