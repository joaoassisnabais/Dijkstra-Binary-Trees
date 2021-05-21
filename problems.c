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

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++);

    fprintf(fp, "%d %d A1 %d %d %d %.2lf", g->nv, g->na, va, vb, steps, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");

    free(result);
}

void B1(FILE* fp, data* g, int va, int vb, char id, double detour){
    double totalCostA=-1, totalCost1 = -1, totalCost2 = -1, updatedCost = __DBL_MAX__;
    int i, j, chosenVertex, steps = 0;
    parentArray *resultA, *result1, *result2, *updatedResult1=NULL, *updatedResult2=NULL;
    bool inOriginalPath=false;

    if( (va < 1) || (vb < 1) || (va > g->nv) || (vb > g->nv) ){
        fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");
        return;
    }

    resultA = dijkstra(g, vb, va, &totalCostA, -2, -2);
    for(i=va; i!= vb; i=resultA[ACS(i)].vertex){
        
        while(g->table[ACS(i)].id[j] != '\0'){
            if(g->table[ACS(i)].id[j]==id) inOriginalPath=true;
            j++;
        }
        steps++;
    }
    if (inOriginalPath){
        
        fprintf(fp, "%d %d B1 %d %d %c %.2lf %d %.2lf", g->nv, g->na, va, vb, id, detour, steps, totalCostA);
        for(i=va; i!= vb; i=resultA[ACS(i)].vertex){
            fprintf(fp , "\n%d %d %.2lf", i, resultA[ACS(i)].vertex, resultA[ACS(i)].cost);
        }
        fprintf(fp, "\n\n");

        free(resultA);
        return;
    }
    //correr o vetor e correr o dijkstra para os que tiverem o id correto
    for(i = 0; i < g->nv; i++){
        //printf("vertice:%d id:%s\n", i, g->table[i].id);
        for(j = 0; (g->table[i].id[j] >= 'a') && (g->table[i].id[j] <= 'z'); j++){
            //verificar se o char pedido esta na string e correr o dijkstra se sim
            if(g->table[i].id[j] == id){
                result1 = dijkstra(g, i+1, va, &totalCost1, -2, -2);
                result2 = dijkstra(g, vb, i+1, &totalCost2, -2, -2);
                //verificar se o custo é menor do que o menor obtido
                if((totalCost1 + totalCost2) < updatedCost){
                    //se não for a 1ª iteração dar free dos valores
                    if(updatedResult1 != NULL && updatedResult2 != NULL){
                        free(updatedResult1);
                        free(updatedResult2);
                    }
                    //atualizar os valores
                    updatedCost = totalCost1 + totalCost2;
                    updatedResult1 = result1;
                    updatedResult2 = result2;
                    chosenVertex = i+1;
                }else{
                    free(result1);
                    free(result2);
                }
            }
        }
    }
    /*PRINTS QUE PODEM VOLTAR A SER PRECISOS PARA DEBUG, NAO APAGUES
    printf("\n\n--PROBLEMS--\n");
    for(i=0;i<8; i++)
        printf("v:%d parent:%d cost:%lf\n", i+1, updatedResult1[i].vertex, updatedResult1[i].cost);
    printf("--1/2--\n");
    for(i=0;i<8; i++)
        printf("v:%d parent:%d cost:%lf\n", i+1, updatedResult2[i].vertex, updatedResult2[i].cost);
    printf("--PROBLEMS--\n\n");*/
    
    //verificar se o custo é excedido
    double extracost = (updatedCost-totalCostA)/totalCostA;
    if(extracost>detour && detour>=0){
        fprintf(fp, "%d %d B1 %d %d %c %.2lf -1", g->nv, g->na, va, vb, id, detour);
        fprintf(fp, "\n\n");

        free(updatedResult1);
        free(updatedResult2);
        free(resultA);
        return;
    }
    //ver o número de steps
    steps=0;
    for(i=va; i!= chosenVertex; i=updatedResult1[ACS(i)].vertex, steps++);
    for(i=chosenVertex; i!= vb; i=updatedResult2[ACS(i)].vertex, steps++);

    if(detour==-1) fprintf(fp, "%d %d B1 %d %d %c -1 %d %.2lf", g->nv, g->na, va, vb, id, steps, updatedCost);
    else fprintf(fp, "%d %d B1 %d %d %c %.2lf %d %.2lf", g->nv, g->na, va, vb, id, detour, steps, updatedCost);

    for(i=va; i!= chosenVertex; i=updatedResult1[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, updatedResult1[ACS(i)].vertex, updatedResult1[ACS(i)].cost);
    }
    for(i=chosenVertex; i!= vb; i=updatedResult2[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, updatedResult2[ACS(i)].vertex, updatedResult2[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");

    free(updatedResult1);
    free(updatedResult2);
    free(resultA);
}

void C1(FILE* fp, data* g, int va, int vb, int k){
    parentArray *result, *result2;
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

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++) if(steps == k-1) notV = i;

    if(va == notV || vb == notV || notV == -1){
        printf("%d %d C1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            printf("\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        printf("\n\n");
        free(result);
        return;
    }

    result2 = dijkstra(g, vb, va, &cost2, notV, -2);
    free(result2);

    totalCost=cost2-cost1;
    fprintf(fp, "%d %d C1 %d %d %d %d %.2lf", g->nv, g->na, va, vb, k, steps, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");

    free(result);
}

void D1(FILE* fp, data* g, int va, int vb, int k){

    parentArray *result, *result2;
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

    for(i=va; i!= vb; i=result[ACS(i)].vertex, steps++) if(steps == k-1){
        notV1 = i;
        notV2 = result[ACS(i)].vertex;
    }

    if(notV1 == -1 && notV2 == -1){
        printf("%d %d D1 %d %d %d %d %.2lf -1",g->nv, g->na, va, vb, k, steps, cost1);
        for(i=va; i!= vb; i=result[ACS(i)].vertex)
            printf("\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);

        printf("\n\n");
        free(result);
        return;
    }

    result2 = dijkstra(g, vb, va, &cost2, notV1, notV2);
    free(result2);

    totalCost=cost2-cost1;
    fprintf(fp, "%d %d D1 %d %d %d %d %.2lf", g->nv, g->na, va, vb, k, steps, totalCost);
    for(i=va; i!= vb; i=result[ACS(i)].vertex){
        fprintf(fp , "\n%d %d %.2lf", i, result[ACS(i)].vertex, result[ACS(i)].cost);
    }
    fprintf(fp, "\n\n");

    free(result);
}