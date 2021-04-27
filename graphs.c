/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"

void createGraph(FILE** fp, graph* g){

    char str[30];
    int i = 0, nVer = 0, va, vb, len;       //nVer: nº do vértice
    double cost;

    createMandV(g, g->nv);

    //colocar os valores dos ids na matriz
    for (i=0; i<g->nv; i++){
        if(fscanf(*fp,"%d", &nVer) == 0) exit(0);
        if(fscanf(*fp, "%s", str) == 0) exit(0);
        len = strlen(str) + 1;
        g->c[ACS(nVer)] = (char*) malloc(len);
        strcpy(g->c[ACS(nVer)], str);           //fazer define -1
        g->c[ACS(nVer)][len-1] = '\0';
    }
    IniMatrix(g->matrix, g->nv);
    
    //colocar os custos na matriz de adjacência
    for(i=0; i<g->na; i++){
        if(fscanf(*fp,"%d", &va) == 0) exit(0);
        if(fscanf(*fp,"%d", &vb) == 0) exit(0);
        if(fscanf(*fp,"%lf", &cost) == 0) exit(0);
        g->matrix[AccessM(ACS(va),ACS(vb), g)] = cost;
    }
    return;
}

void freeGraph(graph* g) {
    
    for(int i = 0; i < g->nv; i++) {
        free(g->c[i]); 
    }
    free(g->c);
    free(g->matrix);
}

void qPop(queue *q){

    qnode *auxNode = q->top;
    q->top = q->top->next;
    free(auxNode);

}

queue * qAdd(queue *q, int v){

    if(q==NULL){
        q = (queue *) malloc(sizeof(queue));
        q->top = (qnode *) malloc(sizeof(qnode));
        q->top->v = v;
        q->top->next = NULL;
        q->bottom = q->top;
        q->top->steps = 0;
    }else{
        q->bottom->next = (qnode *) malloc(sizeof(qnode));
        q->bottom = q->bottom->next;
        q->bottom->v = v;
        q->bottom->next = NULL;
        q->bottom->steps = q->top->steps+1;
    }
    return q;
}

void qFree(queue *q){

    qnode *aux=q->top;

    while(q->top!=NULL){
        q->top=aux->next;
        free(aux);
        aux = q->top;
    }
    free(q);
}

void qPrint(queue *q){

    qnode *aux = q->top;

    while (aux!=NULL) {
        printf("%d\n", aux->v);
        aux = aux->next;
    }
}  
