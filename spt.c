#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

#include "spt.h"
#include "matrix.h"

bool compare (double cost1, double cost2) {
    if(cost1 > cost2)
        return true;
    return false;
}

double getCost (PQueue *q, int index) {
    return q->data[q->qVertex[index]].cost;
}

void updateIndex (PQueue *q, int newIndex, int oldIndex) {
    q->data[q->qVertex[oldIndex]].index = newIndex;
}

int parentOf (int childIndex) {
    return (childIndex-1) / 2;
}

void fixUp(PQueue *q, int index) {
    int aux;
    while((index > 0) && compare(getCost(q, parentOf(index)), getCost(q, index))) {
        aux = q->qVertex[index];
        q->qVertex[index] = q->qVertex[parentOf(index)];
        q->qVertex[parentOf(index)] = aux;
        updateIndex(q, index, parentOf(index));
        updateIndex(q, parentOf(index), index);
        index = parentOf(index);
    }
}

void fixDown(PQueue *q, int index) {
    int j, aux;
    while((index*2 + 1) < q->n_elements) {
        j = 2*index + 1;
        if((j+1 < q->n_elements) && compare(getCost(q, j), getCost(q, j+1))) {
            j++;
        }
        if(!compare(getCost(q, index), getCost(q, j))) {
            break;
        }
        aux = q->qVertex[index];
        q->qVertex[index] = q->qVertex[j];
        q->qVertex[j] = aux;
        updateIndex(q, index, j);
        updateIndex(q, j, index);
        index = j;
    }
}

void pqModify(PQueue *q, int index, double newcost){
    if(index > q->n_elements - 1)
        return;
    if(compare(newcost, getCost(q, index))) {
        q->data[q->qVertex[index]].cost = newcost;
        fixDown(q, index);
    } else {
        q->data[q->qVertex[index]].cost = newcost;
        fixUp(q, index);
    }
    return;
}

void pqAdd(PQueue **qP, int vId, double newcost, int previous, double parentCost, int va, int vb){
    PQueue *q = *qP;

    if(vId == va && vb == -2)
        return;
    if( (vId == va && previous == vb) || (vId == vb && previous == va) )
        return;
    
    if(q->data[vId].visited == true)
        return;
    if(q->data[vId].index != -1) {
        if(q->data[vId].cost <= newcost)
            return;
        pqModify(q, q->data[vId].index, newcost);
    }
    q->qVertex[q->n_elements] = vId;
    q->data[vId].cost = newcost;
    q->data[vId].index = q->n_elements;
    q->data[vId].previous = previous;
    q->data[vId].parentCost = parentCost;
    q->n_elements++;
    fixUp(q, q->data[vId].index);
}

int pqPop(PQueue *q) {
    int aux;

    if(q->n_elements > 0) {
        aux = q->qVertex[0];
        q->qVertex[0] = q->qVertex[q->n_elements - 1];
        q->qVertex[q->n_elements - 1] = -1;
        q->n_elements--;
        fixDown(q, 0);

        q->data[aux].index = -1;
        q->data[aux].visited = true;

        return aux;
    }
    return -1;
}

void pqTree(node* tree, PQueue** q, double currentCost, int previous, int va, int vb){
    
    if(tree==NULL)
        return;
    if(!(*q)->data[ACS(tree->name)].visited)
        pqAdd(q, ACS(tree->name), tree->cost + currentCost, previous, tree->cost, va, vb);
    if ((tree->left==NULL) && (tree->right==NULL))
        return; //Dead End
    if (tree->left)
        pqTree(tree->left, q, currentCost, previous, va, vb);
    if (tree->right)
        pqTree(tree->right, q, currentCost, previous, va, vb);
}

PQueue * pqCreate(int size) {
    PQueue * q;
    q = (PQueue*) malloc(sizeof(PQueue));
    q->data = (QData*) malloc(sizeof(QData) * size);
    q->qVertex = (int*) malloc(sizeof(int) * size);
    q->n_elements = 0;
    q->size = size;
    return q;
}

bool pqEmpty(PQueue *q) {
    if(q->n_elements == 0)
        return true;
    return false;
}

void initQData(PQueue *q, int vId) {
    q->data[vId].cost = DBL_MAX;
    q->data[vId].index = -1;
    q->data[vId].visited = false;
    q->data[vId].previous = -1;
    q->qVertex[vId] = -1;
}

void pqFree(PQueue *q){
    free(q->data);
    free(q->qVertex);
    free(q);
}

parentArray* dijkstra(data *g, int src, int end, double* totalCost, int va, int vb) {

    PQueue *q;
    parentArray *parent; //array de parents
    int current;
    
    parent = (parentArray*) malloc(sizeof(parentArray) * g->nv);
    q = pqCreate(g->nv);

    for(int v = 0; v < g->nv; v++) {
        initQData(q, v);
        parent[v].vertex = v;
        parent[v].cost = -1;
    }

    pqAdd(&q, ACS(src), 0, ACS(src), 0, va, vb);    //add src à Queue


    while(!pqEmpty(q)){//condição de paragem??

        current = pqPop(q);

    
        if(current != -1 && q->data[ACS(end)].visited != 1){
            pqTree(g->table[current].root, &q, q->data[current].cost, current, va, vb);
        }
        parent[current].vertex = q->data[current].previous + 1;
        parent[current].cost = q->data[current].parentCost;
        
        if(q->data[ACS(end)].visited == 1){
            *totalCost=q->data[ACS(end)].cost;
            pqFree(q);
            return parent;
        }
        //PRINT PARA DEBUGS, NAO APAGAR
        //printf("vertice: %d Pai: %d custo: %.2lf\n", current+1, parent[current].vertex, parent[current].cost);
    }
    return NULL;
}