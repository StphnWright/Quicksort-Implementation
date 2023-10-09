#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quicksort.h"

#define MAX_STRLEN     64 // Not including '\0'
#define MAX_ELEMENTS 1024

int int_cmp(const void *a, const void *b) {
    int *a2 = (int *) a;
    int *b2 = (int *) b;
    int a3 = *a2;
    int b3 = *b2;

    if (a3 < b3) {
        return -1;
    } else if (a3 > b3) {
        return 1;
    } else {
        return 0;
    }
}

int dbl_cmp(const void *a, const void *b) {
    double *a2 = (double *) a;
    double *b2 = (double *) b;
    double a3 = *a2;
    double b3 = *b2;

    if (a3 < b3) {
        return -1;
    } else if (a3 > b3) {
        return 1;
    } else {
        return 0;
    }
}

int str_cmp(const void *a, const void *b) {
    char **a2 = (char **) a;
    char **b2 = (char **) b;

    return strcmp(*a2, *b2);
}

void test_int() {
    int int_array[] = {-2, 7, 1, -4, -1, 0, 3, 8};
    quicksort(int_array, 8, 4, int_cmp);

    for (int i = 0; i < 8; i++) {
        printf("%d ", int_array[i]);
    }
    printf("\n");
}

void test_double() {
    double dbl_array[] = {-2.6, 7.3, 1.2, -4.9, -1.5, 0.3, 3.6, 8.9};
    quicksort(dbl_array, 8, 8, dbl_cmp);

    for (int i = 0; i < 8; i++) {
        printf("%.2lf ", dbl_array[i]);
    }
    printf("\n");
}

void test_str() {
    char *str_array[] = {"hello", "bicycle", "car", "book", "bird", "Kite", "Lamb", "train"};
    quicksort(str_array, 8, 8, str_cmp);

    for (int i = 0; i < 8; i++) {
        printf("%s ", str_array[i]);
    }
    printf("\n");
}

void usage() {
    printf("Usage: ./sort [-i|-d] [filename]\n");
    printf("   -i: Specifies the input contains ints.\n");
    printf("   -d: Specifies the input contains doubles.\n");
    printf("   filename: The file to sort. If no file is supplied, input is read from\n");
    printf("             stdin.\n");
    printf("   No flags defaults to sorting strings.\n");
}

int main(int argc, char **argv) {
    int sort_int = 0;
    int sort_double = 0;
    //char *filename = NULL;
    
    int opt;

    //C1 - Invalid flag test
    while((opt = getopt(argc, argv, "id")) != -1) {
        switch (opt) {
            case 'i':
                sort_int = 1;
                break;
            case 'd':
                sort_double = 1;
                break;
            case '?':
                //C5 - Multiple flags with invalid flag test
                printf("Error: Unknown option '-%c' received.\n", optopt);
                usage();
                exit(EXIT_FAILURE);
        }
    } 

    //C3 - Multiple filenames test
    if (argc - optind > 1) {
        printf("Error: Too many files specified.\n");
        exit(EXIT_FAILURE);
    }

    //C4 - Multiple valid flag test
    if (sort_int == 1 && sort_double == 1) {
        printf("Error: Too many flags specified.\n");
        exit(EXIT_FAILURE);
    }

    FILE *file;

    //C2 - Invalid filename test
    if (argc == optind) {
        file = stdin;
    } else {
        file = fopen(argv[optind], "r");
        if (file == NULL) {
            printf("Error: Cannot open '%s'. %s.\n", argv[optind], strerror(errno));
            exit(EXIT_FAILURE);
        } 
    }

    if (sort_int == 1) {
        int array[MAX_ELEMENTS];
        int size = 0;
        
        while (fscanf(file, "%d\n", &array[size]) > 0) {
            size++;
        }

        quicksort(array, size, sizeof(int), int_cmp);

        for (int i = 0; i < size; i++) {
            printf("%d\n", array[i]);
        }
    } else if (sort_double == 1) {
        double array[MAX_ELEMENTS];
        int size = 0;
        
        while (fscanf(file, "%lf\n", &array[size]) > 0) {
            size++;
        }

        quicksort(array, size, sizeof(double), dbl_cmp);

        for (int i = 0; i < size; i++) {
            printf("%.6lf\n", array[i]);
        }
    } else {
        char *array[MAX_ELEMENTS];
        
        for (int i = 0; i < MAX_ELEMENTS; i++) {
            array[i] = malloc((MAX_STRLEN + 1) * sizeof(char));
            if (array[i] == NULL) {
                fprintf(stderr, "malloc failed\n");
                for (int j = 0; j < i; j++) {
                    free(array[j]);
                }
                exit(EXIT_FAILURE);
            }
        }
    
        int size = 0;
        
        while (fscanf(file, "%s\n", &array[size][0]) > 0) {
            size++;
        }

        quicksort(&array[0], size, sizeof(char *), str_cmp);

        for (int i = 0; i < size; i++) {
            printf("%s\n", array[i]);
        }

        for (int i = 0; i < MAX_ELEMENTS; i++) {
            free(array[i]);
        }
    }

    fclose(file);    
    return EXIT_SUCCESS;
}
