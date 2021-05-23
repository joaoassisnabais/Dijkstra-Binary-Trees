/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   problems.c
 *
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <float.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"
#include "binaryTree.h"
#include "spt.h"

int A0 (data *g, int vertex) {

    if((vertex <= g->nv) && (vertex > 0))
        return g->table[ACS(vertex)].nLinks;
    else return -1;
}

double B0 (data *g, int v1, int v2) {

    node* link;

    if(((v1 <= g->nv) && (v1 > 0)) && ((v2 <= g->nv) && (v2 > 0))) {
        if(v1==v2)
            return -1;
        else if(g->table[ACS(v1)].nLinks < g->table[ACS(v2)].nLinks)    //check which one has the least link, to make the search faster
            link = FindNode(g->table[ACS(v1)].root, v2);
        else
            link = FindNode(g->table[ACS(v2)].root, v1);
    } else
        return -1;

    if(link == NULL)
        return -1;
    else
        return link->cost;
}

int C0 (data *g, int v1, int k){

    int steps=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        if(k == 0)
            return 1;
        if(k < 0)
            return 0;
        outputBfs = bfsTree(g,ACS(v1), k);
        steps=outputBfs->maxSteps;
        free(outputBfs);
        if(k <= steps)
            return 1;
        else
            return 0;
    }else
        return -1;
}

int D0 (data *g, int v1, int k){

    int sol=0;
    bfsOut* outputBfs;

    if((v1<=g->nv) && (v1>0)){  //verificação da existência do vértice
        if(k == 0)
            return 1;
        if(k < 0)
            return 0;
        outputBfs=bfsTree(g,ACS(v1), k+1);
        sol = outputBfs->verticesAtK;
        free(outputBfs);
    }else sol = -1;

    return sol;
}

bfsOut* bfsTree(data *g, int v, int k) {
    
    queue *q = NULL;
    int *visited = (int *) calloc(g->nv,sizeof(int));
    bfsOut* output = (bfsOut*) malloc(sizeof(bfsOut));
    output->maxSteps = 0;
    output->verticesAtK = 0;
    
    q = qAdd(q,v);
    while (q->top != NULL){
        if (visited[q->top->v] == 0){//verificação de vértice visitado
            visited[q->top->v] = 1;
            if(q->top->steps > output->maxSteps) { //ADICIONAR VERIFICAÇÃO COM K
                output->maxSteps = q->top->steps;
                if(output->maxSteps == k)
                    break;
            }
            if(q->top->steps == k-1)    //usado para D0, com k+1 de input
                output->verticesAtK++;

            qTree(g->table[q->top->v].root, &q, visited);
        }
        qPop(q);
    }
    free(visited);
    qFree(q);
    return output;
}

/*----------------------------------------------------------2nd Submission----------------------------------------------------------------*/

void recursivePrinting(FILE *fp, int i, int va, parentArray *resultA) {
        //i=resultA[ACS(i)].vertex;
    if(i != va) {
        recursivePrinting(fp, resultA[ACS(i)].vertex, va, resultA);
        fprintf(fp , "\n%d %d %.2lf", resultA[ACS(i)].vertex, i, resultA[ACS(i)].cost);
    }
    return;
}

