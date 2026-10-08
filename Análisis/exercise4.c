/**************************************************/
/* Programa: ejercise4       Date:                */
/* Authors:                                       */
/*                                                */
/* Program that checks InsertSort                 */
/*                                                */
/* Input: Command Line                            */
/* -size: number of elements of each permutation  */
/* Output: 0: OK, -1: ERR                         */
/**************************************************/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "permutations.h"
#include "sorting.h"

int main(int argc, char** argv)
{
    int tamano, i, j;
    int ret_insert, ret_bubble;
    int *perm = NULL;
    int *perm_insert = NULL;
    int *perm_bubble = NULL;

    srand(time(NULL));

    if (argc != 3) {
        fprintf(stderr, "Error in input parameters:\n\n");
        fprintf(stderr, "%s -size <int>\n", argv[0]);
        fprintf(stderr, "Where:\n");
        fprintf(stderr, " -size : number of elements in the permutation.\n");
        return 0;
    }
    printf("Practice number 1, section 4\n");
    printf("Done by: Ivan Reyero y Jorge Torrijos\n");
    printf("Group: 1261-10\n");

    /* check command line */
    for(i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-size") == 0) {
            tamano = atoi(argv[++i]);
        } else {
            fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
        }
    }

    perm = generate_perm(tamano);

    if (perm == NULL) { /* error */
        printf("Error: Out of memory\n");
        exit(-1);
    }

    perm_insert = (int *)malloc(tamano * sizeof(int));
    perm_bubble = (int *)malloc(tamano * sizeof(int));

    if (perm_insert == NULL || perm_bubble == NULL) {
        printf("Error: Out of memory\n");

        free(perm);
        free(perm_insert);
        free(perm_bubble);

        exit(-1);
    }

    for (i = 0; i < tamano; i++) {
        perm_insert[i] = perm[i];
        perm_bubble[i] = perm[i];
    }

    ret_insert = InsertSort(perm_insert, 0, tamano - 1);

    if (ret_insert == ERR) {
        printf("Error: Error in InsertSort\n");

        free(perm);
        free(perm_insert);
        free(perm_bubble);

        exit(-1);
    }

    /* Sort the second copy with BubbleSort */
    ret_bubble = BubbleSort(perm_bubble, 0, tamano - 1);

    if (ret_bubble == ERR) {
        printf("Error: Error in BubbleSort\n");

        free(perm);
        free(perm_insert);
        free(perm_bubble);

        exit(-1);
    }

    /* Print InsertSort result */
    printf("\nInsertSort:\n");

    for (j = 0; j < tamano; j++) {
        printf("%d\t", perm_insert[j]);
    }

    printf("\nOB InsertSort: %d\n", ret_insert);

    /* Print BubbleSort result */
    printf("\nBubbleSort:\n");

    for (j = 0; j < tamano; j++) {
        printf("%d\t", perm_bubble[j]);
    }

    printf("\nOB BubbleSort: %d\n", ret_bubble);

    /* Free memory */
    free(perm);
    free(perm_insert);
    free(perm_bubble);

    return 0;
}

