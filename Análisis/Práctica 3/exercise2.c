#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "permutations.h"
#include "gen.h"
#include "search.h"

static int parse_positive_int(const char *text, int *value)
{
    char *end;
    long parsed;

    errno = 0;
    parsed = strtol(text, &end, 10);
    if (errno != 0 || *text == '\0' || *end != '\0' ||
        parsed <= 0 || parsed > INT_MAX)
        return 0;

    *value = (int)parsed;
    return 1;
}

int main(int argc, char **argv)
{
    int size = 0, key = 0, position, operations;
    PDICT dictionary;
    int *keys;
    pfunc_key_generator generator = NULL;
    pfunc_search method = NULL;
    char order = NOT_SORTED;
    int have_size = 0, have_key = 0, have_generator = 0, have_order = 0;
    int have_method = 0;

    if (argc != 11) {
        fprintf(stderr,
                "Usage: %s --size <positive-int> --key <int> "
                "--generator <uniform|potential|gaussian> "
                "--order <sorted|unsorted> "
                "--method <binary|linear|auto>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--size") == 0 && !have_size) {
            if (!parse_positive_int(argv[i + 1], &size)) {
                fprintf(stderr, "--size must be a positive integer.\n");
                return EXIT_FAILURE;
            }
            have_size = 1;
        } else if (strcmp(argv[i], "--key") == 0 && !have_key) {
            char *end;
            long parsed;

            errno = 0;
            parsed = strtol(argv[i + 1], &end, 10);
            if (errno != 0 || *argv[i + 1] == '\0' || *end != '\0' ||
                parsed < INT_MIN || parsed > INT_MAX) {
                fprintf(stderr, "--key must be an integer.\n");
                return EXIT_FAILURE;
            }
            key = (int)parsed;
            have_key = 1;
        } else if (strcmp(argv[i], "--generator") == 0 && !have_generator) {
            if (strcmp(argv[i + 1], "uniform") == 0)
                generator = uniform_key_generator;
            else if (strcmp(argv[i + 1], "potential") == 0)
                generator = potential_key_generator;
            else if (strcmp(argv[i + 1], "gaussian") == 0)
                generator = gaussian_key_generator;
            else {
                fprintf(stderr,
                        "Invalid generator '%s'; use uniform, potential, or gaussian.\n",
                        argv[i + 1]);
                return EXIT_FAILURE;
            }
            have_generator = 1;
        } else if (strcmp(argv[i], "--order") == 0 && !have_order) {
            if (strcmp(argv[i + 1], "sorted") == 0)
                order = SORTED;
            else if (strcmp(argv[i + 1], "unsorted") == 0)
                order = NOT_SORTED;
            else {
                fprintf(stderr,
                        "Invalid order '%s'; use sorted or unsorted.\n",
                        argv[i + 1]);
                return EXIT_FAILURE;
            }
            have_order = 1;
        } else if (strcmp(argv[i], "--method") == 0 && !have_method) {
            if (strcmp(argv[i + 1], "binary") == 0)
                method = bin_search;
            else if (strcmp(argv[i + 1], "linear") == 0)
                method = lin_search;
            else if (strcmp(argv[i + 1], "auto") == 0)
                method = lin_auto_search;
            else {
                fprintf(stderr,
                        "Invalid method '%s'; use binary, linear, or auto.\n",
                        argv[i + 1]);
                return EXIT_FAILURE;
            }
            have_method = 1;
        } else {
            fprintf(stderr, "Unknown or duplicate option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!have_size || !have_key || !have_generator || !have_order ||
        !have_method) {
        fprintf(stderr,
                "Options --size, --key, --generator, --order, and --method are required.\n");
        return EXIT_FAILURE;
    }

    if ((method == bin_search && order != SORTED) ||
        (method == lin_auto_search && order != NOT_SORTED)) {
        fprintf(stderr,
                "Binary search requires sorted order; auto search requires unsorted order.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    dictionary = init_dictionary(size, order);
    if (dictionary == NULL) {
        fprintf(stderr, "Could not initialize the dictionary.\n");
        return EXIT_FAILURE;
    }

    keys = malloc((size_t)size * sizeof(*keys));
    if (keys == NULL) {
        fprintf(stderr, "Could not allocate dictionary keys.\n");
        free_dictionary(dictionary);
        return EXIT_FAILURE;
    }

    generator(keys, size, size);
    operations = massive_insertion_dictionary(dictionary, keys, size);
    free(keys);
    if (operations == ERR) {
        fprintf(stderr, "Could not populate the dictionary.\n");
        free_dictionary(dictionary);
        return EXIT_FAILURE;
    }

    operations = search_dictionary(dictionary, key, &position, method);
    if (operations == ERR) {
        fprintf(stderr, "Search failed.\n");
        free_dictionary(dictionary);
        return EXIT_FAILURE;
    }

    if (position != NOT_FOUND)
        printf("Key %d found at position %d in %d basic operations.\n",
               key, position, operations);
    else
        printf("Key %d was not found after %d basic operations.\n",
               key, operations);

    free_dictionary(dictionary);
    return EXIT_SUCCESS;
}
