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
/* int ip: index of first position  			         */
/* int iu: index of last position			             */
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
    OB = MergeSort(array, ip, iu);
    OB += MergeSort(array, ip + 1, iu);
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
/* int ip: index of first position  			         */
/* int iu: index of last position			             */
/* int im: index of last position of the left 		 */
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

  aux = (int *)malloc(sizeof(int) * iu - ip + 1);
  if (!aux)
  {
    return ERR;
  }

  i = ip;
  j = im + 1;
  k = ip;

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
  if (i > im)
  {
    while (j <= iu)
    {
      aux[k] = array[j];
      j++;
      k++;
    }
  }
  else if (j < iu)
  {
    while (i <= im)
    {
      aux[k] = array[i];
      i++;
      k++;
    }
  }

  for (q = ip, l= 0; q < iu; q++, l++)
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
/* int ip: index of first position  			         */
/* int iu: index of last position			             */
/* int im: index of last position of the left 		 */
/* partition                                       */
/* Output:                                         */
/* int: Number of times the basic operation has    */
/*  been made                                      */
/***************************************************/
int partition(int *array, int ip, int iu, int *pos, pfunc_pivot pivot)
{
  return -1;
}

/***************************************************/
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
/*                                                 */
/* Input:                                          */
/* int *array: Array with permutations             */
/* int ip: index of first position  			         */
/* int iu: index of last position			             */
/* int im: index of last position of the left 		 */
/* partition                                       */
/* Output:                                         */
/* int: Number of times the basic operation has    */
/*  been made                                      */
/***************************************************/
int QuickSort_min(int *array, int ip, int iu)
{
  int m;
  int *pos = NULL;
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
    m = partition(array, ip, iu, pos, pivot_min);
    if (ip < m - 1)
    {
      QuickSort_min(array, ip, m - 1);
    }
    else if (m + 1 < iu)
    {
      QuickSort_min(array, m + 1, iu);
    }
  }

  return OK;
}

/***************************************************/
/* Function: Merge         Date:29/09/2026         */
/* Authors: Jorge Torrijos                         */
/*                                                 */
/* Subfunction to sort the list                    */
/*                                                 */
/* Input:                                          */
/* int *array: Array with permutations             */
/* int ip: index of first position  			         */
/* int iu: index of last position			             */
/* int im: index of last position of the left 		 */
/* partition                                       */
/* Output:                                         */
/* int: Number of times the basic operation has    */
/*  been made                                      */
/***************************************************/
int pivot_min(int *array, int ip, int iu, int *pos)
{
  return 1;
}