/******************************************************************************
 * (c) 2021 João Nabais & João Nabais
 *
 * NAME
 *   graphs.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"

void createGraph(FILE* fp, graph* g){

    FILE* aux = fp;
    char* buffer, auxbuffer = NULL;
    int vexNumber, aNumber;
    
    fscanf("%d", vexNumber);
    fscanf("%d", aNumber);
    g->nv= (int*) malloc(sizeof(int));
    g->nv= vexNumber;
    g->na= (int*) malloc(sizeof(int));
    g->na= aNumber;
    createMatrix(g, g->nv);


    for (int i=0; i<vexNumber; i++){
        g->
        fscanf("%d", );
    }


    return;

}