void A1(FILE* fp, data* g, int va, int vb){
    parentArray *result;
    double totalCost=-1;
    int steps=0, i;

    if( (va < 1) || (vb < 1) || (va > g->nv) || (vb > g->nv) ){
        fprintf(fp, "%d %d A1 %d %d -1", g->nv, g->na, va, vb);
        fprintf(fp, "\n\n");
        return;
    }

    if(va == vb){
        fprintf(fp, "%d %d A1 %d %d 0 0.00", g->nv, g->na, va, vb);
        fprintf(fp, "\n\n");
        return;
    }

    result = dijkstra(g, vb, va, &totalCost, -2, -2);

    if(result == NULL) {
        fprintf(fp, "%d %d A1 %d %d -1", g->nv, g->na, va, vb);
        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++);

    fprintf(fp, "%d %d A1 %d %d %d %.2lf", g->nv, g->na, va, vb, steps, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");
    free(result);
}

void B1(FILE* fp, data* g, int va, int vb, char id, double detour){
    double totalCost = 0, auxCost=0, updatedCost = DBL_MAX;
    int i, j = 0, k = 0, chosenVertex = -1, steps = 0, finalSteps = 0;
    parentArray *resultA, *resultB;

    if( (va < 1) || (vb < 1) || (va > g->nv) || (vb > g->nv) ){
        if(detour==-1)
            fprintf(fp, "%d %d B1 %d %d %c -1 -1", g->nv, g->na, va, vb, id);
        else
            fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");
        return;
    }

    resultA = dijkstra(g, va, -1, NULL, -2, -2);

    if(resultA == NULL) {
        if(detour==-1)
            fprintf(fp, "%d %d B1 %d %d %c -1 -1", g->nv, g->na, va, vb, id);
        else
            fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");
        return;
    }

    resultB = dijkstra(g, vb, -1, NULL, -2, -2);

    if(resultB == NULL) {
        if(detour==-1)
            fprintf(fp, "%d %d B1 %d %d %c -1 -1", g->nv, g->na, va, vb, id);
        else
            fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");

        free(resultA);
        return;
    }
    //corre todos os vértices
    for(i=1; i<=g->nv; i++){
        //corre os ids de cada vértice
        for(j = 0; (g->table[ACS(i)].id[j] != '\0') && (g->table[ACS(i)].id[j] != '-') ; j++){
            //compara ao id pedido
            if(g->table[ACS(i)].id[j] == id){
                //verifica se o vertice tem ligação a A e B
                if((resultA[ACS(i)].cost != -1) && (resultB[ACS(i)].cost != -1)) {
                    auxCost = 0;
                    steps = 0;
                    for(k = i; k!= va; k=resultA[ACS(k)].vertex, steps++)
                        auxCost+=resultA[ACS(k)].cost;
                    for(k = i; k!= vb; k=resultB[ACS(k)].vertex, steps++)
                        auxCost+=resultB[ACS(k)].cost;
                    if( updatedCost > auxCost ){
                        updatedCost = auxCost;
                        finalSteps = steps;
                        chosenVertex = i;
                    }
                }
                break;
            }
        }
    }

    //verificar se encontrámos ligação entre um vertice com o id e A e B
    if(auxCost == 0){
        if( detour == -1 )
            fprintf(fp, "%d %d B1 %d %d %c -1 -1", g->nv, g->na, va, vb, id);
        else
            fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);

        fprintf(fp, "\n\n");
        free(resultA);
        free(resultB);
        return;
    }
    //custo de va para vb sem o desvio
    steps=0;
    for(i=vb; i!= va; i=resultA[ACS(i)].vertex, steps++)
        totalCost+=resultA[ACS(i)].cost;

    //verificar se o custo é excedido como desvio
    double extracost = (updatedCost-totalCost)/totalCost;
    if(extracost>detour && detour>=0){
        fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");

        free(resultA);
        free(resultB);
        return;
    }

    if( detour == -1 )
        fprintf(fp, "%d %d B1 %d %d %c -1 %d %.2lf", g->nv, g->na, va, vb, id, finalSteps, updatedCost);
    else
        fprintf(fp, "%d %d B1 %d %d %c %.2lf %d %.2lf", g->nv, g->na, va, vb, id, detour, finalSteps, updatedCost);

    recursivePrinting(fp, chosenVertex, va, resultA);

    for(i=chosenVertex; i!= vb; i=resultB[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, resultB[ACS(i)].vertex, resultB[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");

    free(resultA);
    free(resultB);
}

void C1(FILE* fp, data* g, int va, int vb, int k){
    parentArray *result=NULL, *result2=NULL;
    double cost1=-1, cost2=-1, totalCost;
    int steps=0, notV=-1, i;

    if( (va < 1) || (vb < 1) || (va > g->nv) || (vb > g->nv) ){
        fprintf(fp, "%d %d C1 %d %d %d -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        return;
    }

    if(va == vb){
        fprintf(fp, "%d %d C1 %d %d %d 0 0.00 -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        return;
    }

    result = dijkstra(g, vb, va, &cost1, -2, -2);

    if(result == NULL) {
        fprintf(fp, "%d %d C1 %d %d %d -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++) if(steps == k-1) notV = i;

    if(va == notV || vb == notV || notV == -1){
        fprintf(fp, "%d %d C1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            fprintf(fp, "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    result2 = dijkstra(g, vb, va, &cost2, notV, -2);

    if(result2==NULL){
        fprintf(fp, "%d %d C1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            fprintf(fp, "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    free(result2);
    
    totalCost=cost2-cost1;
    fprintf(fp, "%d %d C1 %d %d %d %d %.2lf %.2lf", g->nv, g->na, va, vb, k, steps, cost1, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");
    free(result);
}

void D1(FILE* fp, data* g, int va, int vb, int k){

    parentArray *result=NULL, *result2=NULL;
    double cost1=-1, cost2=-1, totalCost;
    int steps=0, notV1=-1, notV2=-1, i;

    if( (va < 1) || (vb < 1) || (va > g->nv) || (vb > g->nv) ){
        fprintf(fp, "%d %d D1 %d %d %d -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        return;
    }

    if(va == vb){
        fprintf(fp, "%d %d D1 %d %d %d 0 0.00 -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        return;
    }

    result = dijkstra(g, vb, va, &cost1, -2, -2);

    if(result == NULL) {
        fprintf(fp, "%d %d D1 %d %d %d -1", g->nv, g->na, va, vb, k);
        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++) if(steps == k-1){
        notV1 = i;
        notV2 = result[ACS(i)].vertex;
    }

    if(notV1 == -1 && notV2 == -1){
        fprintf(fp, "%d %d D1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            fprintf(fp, "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        fprintf(fp, "\n\n");
        free(result);
        return;
    }

    result2 = dijkstra(g, vb, va, &cost2, notV1, notV2);

    if(result2==NULL){
        fprintf(fp, "%d %d D1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            fprintf(fp, "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        fprintf(fp, "\n\n");
        free(result);
        return;
    }
    free(result2);

    totalCost=cost2-cost1;
    fprintf(fp, "%d %d D1 %d %d %d %d %.2lf %.2lf", g->nv, g->na, va, vb, k, steps, cost1, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");
    free(result);
}