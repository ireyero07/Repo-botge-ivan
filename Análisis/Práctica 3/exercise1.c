#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
    int n_keys = 0, max = 0;
    int have_n_keys = 0, have_max = 0, have_generator = 0;
    int *keys;
    pfunc_key_generator generator = NULL;

    if (argc != 7) {
        fprintf(stderr,
                "Usage: %s --keys <positive-int> --max <positive-int> "
                "--generator <uniform|potential|gaussian>\n",
                argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc; i += 2) {
        if (strcmp(argv[i], "--keys") == 0 && !have_n_keys) {
            if (!parse_positive_int(argv[i + 1], &n_keys)) {
                fprintf(stderr, "--keys must be a positive integer.\n");
                return EXIT_FAILURE;
            }
            have_n_keys = 1;
        } else if (strcmp(argv[i], "--max") == 0 && !have_max) {
            if (!parse_positive_int(argv[i + 1], &max)) {
                fprintf(stderr, "--max must be a positive integer.\n");
                return EXIT_FAILURE;
            }
            have_max = 1;
        } else if (strcmp(argv[i], "--generator") == 0 &&
                   !have_generator) {
            if (strcmp(argv[i + 1], "uniform") == 0)
                generator = uniform_key_generator;
            else if (strcmp(argv[i + 1], "potential") == 0)
                generator = potential_key_generator;
            else if (strcmp(argv[i + 1], "gaussian") == 0)
                generator = gaussian_key_generator;
            else {
                fprintf(stderr,
                        "Invalid generator '%s'; use uniform, potential, "
                        "or gaussian.\n",
                        argv[i + 1]);
                return EXIT_FAILURE;
            }
            have_generator = 1;
        } else {
            fprintf(stderr, "Unknown or duplicate option: %s\n", argv[i]);
            return EXIT_FAILURE;
        }
    }

    if (!have_n_keys || !have_max || !have_generator) {
        fprintf(stderr,
                "Options --keys, --max, and --generator are required.\n");
        return EXIT_FAILURE;
    }

    if ((size_t)n_keys > SIZE_MAX / sizeof(*keys)) {
        fprintf(stderr, "--keys is too large.\n");
        return EXIT_FAILURE;
    }

    keys = malloc((size_t)n_keys * sizeof(*keys));
    if (keys == NULL) {
        fprintf(stderr, "Could not allocate memory for keys.\n");
        return EXIT_FAILURE;
    }

    srand((unsigned int)time(NULL));
    generator(keys, n_keys, max);

    for (int i = 0; i < n_keys; i++) {
        if (printf("%d\n", keys[i]) < 0) {
            fprintf(stderr, "Failed to write generated keys to stdout.\n");
            free(keys);
            return EXIT_FAILURE;
        }
    }

    free(keys);
    return EXIT_SUCCESS;
}
