/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   binaryTree.c
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

int Height(node *n) {
    
    if (n == NULL){
        return 0;
    }
    return n->height;
}

int Max(int a, int b){
    if(a>b)
        return a;
    else
        return b;
}

int Balance (node * root){
    
    if(root == NULL) return 0;
    
    return Height(root->left)-Height(root->right);
}

void CutTree(node *tree){
    if(tree != NULL){
        if(tree->left != NULL)
            CutTree(tree->left);
        if(tree->right != NULL)
            CutTree(tree->right);
        free(tree);
    }
}

void CutTrunk(trunk *table){
    free(table);
}

void CleanMem(trunk *table, int n_vertex){
    
    for (int i = 0; i < n_vertex; i++){
        CutTree(table[i].root);
        free(table[i].id);
    }
        CutTrunk(table);
}

void InitVertex(trunk *table) {
    (*table).nLinks = 0;
    (*table).id = NULL;
    (*table).root = NULL;
}

void InitTree(trunk * table, int n_vertex){
    for (int i = 0 ; i < n_vertex ; i++) {
        InitVertex(&table[i]);
    }
}

trunk* CreateTrunk(int n_vertex){
    
    trunk *table = (trunk *) malloc(sizeof(trunk)*n_vertex);
    
    if (table == NULL) {
        exit(0);
    }
    InitTree(table, n_vertex);
    return table;
}

node* CreateLeaf(int name, double cost){
    
    node* new = (node *) malloc(sizeof(node));
    
    if (new == NULL) {
        exit(0);
    }
    new->left = NULL;
    new->right = NULL;
    new->cost = cost;
    new->name = name;
    new->height = 1;
    return new;
}

node* RotateRight(node * y){
    
    node * x = y->left;
    node * z = x->right;
    
    x->right = y;
    y->left = z;
    
    y->height = 1 + Max(Height(y->left), Height(y->right));
    x->height = 1 + Max(Height(x->left), Height(x->right));
    
    return x;
}

node* RotateLeft(node * x){
    
    node* y = x->right;
    node* z = y->left;
    
    y->left = x;
    x->right = z;
    
    x->height = 1 + Max(Height(x->left), Height(x->right));
    y->height = 1 + Max(Height(y->left), Height(y->right));
    
    return y;
}

//Vê se existe uma ligação a um node 'v' numa árvore
node* FindNode(node *tree, int v){
    
    if((tree)==NULL)
        return NULL;
    
    if(v == (tree)->name)
        return (tree);
    else if(v < (tree)->name)
        return FindNode((tree)->left, v);
    else if (v > (tree)->name)
        return FindNode((tree)->right, v);
    else
        return NULL;
}

node* AVLInsert(node *root, int name, double cost){
  
    if (root == NULL) { return(CreateLeaf(name, cost)); }

    if (name < root->name) {
        root->left  = AVLInsert(root->left, name, cost);
        
    } else if (name > root->name) {
        root->right  = AVLInsert(root->right, name, cost);
        
    } else { return root; }
    
    root->height = 1 + Max(Height(root->left), Height(root->right));
    int bal = Balance(root);
    
    if(bal >  1 && name < root->left->name)  { return RotateRight(root);}
    else if(bal < -1 && name > root->right->name) { return RotateLeft(root); }
    else if(bal >  1 && name > root->left->name)  {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }
    else if(bal < -1 && name < root->right->name) {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }
    return root;
}