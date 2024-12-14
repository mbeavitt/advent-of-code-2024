#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

int scan_file(FILE *fp, int **a1, int **a2);
int compare(const void *a, const void *b);

int array_size = 100;

int main(int argc, char **argv)
{
    FILE *fp;
    int lines_read;
    int diff;
    int total_difference = 0;
    int *a1, *a2;

    if (argc != 2) {
        printf("Usage: %s <input.txt>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    a1 = malloc(array_size * sizeof(int));
    a2 = malloc(array_size * sizeof(int));

    if (a1 == NULL || a2 == NULL) {
        printf("Error: out of memory!\n");
        exit(EXIT_FAILURE);
    }

    printf("Reading %s\n", argv[1]);
    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("Could not open file for reading!\n");
        exit(EXIT_FAILURE);
    } 

    lines_read = scan_file(fp, &a1, &a2);

    qsort(a1, lines_read, sizeof(int), compare);
    qsort(a2, lines_read, sizeof(int), compare);

    for (int i = 0; i < lines_read; i++) {
        diff = a1[i] - a2[i];
        diff = diff < 0 ? (diff * -1) : diff; 
        total_difference += diff;
    }
    
    printf("Total difference: %d\n", total_difference);

    free(a1);
    free(a2);
    fclose(fp);
}

int scan_file(FILE *fp, int **a1, int **a2)
{
    int lines_read = 0;

    while (fscanf(fp, "%d %d", &(*a1)[lines_read], &(*a2)[lines_read]) == 2) {
        lines_read++;
        if (lines_read == array_size) {
            array_size = array_size * 2;
            *a1 = realloc(*a1, array_size * sizeof(int));
            *a2 = realloc(*a2, array_size * sizeof(int));

            if (*a1 == NULL || *a2 == NULL) {
                printf("Error: out of memory!\n");
                exit(EXIT_FAILURE);
            }
        }
    }

    return lines_read;
}

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}    
