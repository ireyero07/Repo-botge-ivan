#ifndef GEN_H_
#define GEN_H_

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
