/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   dijsktra.c
 *
 ******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "fileData.h"
#include "graphs.h"
#include "matrix.h"
#include "problems.h"
#include "binaryTree.h"
#include "dijkstra.h"

bool compare(QData item1, QData item2){
    if (item1.cost < item2.cost)
        return true;
    else
        return false;
}

/*void pqPrint(PQueue * q, void printItem(const void *)) {
    for (int i = 0; i < q->n_elements ; i++) {
        printItem(q->data[i]);
    }
}*/

void pqErase(PQueue * q){
    free(q->data);
    free(q);
}

PQueue * pqCreate(int size){
    PQueue * q = (PQueue *) malloc(sizeof(PQueue));     //malloc struct of type PQueue
    if (q == NULL) { return NULL; }                     //malloc error
    q->n_elements = 0;                                  //number of elements at 0
    q->size = size;
    q->data = (QData *) malloc(sizeof(QData)*size);     //malloc array of structs of type QData
    if (q->data == NULL) {                              //malloc error
        free(q);
        return NULL;
    }
    return q;
}

//i = index
void FixUp(PQueue *q, int index) {
    QData t;
    while ((index > 0) && compare(q->data[(index-1) / 2], q->data[index])) {
        t = q->data[index];
        q->data[index] = q->data[(index - 1) / 2];
        q->data[(index - 1) / 2] = t;
        index = (index - 1) / 2;
    }
    return;
}

void FixDown(PQueue * q, int index) {
    int j;
    QData t;
    
    while ((2 * index + 1) < q->n_elements) {
        j = 2 * index + 1;
        if (((j + 1) < q->n_elements) && compare(q->data[j], q->data[j + 1])) {
            /* second offspring is greater */
            j++;
        }
        if (!compare(q->data[index], q->data[j])) {
            /* Elements are in correct order. */
            break;
        }
        /* the 2 elements are not correctly sorted, it is
         necessary to exchange them */
        t = q->data[index];
        q->data[index] = q->data[j];
        
        q->data[j] = t;
        index = j;
    }
    return;
}

//i = index
void SFixUp(PQueue *q, int index) {
    QData t;
    while ((index > 0) && !compare(q->data[(index - 1) / 2], q->data[index])) {
        t = q->data[index];
        
        q->data[index] = q->data[(index - 1) / 2];
        
        q->data[(index - 1) / 2] = t;
        index = (index - 1) / 2;
    }
    return;
}

void SFixDown(PQueue * q, int k) {
    int j;
    QData t;
    
    while ((2 * k + 1) < q->n_elements) {
        j = 2 * k + 1;
        if (((j + 1) < q->n_elements) && !compare(q->data[j], q->data[j + 1])) {
            /* second offspring is greater */
            j++;
        }
        if (compare(q->data[k], q->data[j])) {
            /* Elements are in correct order. */
            break;
        }
        /* the 2 elements are not correctly sorted, it is
         necessary to exchange them */
        t = q->data[k];
        q->data[k] = q->data[j];
        
        q->data[j] = t;
        k = j;
    }
    return;
}

void HeapSort(PQueue * q) {
    QData aux;
    int num_elements = q->n_elements;
    for (int i = q->n_elements-1 ; i > 0 ; i--) {
        aux = q->data[0];
        
        q->data[0] = q->data[i];
        
        q->data[i] = aux;
        
        q->n_elements--;
        FixDown(q, 0);
    }
    q->n_elements = num_elements;
  return;
}
/*
Function to add a vertex to the PQ
*/
void pqAdd(PQueue * q, QData data){
    q->data[q->n_elements] = data;
    q->n_elements++;
    FixUp(q, q->n_elements-1);
}

void pqModify(PQueue * q, int q_index, int newcost) {
    if (newcost < q->data[q_index].cost) {
        q->data[q_index].cost = newcost;
        SFixUp(q, q_index);
    } else {
        q->data[q_index].cost = newcost;
        SFixDown(q, q_index);
    }
    return;
}

void pqMinDel(PQueue * q){
    if (q->n_elements > 0) {
        q->data[0] = q->data[q->n_elements - 1];
        
        //q->data[q->n_elements - 1] = 0;
        q->n_elements--;
        SFixDown(q, 0); //FIXME
    }
}

QData pqGetFirst(PQueue * q){   //alternativamente: QData *
    QData t = q->data[0];       //alternativamente: QData *t = &(q->data[0]);
    return t;
}

int * dijkstra(data * g, int src, int end) {

    int *parentArr, cost;
    node *auxVertex;
    PQueue *q = pqCreate(g->nv);
    QData aux, current;
    aux.cost = INF;

    for(int v = 0; v < g->nv; v++) {
        aux.vert = v;
        pqAdd(q, aux);
    }

    pqModify(q, src, 0);

    while (q->data != NULL) {
        current = pqGetFirst(q);
        cost = FindNode(g->table[ACS(current)].root, );
        while(aux.vert != src) {
            pqModify(q, aux.vert, cost);
        }
    }

    return parentArr;
}