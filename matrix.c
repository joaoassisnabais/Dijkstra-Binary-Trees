/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   matrix.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"

void printMatrix(double* matrix, int nv) {
    for(int i = 0; i < nv; i++) {
        for(int j = 0; j < nv; j++) {
            if(i != j)
                printf("%.2f ",matrix[AccessM(i, j)]);
            else
                printf("0.00 ");
        }
        printf("\n");
    }
}

int AccessM(int va, int vb){
    int result, min, max;

    if (va > vb){
        min=vb;
        max=va;
    }else{
        min=va;
        max=vb;
    }
    result= min + max*(max-1)/2;
    return result;
}

void createMandV(graph* g, int numV){
    g->matrix = (double*) malloc(sizeof(double)*(numV*(numV-1)/2));
    g->c = malloc(sizeof(g->c)*numV*27);
    return;
}

void IniMatrix(double* matrix, int numV){
    int max=numV*(numV-1)/2;
    for(int i=0; i<max; i++) matrix[i]=0;
}