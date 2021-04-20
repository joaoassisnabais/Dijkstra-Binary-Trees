/******************************************************************************
 * (c) 2021 João Nabais & João Nabais
 *
 * NAME
 *   graphs.h
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "fileData.h"
#include "graphs.h"

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


    for (int i=0; i<vexNumber; i++){
        fscanf("%d", );
    }


    return;

}
