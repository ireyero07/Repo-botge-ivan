/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Jorge Torrijos de la Cruz e Ivan Reyero Fernández
 * Version: 1.0
 * Fecha: 25-11-2026
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#include "times.h"
#include "search.h"
#include "permutations.h"


/*********************************************************************************/
/* Function: generate_search_times                        Date: 25/11/2026       */
/* Authors: Ivan Reyero Fernández                                                */
/*                                                                               */
/* Measures search performance across a range of dictionary sizes and writes     */
/* one result row per size to file.                                              */
/*                                                                               */
/* Input:                                                                        */
/* pfunc_search method: Search algorithm to measure.                             */
/* char order: SORTED or NOT_SORTED dictionary order.                            */
/* char *file: Output path for the measurement table.                            */
/* int min_size: First dictionary size to measure.                               */
/* int max_size: Maximum dictionary size to measure.                             */
/* int size_incr: Increment between dictionary sizes.                            */
/* int n_perms: Number of dictionary permutations to average over.               */
/* pfunc_key_generator generator: Generates search keys in [1, dictionary size]. */
/* int n_keys: Number of generated queries per dictionary entry.                 */
/* Output:                                                                       */
/* short: OK on success; ERR if arguments, allocation, measurement, or writing   */
/*        fails.                                                                 */
/*********************************************************************************/
short generate_search_times(pfunc_search method, char order, char *file, int min_size, int max_size, int size_incr, int n_perms, pfunc_key_generator generator, int n_keys)
{
    int size, k, num_times;
    PTIME_AA p = NULL;

    /* Comprobar los parámetros de entrada */
    if (method == NULL || file == NULL || generator == NULL || (order != SORTED && order != NOT_SORTED) || min_size <= 0 || min_size > max_size || size_incr <= 0 || n_perms <= 0 || n_keys <= 0) {
        return ERR;
    }

    num_times = ((max_size - min_size) / size_incr) + 1;

    p = (PTIME_AA)malloc(num_times * sizeof(TIME_AA));
    if (p == NULL) {
        return ERR;
    }

    for (size = min_size, k = 0; size <= max_size; size += size_incr, k++) {
        if (average_search_time(method, order, size, n_perms, generator, n_keys, &p[k]) == ERR) {
            free(p);
            return ERR;
        }
    }

    if (save_time_table(file, p, num_times) == ERR) {
        free(p);
        return ERR;
    }

    free(p);
    return OK;
}

