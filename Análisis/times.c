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
  /*Ivan he comentado la función porque es compleja y va a venir bien para los ejercicios*/
  double t;
  clock_t start, end;
  int **aux = NULL;
  int i, ob;

  /*Chequeo de errores*/
  if (!metodo || n_perms < 0 || N < 0 || !ptime)
  {
    return ERR;
  }

  /*Creacion de las permutaciones, no hace falta pedir memoria dinámica porque ya lo hace la función :)*/
  aux = generate_permutations(n_perms, N);
  if (!aux)
  {
    return ERR;
  }

  /*Comienza el reloj con start, comienza la organización y cierra con end*/
  start = clock();
  for (i = 0; i < n_perms; i++)
  {
    ob = metodo(aux[i], 0, N - 1);

    if (ob == ERR)
    {
      for (i = 0; i < n_perms; i++)
      {
        free(aux[i]);
      }
      free(aux);
      return ERR;
    }
    t += ob;

    /*Comienza con el caso cero, ya que si i no ha avanzado n_perms = 2 y ya esta ordenado (No se si n_perms podría tambien ser 1) y el min y el max son ob*/
    if (i == 0)
    {
      ptime->min_ob = ob;
      ptime->max_ob = ob;
    }
    /*Al no ser 0 tiene que hacer la comparación para asignar*/
    else
    {
      if (ob < ptime->min_ob)
      {
        ptime->min_ob = ob;
      }

      if (ob > ptime->max_ob)
      {
        ptime->max_ob = ob;
      }
    }
    end = clock();
  }

  /*Una vez calculado asigna los valores, end-start es para calcular el tiempo transcurrido y clocks_per_sec es la conversion a segundos*/
  ptime->n_elems = n_perms;
  ptime->N = N;
  ptime->time = ((end - start) / CLOCKS_PER_SEC) / n_perms;
  ptime->average_ob = t / n_perms;

  /*Liberación de memoria*/
  for (i = 0; i < n_perms; i++)
  {
    free(aux[i]);
  }
  free(aux);
  return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char *file,
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

  p = (PTIME_AA *)malloc(sizeof(PTIME_AA));
  if (!p)
  {
    return ERR;
  }

  N = num_min + k * incr;
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
short save_time_table(char *file, PTIME_AA time, int n_times)
{
  FILE *f;
  int i;

  if (file == NULL || time == NULL || n_times <= 0)
  {
    return ERR;
  }

  f = fopen(file, "w");

  if (f == NULL)
  {
    return ERR;
  }

  fprintf(f, "N\tn_elems\ttime\taverage_ob\tmin_ob\tmax_ob\n");

  for (i = 0; i < n_times; i++)
  {
    fprintf(f, "%d\t%d\t%f\t%f\t%d\t%d\n", time[i].N, time[i].n_elems, time[i].time, time[i].average_ob, time[i].min_ob, time[i].max_ob);
  }

  fclose(f);

  return OK;
}
