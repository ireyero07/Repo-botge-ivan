/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
  double time;
  clock_t clk;
  int *aux = NULL;
  int avg = 0, min = 0, max = 0;

  if (!metodo || n_perms < 0 || N < 0 || ! ptime)
  {
    return ERR;
  }

  aux = (int*) malloc(sizeof(int)*N);
  if (!aux)
  {
    return ERR;
  }

  aux = generate_permutations (n_perms, N);
  if (!aux)
  {
    return ERR;
  }

  ptime->n_elems = 
  ptime->N = N;

  free (aux);
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                            int num_min, int num_max, 
                            int incr, int n_perms)
{
  int N, k;
  short chek;
  PTIME_AA *p = NULL;
  if (!method || !file || 1 > num_min || num_min > num_max || incr < 0 || n_perms < 0)
  {
    return ERR;
  }

  p = (PTIME_AA*) malloc(sizeof(PTIME_AA));
  if (!p)
  {
    return ERR;
  }

  N = num_min + k*incr;
  while (N <= num_max)
  {
    chek = average_sorting_time(method, n_perms, N, p);
    if (chek == ERR)
    {
      return ERR;
    }
    if (save_time_table(file, p, N) == ERR)
    {
      return ERR;
    }
    k++;
  }

  free(p);
  return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  /* your code */
}


