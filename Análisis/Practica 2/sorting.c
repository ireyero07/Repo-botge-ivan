/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Jorge Torrijos e Ivan Reyero Fernández
 * Version: 1.0
 * Fecha: 16-09-2026
 *
 */

#include "sorting.h"
#include "stdlib.h"
#include "string.h"

/***************************************************/
/* Function: MergeSort         Date:21/10/2026     */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Function that  sorts a list via merging while   */
/*  while sorting the list                         */
/* Input:                                          */
/* int *array: Array with permutations             */
/* int ip: index of first position                 */
/* int iu: index of last position                  */
/* Output:                                         */
/* int: Number of times the basic operation has    */
/*  been made                                      */
/***************************************************/
int MergeSort(int *array, int ip, int iu)
{
  int h, OB = 0;
  if (!array || ip < 0 || ip > iu)
  {
    return ERR;
  }

  if (ip == iu)
  {
    return OK;
  }

  else
  {
    h = (ip + iu) / 2;
    OB = MergeSort(array, ip, h);
    OB += MergeSort(array, h + 1, iu);
  }

  OB += merge(array, ip, iu, h);
  return OB;
}

/***************************************************/
/* Function: Merge             Date:28/10/2026     */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to merge the list                   */
/*                                                 */
/* Input:                                          */
/* int *array: Array with permutations             */
/* int ip: index of first position                 */
/* int iu: index of last position                  */
/* int im: index of last position of the left      */
/* partition                                       */
/* Output:                                         */
/* int: Number of times the basic operation has    */
/*  been made                                      */
/***************************************************/
int merge(int *array, int ip, int iu, int im)
{
  int i, j, k, q, l, OB = 0;
  int *aux = NULL;
  if (!array || ip < 0 || ip > iu)
  {
    return ERR;
  }

  aux = (int *)malloc(sizeof(int) * (iu - ip + 1));
  if (!aux)
  {
    return ERR;
  }

  i = ip;
  j = im + 1;
  k = 0;

  while (i <= im && j <= iu)
  {
    if (array[i] < array[j])
    {
      aux[k] = array[i];
      i++;
    }
    else
    {
      aux[k] = array[j];
      j++;
    }
    OB++;
    k++;
  }

  while (i <= im)
  {
    aux[k] = array[i];
    i++;
    k++;
  }

  while (j <= iu)
  {
    aux[k] = array[j];
    j++;
    k++;
  }

  for (q = ip, l = 0; q <= iu; q++, l++)
  {
    array[q] = aux[l];
  }

  free(aux);
  return OB;
}

/***************************************************/
/* Function: partition         Date:21/10/2026     */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Partitions the array segment around a pivot     */
/* chosen by the 'pivot' function strategy.        */
/*                                                 */
/* Input:                                          */
/* int *array: Array to be partitioned             */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* int *pos: Pointer to store the final pivot index*/
/* pfunc_pivot pivot: Function pointer to selector */
/* Output:                                         */
/* int: Total basic operations (OB) performed      */
/***************************************************/
int partition(int *array, int ip, int iu, int *pos, pfunc_pivot pivot)
{
  int i, m, count, key, temp, pivot_count;

  if (array == NULL || pos == NULL || pivot == NULL || ip < 0 || ip > iu)
    return ERR;

  pivot_count = pivot(array, ip, iu, pos);

  if (pivot_count == ERR || *pos < ip || *pos > iu)
    return ERR;

  temp = array[ip];
  array[ip] = array[*pos];
  array[*pos] = temp;

  key = array[ip];
  m = ip;
  count = pivot_count;

  for (i = ip + 1; i <= iu; i++) {
    count++;
    if (array[i] < key) {
      m++;
      temp = array[m];
      array[m] = array[i];
      array[i] = temp;
    }
  }

  temp = array[ip];
  array[ip] = array[m];
  array[m] = temp;

  *pos = m;

  return count;
}

/***************************************************/
/* Function: QuickSort_min     Date:21/10/2026     */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Sorts the array segment using QuickSort         */
/* selecting the first element as the pivot.       */
/*                                                 */
/* Input:                                          */
/* int *array: Array to be sorted                  */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* Output:                                         */
/* int: Total basic operations (OB) performed      */
/***************************************************/
int QuickSort_min(int *array, int ip, int iu)
{
  int pos, count, left_count, right_count;
  if (!array || ip < 0)
  {
    return ERR;
  }

  if (ip >= iu)
  {
    return OK;
  }

  count = partition(array, ip, iu, &pos, pivot_min);

  if (count == ERR)
  {
    return ERR;
  }

  left_count = QuickSort_min(array, ip, pos - 1);
  if (left_count == ERR)
  {
    return ERR;
  }

  right_count = QuickSort_min(array, pos + 1, iu);
  if (right_count == ERR)
  {
    return ERR;
  }

  return count + left_count + right_count;
}

