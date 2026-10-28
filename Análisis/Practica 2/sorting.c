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
/* Function: MergeSort     Date:29/09/2026         */
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
/* Function: Merge         Date:29/09/2026         */
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
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
int QuickSort_mean(int* array, int ip, int iu)
{
  int m, pos, count, left_count, right_count;
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
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
int pivot_min(int *array, int ip, int iu, int *pos)
{
  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

  *pos = ip;

  return 0;
}

/***************************************************/
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
int pivot_mean(int* array, int ip, int iu, int* pos)
{
  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

  *pos = ip + (iu - ip) / 2;

  return 0;
}


/***************************************************/
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
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
int pivot_median(int* array, int ip, int iu, int* pos)
{
  if (array == NULL || pos == NULL || ip < 0 || ip > iu)
    return ERR;

}
