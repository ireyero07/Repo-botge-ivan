/**
 *
 * Descriptions: Declarations of the search functions and data
 *
 * File: search.h
 */

#ifndef SEARCH_H_
#define SEARCH_H_

#ifndef ERR
#define ERR -1
#define OK (!ERR)
#endif

#define NOT_FOUND -2

#define SORTED 1
#define NOT_SORTED 0

typedef struct dictionary {
    int size;
    int n_data;
    char order;
    int *table;
} DICT, *PDICT;

typedef int (*pfunc_search)(int *, int, int, int, int *);
typedef void (*pfunc_key_generator)(int *, int, int);

/**
 * Initializes a dictionary with the requested capacity and sorting policy.
 *
 * @param size Maximum number of elements the dictionary can store.
 * @param order SORTED if the table must remain ordered, otherwise NOT_SORTED.
 * @return A newly allocated dictionary or NULL if memory or arguments are invalid.
 */
PDICT init_dictionary(int size, char order);

/**
 * Releases the memory allocated for a dictionary.
 *
 * @param pdict Dictionary to free; may be NULL.
 */
void free_dictionary(PDICT pdict);

/**
 * Inserts a key into the dictionary.
 *
 * @param pdict Dictionary to update.
 * @param key Value to store.
 * @return Number of operations performed when the insertion succeeds; ERR otherwise.
 */
int insert_dictionary(PDICT pdict, int key);

/**
 * Inserts an array of keys into the dictionary in sequence.
 *
 * @param pdict Dictionary to update.
 * @param keys Array of numeric keys to store.
 * @param n_keys Number of keys in the array.
 * @return Total number of operations performed or ERR if the insertion fails.
 */
int massive_insertion_dictionary(PDICT pdict, int *keys, int n_keys);

/**
 * Searches for a key in the dictionary using a caller-provided search method.
 *
 * @param pdict Dictionary to search.
 * @param key Key to locate.
 * @param ppos Output pointer receiving the index of the found key or NOT_FOUND.
 * @param method Function implementing the search strategy.
 * @return Number of operations performed by the search or ERR on invalid input.
 */
int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method);

/**
 * Performs a binary search in a sorted table.
 *
 * @param table Array to search.
 * @param F Lower-bound index of the search interval.
 * @param L Upper-bound index of the search interval.
 * @param key Key being searched.
 * @param ppos Output pointer receiving the key position or NOT_FOUND.
 * @return Number of comparisons performed.
 */
int bin_search(int *table, int F, int L, int key, int *ppos);

/**
 * Performs a linear search in a table interval.
 *
 * @param table Array to search.
 * @param F Lower-bound index of the search interval.
 * @param L Upper-bound index of the search interval.
 * @param key Key being searched.
 * @param ppos Output pointer receiving the key position or NOT_FOUND.
 * @return Number of comparisons performed.
 */
int lin_search(int *table, int F, int L, int key, int *ppos);

/**
 * Performs a linear search that moves a found key one position closer to the front.
 *
 * @param table Array to search.
 * @param F Lower-bound index of the search interval.
 * @param L Upper-bound index of the search interval.
 * @param key Key being searched.
 * @param ppos Output pointer receiving the final key position or NOT_FOUND.
 * @return Number of comparisons performed.
 */
int lin_auto_search(int *table, int F, int L, int key, int *ppos);

/**
 * Fills an array with pseudo-random integer values uniformly distributed in [1, max].
 *
 * @param keys Output array that receives generated keys.
 * @param n_keys Number of values to generate.
 * @param max Maximum key value included in the range.
 */
void uniform_key_generator(int *keys, int n_keys, int max);

/**
 * Fills an array with keys following an approximate power-law distribution.
 *
 * @param keys Output array that receives generated keys.
 * @param n_keys Number of values to generate.
 * @param max Maximum key value included in the range.
 */
void potential_key_generator(int *keys, int n_keys, int max);

/**
 * Fills an array with keys following a Gaussian-like distribution centered around the midpoint.
 *
 * @param keys Output array that receives generated keys.
 * @param n_keys Number of values to generate.
 * @param max Maximum key value included in the range.
 */
void gaussian_key_generator(int *keys, int n_keys, int max);

#endif
