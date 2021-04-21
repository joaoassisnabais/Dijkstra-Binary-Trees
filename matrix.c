/******************************************************************************
 * (c) 2021 João Nabais & João Nabais
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

void createMatrix(graph* g, int numV){

    g->matrix = (double*) malloc(sizeof(double)*(numV*(numV - 1)/2));

    return;
}