#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "search.h"
#include "gen.h"    
#include "times.h"

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
    int min_size = 0, max_size = 0, size_incr = 0, n_perms = 0, n_keys = 0;
    char *file = NULL;
    pfunc_key_generator generator = NULL;
    pfunc_search method = NULL;
    char order = NOT_SORTED;
    int have_min_size = 0, have_max_size = 0, have_size_incr = 0;
    int have_n_perms = 0, have_n_keys = 0;
    int have_generator = 0, have_order = 0, have_method = 0;

    if (argc != 19) {
        fprintf(stderr,
                "Usage: %s --min-size N --max-size N --size_incr N "
                "--n_perms N --n_keys N --generator NAME "
                "--order <sorted|unsorted> --method <binary|linear|auto> "
                "--output FILE\n"
                "NAME must be uniform, potential, or gaussian; auto search "
                "requires unsorted order.\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i += 2) {
        int *number = NULL;
        int *present = NULL;

        if (strcmp(argv[i], "--min-size") == 0) {
            number = &min_size;
            present = &have_min_size;
        } else if (strcmp(argv[i], "--max-size") == 0) {
            number = &max_size;
            present = &have_max_size;
        } else if (strcmp(argv[i], "--size_incr") == 0) {
            number = &size_incr;
            present = &have_size_incr;
        } else if (strcmp(argv[i], "--n_perms") == 0) {
            number = &n_perms;
            present = &have_n_perms;
        } else if (strcmp(argv[i], "--n_keys") == 0) {
            number = &n_keys;
            present = &have_n_keys;
        } else if (strcmp(argv[i], "--generator") == 0) {
            if (have_generator) {
                fprintf(stderr, "Duplicate --generator option.\n");
                return EXIT_FAILURE;
            }
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
            continue;
        } else if (strcmp(argv[i], "--order") == 0) {
            if (have_order) {
                fprintf(stderr, "Duplicate --order option.\n");
                return EXIT_FAILURE;
            }
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
            continue;
        } else if (strcmp(argv[i], "--method") == 0) {
            if (have_method) {
                fprintf(stderr, "Duplicate --method option.\n");
                return EXIT_FAILURE;
            }
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
            continue;
        } else if (strcmp(argv[i], "--output") == 0) {
            if (file != NULL || argv[i + 1][0] == '\0') {
                fprintf(stderr, "Invalid or duplicate --output option.\n");
                return EXIT_FAILURE;
            }
            file = argv[i + 1];
            continue;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }

        if (*present || !parse_positive_int(argv[i + 1], number)) {
            fprintf(stderr, "Invalid or duplicate value for %s.\n", argv[i]);
            return EXIT_FAILURE;
        }
        *present = 1;
    }

    if (!have_min_size || !have_max_size || !have_size_incr ||
        !have_n_perms || !have_n_keys || !have_generator || !have_order ||
        !have_method ||
        file == NULL || min_size > max_size) {
        fprintf(stderr,
                "Invalid or missing options; ensure min-size <= max-size "
                "and provide --order and --method.\n");
        return EXIT_FAILURE;
    }

    if ((method == bin_search && order != SORTED) ||
        (method == lin_auto_search && order != NOT_SORTED)) {
        fprintf(stderr,
                "Binary search requires sorted order; auto search requires unsorted order.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    if (generate_search_times(method, order, file,
                              min_size, max_size, size_incr, n_perms,
                              generator, n_keys) == ERR) {
        fprintf(stderr, "Failed to measure search performance.\n");
        return EXIT_FAILURE;
    }

    printf("Search measurements written to %s.\n", file);
    return EXIT_SUCCESS;
}
