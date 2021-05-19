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
#include "binaryTree.h"

void createGraph(FILE** fp, data* g){

    char str[30];
    int i = 0, nVer = 0, va, vb, len;       //nVer: nº do vértice
    double cost;

    g->table = CreateTrunk(g->nv);

    //colocar os valores dos ids na matriz
    for (i=0; i<g->nv; i++){
        if(fscanf(*fp,"%d", &nVer) == 0) exit(0);
        if(fscanf(*fp, "%s", str) == 0) exit(0);
        len = strlen(str) + 1;
        g->table[ACS(nVer)].id = (char*) malloc(len);
        strcpy(g->table[ACS(nVer)].id, str);           //fazer define -1 ? 
        g->table[ACS(nVer)].id[len-1] = '\0';
    }
    
    //colocar os custos na matriz de adjacência
    for(i=0; i<g->na; i++){
        if(fscanf(*fp,"%d", &va) == 0) exit(0);
        if(fscanf(*fp,"%d", &vb) == 0) exit(0);
        if(fscanf(*fp,"%lf", &cost) == 0) exit(0);
        g->table[ACS(va)].root = AVLInsert(g->table[ACS(va)].root, vb, cost);   //Insert edge into tree
        g->table[ACS(va)].nLinks++;                                             //Increment number of links of the one vertex
        g->table[ACS(vb)].root = AVLInsert(g->table[ACS(vb)].root, va, cost);
        g->table[ACS(vb)].nLinks++;
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

//Recebe uma queue e uma árvore e percorre a árvore 
//adicionando os nós não visitados à queue
void qTree(node* tree, queue** q, int* visited){
    
    if(tree==NULL)
        return;
    if(!visited[ACS(tree->name)])
        *q = qAdd(*q, ACS(tree->name));
    if ((tree->left==NULL) && (tree->right==NULL))
        return; //Dead End
    if (tree->left)
        qTree(tree->left, q, visited);
    if (tree->right)
        qTree(tree->right, q, visited);
}