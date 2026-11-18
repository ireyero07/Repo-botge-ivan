#include "gen.h"

#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define ALPHA 1.5
#define PI 3.14159265358979323846

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in n_keys.
 *               Generated keys range from 1 to max and are returned
 *               in the externally allocated keys array.
 */
  
/**
 *  Function: uniform_key_generator
 */

/* Entero uniforme en [1, max] */

void uniform_key_generator(int *keys, int n_keys, int max)
{
    if (!keys || n_keys <= 0 || max <= 0) return;

    for (int i = 0; i < n_keys; i++)
        keys[i] = 1 + (int)((double)rand() / ((double)RAND_MAX + 1.0) * max);
}

/**
 *  Function: potential_key_generator
 *               Generates keys following an approximate power-law distribution.
 */


/* Distribución potencial P(k) proporcional a k^(-ALPHA) */

void potential_key_generator(int *keys, int n_keys, int max)
{
    if (!keys || n_keys <= 0 || max <= 0) return;

    double total = 0.0;

    for (int k = 1; k <= max; k++)
        total += pow(k, -ALPHA);

    for (int i = 0; i < n_keys; i++) {
        double r = ((double) rand() / ((double) RAND_MAX + 1.0)) * total;
        double acumulado = 0.0;
        int k;

        for (k = 1; k < max; k++) {
            acumulado += pow(k, -ALPHA);
            if (r < acumulado)
                break;
        }

        keys[i] = k;
    }
}

/* Distribución gaussiana mediante Box-Muller */

void gaussian_key_generator(int *keys, int n_keys, int max)
{
    if (!keys || n_keys <= 0 || max <= 0) return;

    double mu = (max + 1.0) / 2.0;
    double sigma = max / 12.0;

    for (int i = 0; i < n_keys; i++) {
        double u1, u2, z, x;

        do {
            u1 = ((double)rand() + 1.0) / ((double) RAND_MAX + 1.0);
            u2 = (double)rand() / ((double) RAND_MAX + 1.0);

            z = sqrt(-2.0 * log(u1)) * cos(2.0 * PI * u2);
            x = mu + sigma * z;

        } while (x < 0.5 || x >= max + 0.5);

        keys[i] = (int) floor(x + 0.5);
    }
}
