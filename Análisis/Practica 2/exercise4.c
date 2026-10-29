/**************************************************/
/* Programa: exercise4                            */
/* Authors: Jorge Torrijos e Ivan Reyero          */
/*                                                */
/* Program that checks QuickSort_median           */
/*                                                */
/* Input: Command Line                            */
/* -size: number of elements in the permutation   */
/* Output: Sorted permutation and number of OB    */
/**************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char **argv)
{
    int tamano, i, ret_Quick;
    int *perm = NULL;

    srand(time(NULL));

    if (argc != 3 || strcmp(argv[1], "-size") != 0) {
        fprintf(stderr, "Error in input parameters:\n");
        fprintf(stderr, "%s -size <int>\n", argv[0]);
        return ERR;
    }

    tamano = atoi(argv[2]);

    if (tamano <= 0) {
        fprintf(stderr, "Error: size must be positive\n");
        return ERR;
    }

    printf("Practice number 2, section 4\n");
    printf("Done by: Ivan Reyero y Jorge Torrijos\n");
    printf("Group: 1261-10\n");

    perm = generate_perm(tamano);

    if (perm == NULL) {
        fprintf(stderr, "Error: Out of memory\n");
        return ERR;
    }

    printf("\nOriginal permutation:\n");
    for (i = 0; i < tamano; i++) {
        printf("%d\t", perm[i]);
    }

    ret_Quick = QuickSort_median(perm, 0, tamano - 1);

    if (ret_Quick == ERR) {
        fprintf(stderr, "\nError in QuickSort_median\n");
        free(perm);
        return ERR;
    }

    printf("\n\nQuickSort_median:\n");
    for (i = 0; i < tamano; i++) {
        printf("%d\t", perm[i]);
    }

    printf("\nOB QuickSort_median: %d\n", ret_Quick);

    free(perm);

    return 0;
}