/*********************************************************************************/
/* Function: average_search_time                          Date: 25/11/2026       */
/* Authors: Ivan Reyero Fernández                                                */
/*                                                                               */
/* Measures searches in one randomly permuted dictionary.                        */
/*                                                                               */
/* Input:                                                                        */
/* pfunc_search method: Search algorithm to measure.                             */
/* char order: SORTED or NOT_SORTED dictionary order.                            */
/* int size: Number of dictionary entries.                                       */
/* int n_perms: Number of dictionary permutations to average over.               */
/* pfunc_key_generator generator: Generates search keys in [1, size].            */
/* int n_keys: Number of generated queries per dictionary entry.                 */
/* PTIME_AA ptime: Receives dictionary size, search count, elapsed time, and     */
/*                 minimum, maximum, and average basic-operation counts.         */
/* Output:                                                                       */
/* short: OK on success; ERR if arguments, allocation, measurement, or timing    */
/*        fails.                                                                 */
/*********************************************************************************/
short average_search_time(pfunc_search method, char order, int size, int n_perms, pfunc_key_generator generator, int n_keys, PTIME_AA ptime) 
{
    int **permutations = NULL;
    PDICT *dictionaries = NULL;
    int *keys = NULL;
    int i, j, k;
    int pos, ob;
    int min_ob = INT_MAX;
    int max_ob = 0;
    long long total_ob = 0;
    long long total_searches;
    clock_t start, end;

    /* Comprobar los parámetros de entrada */
    if (method == NULL || generator == NULL || ptime == NULL || size <= 0 || n_perms <= 0 || n_keys <= 0 || (order != SORTED && order != NOT_SORTED)) {
        return ERR;
    }

    /* Calcular el número total de búsquedas */
    total_searches = (long long)n_perms * n_keys;
    if (total_searches > INT_MAX) {
        return ERR;
    }

    /* 1. Generar las permutaciones */
    permutations = generate_permutations(n_perms, size);
    if (permutations == NULL) {
        return ERR;
    }

    /* 2. Reservar espacio para los diccionarios */
    dictionaries = (PDICT *)calloc(n_perms, sizeof(PDICT));
    if (dictionaries == NULL) {
        for (i = 0; i < n_perms; i++) {
            free(permutations[i]);
        }
        free(permutations);
        return ERR;
    }

    /* 3. Crear y rellenar los diccionarios */
    for (i = 0; i < n_perms; i++) {
        dictionaries[i] = init_dictionary(size, order);
        if (dictionaries[i] == NULL || massive_insertion_dictionary(dictionaries[i], permutations[i], size) == ERR) {
            for (k = 0; k <= i; k++) {
                if (dictionaries[k] != NULL) {
                    free_dictionary(dictionaries[k]);
                }
            }
            free(dictionaries);
            for (k = 0; k < n_perms; k++) {
                free(permutations[k]);
            }
            free(permutations);
            return ERR;
        }
    }

    /* 4. Generar las claves de búsqueda */
    keys = (int *)malloc(n_keys * sizeof(int));
    if (keys == NULL) {
        for (i = 0; i < n_perms; i++) {
            free_dictionary(dictionaries[i]);
            free(permutations[i]);
        }
        free(dictionaries);
        free(permutations);
        return ERR;
    }
    generator(keys, n_keys, size);

    /* 5. Iniciar el cronómetro y realizar las búsquedas */
    start = clock();
    if (start == (clock_t)-1) {
        free(keys);
        for (i = 0; i < n_perms; i++) {
            free_dictionary(dictionaries[i]);
            free(permutations[i]);
        }
        free(dictionaries);
        free(permutations);
        return ERR;
    }

    for (i = 0; i < n_perms; i++) {
        for (j = 0; j < n_keys; j++) {
            ob = search_dictionary(dictionaries[i], keys[j], &pos, method);

            /* Comprobar si la búsqueda ha sido correcta */
            if (ob == ERR || pos == NOT_FOUND) {
                free(keys);
                for (k = 0; k < n_perms; k++) {
                    free_dictionary(dictionaries[k]);
                    free(permutations[k]);
                }
                free(dictionaries);
                free(permutations);
                return ERR;
            }

            /* 6. Acumular las operaciones básicas */
            total_ob += ob;
            if (ob < min_ob) {
                min_ob = ob;
            }
            if (ob > max_ob) {
                max_ob = ob;
            }
        }
    }

    /* 7. Detener el cronómetro y calcular los resultados */
    end = clock();
    if (end == (clock_t)-1) {
        free(keys);
        for (i = 0; i < n_perms; i++) {
            free_dictionary(dictionaries[i]);
            free(permutations[i]);
        }
        free(dictionaries);
        free(permutations);
        return ERR;
    }

    ptime->size = size;
    ptime->n_elems = (int)total_searches;
    ptime->time = ((double)(end - start) / CLOCKS_PER_SEC) / total_searches;
    ptime->average_ob = (double)total_ob / total_searches;
    ptime->min_ob = min_ob;
    ptime->max_ob = max_ob;

    /* 8. Liberar la memoria reservada */
    free(keys);
    for (i = 0; i < n_perms; i++) {
        free_dictionary(dictionaries[i]);
        free(permutations[i]);
    }
    free(dictionaries);
    free(permutations);

    return OK;
}

/*********************************************************************************/
/* Function: save_time_table                              Date: 25/11/2026       */
/* Authors: Ivan Reyero Fernández                                                */
/*                                                                               */
/* Writes measurement records as five whitespace-separated columns:              */
/* dictionary size, elapsed seconds, average operations, maximum operations,     */
/* and minimum operations.                                                       */
/*                                                                               */
/* Input:                                                                        */
/* char *file: Output path.                                                      */
/* PTIME_AA times: Array of measurement records.                                 */
/* int n_times: Number of records in times.                                      */
/* Output:                                                                       */
/* short: OK on success; ERR if arguments or file operations fail.               */
/*********************************************************************************/
short save_time_table(char *file, PTIME_AA times, int n_times) 
{
    FILE *f = NULL;
    int i;

    if (file == NULL || times == NULL || n_times <= 0) {
        return ERR;
    }

    f = fopen(file, "w");
    if (f == NULL) {
        return ERR;
    }

    for (i = 0; i < n_times; i++) {
        if (fprintf(f, "%d\t%.9f\t%f\t%d\t%d\n", times[i].size, times[i].time, times[i].average_ob, times[i].max_ob, times[i].min_ob) < 0) {
            fclose(f);
            return ERR;
        }
    }

    if (fclose(f) != 0) {
        return ERR;
    }

    return OK;
}