/***************************************************/
/* Function: QuickSort_mean     Date:28/10/2026    */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Sorts the array segment using QuickSort         */
/* selecting the middle element as the pivot.      */
/*                                                 */
/* Input:                                          */
/* int *array: Array to be sorted                  */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* Output:                                         */
/* int: Total basic operations (OB) performed      */
/***************************************************/
int QuickSort_mean(int* array, int ip, int iu)
{
  int pos, count, left_count, right_count;
  if (!array || ip < 0)
  {
    return ERR;
  }

  if (ip >= iu)
  {
    return OK;
  }

  count = partition(array, ip, iu, &pos, pivot_mean);

  if (count == ERR)
  {
    return ERR;
  }

  left_count = QuickSort_mean(array, ip, pos - 1);
  if (left_count == ERR)
  {
    return ERR;
  }

  right_count = QuickSort_mean(array, pos + 1, iu);
  if (right_count == ERR)
  {
    return ERR;
  }

  return count + left_count + right_count;
}

/***************************************************/
/* Function: QuickSort_median     Date:28/10/2026  */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Sorts the array segment using QuickSort         */
/* selecting the median of three elements as pivot.*/
/*                                                 */
/* Input:                                          */
/* int *array: Array to be sorted                  */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* Output:                                         */
/* int: Total basic operations (OB) performed      */
/***************************************************/
int QuickSort_median(int* array, int ip, int iu)
{
  int pos, count, left_count, right_count;
  if (!array || ip < 0)
  {
    return ERR;
  }

  if (ip >= iu)
  {
    return OK;
  }

  count = partition(array, ip, iu, &pos, pivot_median);

  if (count == ERR)
  {
    return ERR;
  }

  left_count = QuickSort_median(array, ip, pos - 1);
  if (left_count == ERR)
  {
    return ERR;
  }

  right_count = QuickSort_median(array, pos + 1, iu);
  if (right_count == ERR)
  {
    return ERR;
  }

  return count + left_count + right_count;
}

/***************************************************/
/* Function: pivot_min         Date:21/10/2026     */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Selects the first index of the segment as pivot.*/
/* Does not perform key comparisons.               */
/*                                                 */
/* Input:                                          */
/* int *array: Array of elements                   */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* int *pos: Pointer to store the selected index   */
/* Output:                                         */
/* int: Number of key comparisons (always 0)       */
/***************************************************/
int pivot_min(int *array, int ip, int iu, int *pos)
{
  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

  *pos = ip;

  return 0;
}

/***************************************************/
/* Function: pivot_mean        Date:28/10/2026     */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Selects the middle index of the segment as pivot*/
/* preventing integer overflow. No comparisons.    */
/*                                                 */
/* Input:                                          */
/* int *array: Array of elements                   */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* int *pos: Pointer to store the selected index   */
/* Output:                                         */
/* int: Number of key comparisons (always 0)       */
/***************************************************/
int pivot_mean(int* array, int ip, int iu, int* pos)
{
  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

  *pos = ip + (iu - ip) / 2;

  return 0;
}

/***************************************************/
/* Function: pivot_median      Date:28/10/2026     */
/* Authors: Iván Reyero                            */
/*                                                 */
/* Selects as pivot the median value between the   */
/* first, middle, and last elements of the segment.*/
/*                                                 */
/* Input:                                          */
/* int *array: Array of elements                   */
/* int ip: Index of the first position             */
/* int iu: Index of the last position              */
/* int *pos: Pointer to store the selected index   */
/* Output:                                         */
/* int: Number of key comparisons performed (2-3)  */
/***************************************************/
int pivot_median(int* array, int ip, int iu, int* pos)
{
  int medio;
  int comps = 0;

  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

  medio = ip + (iu - ip) / 2;

  comps++;
  if (array[ip] < array[medio]) {
    comps++;

    if (array[medio] < array[iu]) {
      *pos = medio;

    } else {
      comps++;

      if (array[ip] < array[iu]) {
        *pos = iu;

      } else {
        *pos = ip;
      }
    }

  } else {
    comps++;

    if (array[iu] < array[medio]) {
      *pos = medio;

    } else {
      comps++;

      if (array[iu] < array[ip]) {
        *pos = iu;

      } else {
        *pos = ip;
      }
    }
  }

  return comps;
}
