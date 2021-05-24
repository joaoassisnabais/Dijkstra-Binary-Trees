#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <float.h>

#include "spt.h"
#include "matrix.h"

/**
 * @description: compares two costs
 * 
 * @parameter: cost1 
 * @parameter: cost2 
 * @return: true 
 * @return: false 
 */
bool compare (double cost1, double cost2) {
    if(cost1 > cost2)
        return true;
    return false;
}

/**
 * @description: gets the cost of a certain index
 * 
 * @parameter: q 
 * @parameter: index 
 * @return: double 
 */
double getCost (PQueue *q, int index) {
    return q->data[q->qVertex[index]].cost;
}

/**
 * @description: changes the index stored in q->data
 * 
 * @parameter: q 
 * @parameter: newIndex 
 * @parameter: oldIndex 
 */
void updateIndex (PQueue *q, int newIndex, int oldIndex) {
    q->data[q->qVertex[oldIndex]].index = newIndex;
}

/**
 * @description: gets the parent of the index passes into the function
 * 
 * @parameter: childIndex 
 * @return: int 
 */
int parentOf (int childIndex) {
    return (childIndex-1) / 2;
}

/**
 * @description: fixUp the heap
 * 
 * @parameter: q 
 * @parameter: index 
 */
void fixUp(PQueue *q, int index) {
    int aux;
    while((index > 0) && compare(getCost(q, parentOf(index)), getCost(q, index))) {
        aux = q->qVertex[index];
        q->qVertex[index] = q->qVertex[parentOf(index)];
        q->qVertex[parentOf(index)] = aux;
        updateIndex(q, index, index);
        updateIndex(q, parentOf(index), parentOf(index));
        index = parentOf(index);
    }
}

/**
 * @description: fixDown the heap
 * 
 * @parameter: q 
 * @parameter: index 
 */
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
        updateIndex(q, index, index);
        updateIndex(q, j, j);
        index = j;
    }
}

/**
 * @description: modifies the cost of a certain vertex, and then returns the array to its heap condition using fixUp and fixDown
 * 
 * @parameter: q 
 * @parameter: index 
 * @parameter: newcost 
 */
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

/**
 * @description: adds an element to the priority queue, or modifies an existing one, in case the given vertex is already in the queue
 * 
 * @parameter: qP 
 * @parameter: vId 
 * @parameter: newcost 
 * @parameter: previous 
 * @parameter: parentCost 
 * @parameter: va 
 * @parameter: vb 
 */
void pqAdd(PQueue **qP, int vId, double newcost, int previous, double parentCost, int va, int vb){
    PQueue *q = *qP;

    if(vId == ACS(va) && vb == -2)
        return;
    if( (vId == ACS(va) && previous == ACS(vb)) || (vId == ACS(vb) && previous == ACS(va)) )
        return;
    
    if(q->data[vId].visited == true)
        return;
    if(q->data[vId].index != -1) {//já está na pQ?
        if(q->data[vId].cost <= newcost)
            return;
        pqModify(q, q->data[vId].index, newcost);
        q->data[vId].previous = previous;
        q->data[vId].parentCost = parentCost;
        return;
    }
    q->qVertex[q->n_elements] = vId;
    q->data[vId].cost = newcost;
    q->data[vId].index = q->n_elements;
    q->data[vId].previous = previous;
    q->data[vId].parentCost = parentCost;
    q->n_elements++;
    fixUp(q, q->data[vId].index);
}

/**
 * @description: pops the top element from the priority queue and then fixes the queue with fixDown
 * 
 * @parameter: q 
 * @return: int 
 */
int pqPop(PQueue *q) {
    int aux;
    
    if (q->n_elements == 1) {
        aux = q->qVertex[0];
        q->data[aux].index = -1;
        q->data[aux].visited = true;
        q->n_elements--;

        return aux;
    }
    
    if(q->n_elements > 0) {
        aux = q->qVertex[0];
        q->qVertex[0] = q->qVertex[q->n_elements - 1];
        q->qVertex[q->n_elements - 1] = -1;
        
        q->data[q->qVertex[0]].index = 0;
        q->n_elements--;
        fixDown(q, 0);

        q->data[aux].index = -1;
        q->data[aux].visited = true;

        return aux;
    }
    return -1;
}

/**
 * @description: reads the tree recursively and adds the read vertices to the priority queue
 * 
 * @parameter: tree 
 * @parameter: q 
 * @parameter: currentCost 
 * @parameter: previous 
 * @parameter: va 
 * @parameter: vb 
 */
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

/**
 * @description: creates a priority queue, allocating space to it
 * 
 * @parameter: size 
 * @return: PQueue* 
 */
PQueue * pqCreate(int size) {
    PQueue * q;
    q = (PQueue*) malloc(sizeof(PQueue));
    q->data = (QData*) malloc(sizeof(QData) * size);
    q->qVertex = (int*) malloc(sizeof(int) * size);
    q->n_elements = 0;
    q->size = size;
    return q;
}

/**
 * @description: checks if the priority queue is empty
 * 
 * @parameter: q 
 * @return: true 
 * @return: false 
 */
bool pqEmpty(PQueue *q) {
    if(q->n_elements == 0)
        return true;
    return false;
}

/**
 * @description: initializes each data node with the wanted values
 * 
 * @parameter: q 
 * @parameter: vId 
 */
void initQData(PQueue *q, int vId) {
    q->data[vId].cost = DBL_MAX;
    q->data[vId].index = -1;
    q->data[vId].visited = false;
    q->data[vId].previous = -1;
    q->qVertex[vId] = -1;
}

/**
 * @description: frees the priority queue
 * 
 * @parameter: q 
 */
void pqFree(PQueue *q){
    free(q->data);
    free(q->qVertex);
    free(q);
}

/**
 * @description: dijkstra function to find the sorthest path beetween to vertices, takes O(ElogV), where E is the number of edges and V is the number of vertices
 * 
 * @parameter: g 
 * @parameter: src 
 * @parameter: end 
 * @parameter: totalCost 
 * @parameter: va 
 * @parameter: vb 
 * @return: parentArray* 
 */
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

    /*add src to the priority queue*/
    pqAdd(&q, ACS(src), 0, ACS(src), 0, va, vb);    //add src à Queue
    parent[ACS(src)].cost = 0;

    /*run while pQ is not empty*/
    while(!pqEmpty(q)){

        /*pop the top vertex and changes the current vertex to it*/
        current = pqPop(q);
    
        /*read the tree of the current vertex and store its linked vertices in the queue*/
        if(current != -1 && (end == -1 || q->data[ACS(end)].visited != true)){
            pqTree(g->table[current].root, &q, q->data[current].cost, current, va, vb);
        }

        /*stores the parent of each vertex and the cost of that edge*/
        parent[current].vertex = q->data[current].previous + 1;
        parent[current].cost = q->data[current].parentCost;

        /*returns when it reaches the wanted vertex*/
        if(end>0 && q->data[ACS(end)].visited == 1){
            *totalCost=q->data[ACS(end)].cost;
            pqFree(q);
            return parent;
        }
    }
    pqFree(q);
    if(end>0)
    /*returns if no path was found to the given vertex*/
        return NULL;
    else
    /*returns after finding the shortest path to every vertex*/
        return parent;
}