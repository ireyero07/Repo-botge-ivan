/**
 * Declarations for search timing and result-file functions.
 */

#ifndef TIMES_H
#define TIMES_H

#ifndef ERR
#define ERR -1
#define OK (!(ERR))
#endif

#include "search.h"

typedef struct {
    int size;           /* Dictionary size. */
    int n_elems;        /* Number of searches performed. */
    double time;        /* Total elapsed search time in seconds. */
    double average_ob;  /* Average basic-operation count per search. */
    int min_ob;         /* Minimum basic-operation count. */
    int max_ob;         /* Maximum basic-operation count. */
} TIME_AA, *PTIME_AA;

/**
 * Measures search performance across a range of dictionary sizes and writes
 * one result row per size to file.
 *
 * @param method Search algorithm to measure.
 * @param order SORTED or NOT_SORTED dictionary order.
 * @param file Output path for the measurement table.
 * @param min_size First dictionary size to measure.
 * @param max_size Maximum dictionary size to measure.
 * @param size_incr Increment between dictionary sizes.
 * @param n_perms Number of dictionary permutations to average over.
 * @param generator Generates search keys in [1, dictionary size].
 * @param n_keys Number of generated queries per dictionary entry.
 * @return OK on success; ERR if arguments, allocation, measurement, or writing
 *         fails.
 */
short generate_search_times(pfunc_search method,
                            char order,
                            char *file,
                            int min_size,
                            int max_size,
                            int size_incr,
                            int n_perms,
                            pfunc_key_generator generator,
                            int n_keys);

/**
 * Measures searches in one randomly permuted dictionary.
 *
 * @param method Search algorithm to measure.
 * @param order SORTED or NOT_SORTED dictionary order.
 * @param size Number of dictionary entries.
 * @param n_perms Number of dictionary permutations to average over.
 * @param generator Generates search keys in [1, size].
 * @param n_keys Number of generated queries per dictionary entry.
 * @param ptime Receives dictionary size, search count, elapsed time, and
 *              minimum, maximum, and average basic-operation counts.
 * @return OK on success; ERR if arguments, allocation, measurement, or timing
 *         fails.
 */
short average_search_time(pfunc_search method,
                          char order,
                          int size,
                          int n_perms,
                          pfunc_key_generator generator,
                          int n_keys,
                          PTIME_AA ptime);

/**
 * Writes measurement records as five whitespace-separated columns:
 * dictionary size, elapsed seconds, average operations, maximum operations,
 * and minimum operations.
 *
 * @param file Output path.
 * @param times Array of measurement records.
 * @param n_times Number of records in times.
 * @return OK on success; ERR if arguments or file operations fail.
 */
short save_time_table(char *file,
                      PTIME_AA times,
                      int n_times);

#endif
