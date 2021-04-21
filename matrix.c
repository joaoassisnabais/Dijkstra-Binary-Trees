/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   matrix.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
//#include "problems.h"

int AccessM(int va, int vb){
    int result, min, max;

    if (va > vb){
        min=vb-1;
        max=va-1;
    }else{
        min=va-1;
        max=vb-1;
    }
    result= min + max*(max-1)/2;
    return result;
}

void createMandV(graph* g, int numV){
    g->matrix = (double*) malloc(sizeof(double)*(numV*(numV-1)/2));
    g->c = (char*) malloc(sizeof(char)*numV*26);
    return;
}

void IniMatrix(double* matrix, int numV){
    int max=numV*(numV-1)/2;
    for(int i=0; i<max; i++) matrix[i]=0;
}