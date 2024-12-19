#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

char *str = "1) John Driverhacker 2) John Doe 3) John Foo;";
char *re = "John Doe";

int main(int argc, char **argv)
{
    if (argc != 2) {
        printf("Usage: %s <input.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *s =  str;
    regex_t    regex;
    regmatch_t pmatch[1];
    regoff_t   off, len;

    if (regcomp(&regex, re, REG_NEWLINE))
        exit(EXIT_FAILURE);

    printf("String = \"%s\"\n", str);
    printf("Matches:\n");

    for (unsigned int i = 0; ; i++) {
        if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0))
            break;

        off = pmatch[0].rm_so + (s - str);
        len = pmatch[0].rm_eo - pmatch[0].rm_so;
        printf("#%zu:\n", i);
        printf("offset = %jd; length = %jd\n", (intmax_t) off,
                (intmax_t) len);
        printf("substring = \"%.*s\"\n", len, s + pmatch[0].rm_so);

        s += pmatch[0].rm_eo;
    }

/*
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    while ((nread = getline(&line, &len, fp)) != -1) {
        fwrite(line, nread, 1, stdout);
    }

    free(line);
    fclose(fp);
*/
}
