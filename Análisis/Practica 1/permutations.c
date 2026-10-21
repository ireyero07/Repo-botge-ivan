/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random number           */
/* between two given numbers                       */
/*                                                 */
/* Input:                                          */
/* int inf: lower limit                            */
/* int sup: upper limit                            */
/* Output:                                         */
/* int: random number                              */
/***************************************************/
int random_num(int inf, int sup)
{
  int resultado;
  long rango;

  if (inf < 0 || sup < inf) {
    return ERR;
  }

  rango = (long)sup - (long)inf + 1;
    
  if (rango > (long)RAND_MAX + 1) {
    return ERR;
  }
  
  resultado = inf + (rand() % rango);
    
  return resultado;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int *generate_perm(int N)
{
  int *perm;
  int i, j, aux;

  if (N <= 0) {
    return NULL;
  }

  perm = (int *)malloc(N * sizeof(int));

  if (perm == NULL) {
    return NULL;
  }

  for (i = 0; i < N; i++) {
    perm[i] = i + 1;
  }

  for (i = 0; i < N; i++) {
    j = random_num(i, N - 1);

    if (j == ERR) {
      free(perm);
      return NULL;
    }

    aux = perm[i];
    perm[i] = perm[j];
    perm[j] = aux;
    }

    return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int **permutations;
  int i, j;

  if (n_perms <= 0 || N <= 0) {
    return NULL;
  }

  permutations = (int **)malloc(n_perms * sizeof(int *));

  if (permutations == NULL) {
    return NULL;
  }

  for (i = 0; i < n_perms; i++) {
    permutations[i] = generate_perm(N);

    if (permutations[i] == NULL) {

      for (j = 0; j < i; j++) {
        free(permutations[j]);
      }

      free(permutations);

      return NULL;
    }
  }

  return permutations;
}
