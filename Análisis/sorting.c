/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "sorting.h"

/***************************************************/
/* Function: InsertSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int InsertSort(int *array, int ip, int iu)
{
  int c = 0, i, j = 0, A = 0;

  if (!array || ip < 0 || ip > iu)
  {
    return ERR;
  }
  
  for (i = ip + 1; i <= iu; i++)
  {
    A = array[i];
    j = i - 1;
    while (j >= ip)
    {
      c++; 
      if (array[j] > A)
      {
        array[j + 1] = array[j];
        j--;
      }
      else
      {
        break; 
      }
    }
    array[j + 1] = A;
  }

  return c;
}

/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
/*int BubbleSort(int* array, int ip, int iu)
{

}*/
