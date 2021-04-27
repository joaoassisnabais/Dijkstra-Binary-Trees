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

void CutTree(node *tree){
    if(tree != NULL){
        if(tree->left != NULL)
            CutTree(tree->left);
        if(tree->right != NULL)
            CutTree(tree->right);
        free(tree);
    }
}

int Height(node *n) {
    
    if (n == NULL){
        return 0;
    }
    return n->height;
}

int Max(int a, int b){
    if(a>b) return a;
    else return b;
}

void CutTrunk(trunk *table){
    free(table->id);
    free(table);
}

node* GetRoot(trunk * table, int key){
    return table[ACS(key)].root;
}

int GetLinks(trunk * table, int key){
    return table[ACS(key)].nLinks;
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

node* CreateLeaf(int name, double cost) {
    
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

int Balance (node * root) {
    
    if(root == NULL) return 0;
    
    return Height(root->left)-Height(root->right);
}

trunk* CreateTrunk(int n_vertex){
    
    trunk *table = (trunk *) malloc(sizeof(trunk)*n_vertex);
    
    if (table == NULL) {
        exit(0);
    }
    InitTree(table, n_vertex);
    return table;
}

node* LeftOf(node * t){
    return t->left;
}

node* RightOf(node * t){
    return t->right;
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


//Recebe um array x posições onde x = n_links de uma árvore
//guarda em cada posição do array um dos nodes
void SeeTree(node* tree, int array[], int *i){
    
    if(tree==NULL) return;
    array[*i] = tree->name;
    (*i)++;
    if ((tree->left==NULL) && (tree->right==NULL) ) return; //Dead End
    if (tree->left) SeeTree(tree->left, array, i);
    if (tree->right) SeeTree(tree->right, array, i);
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

void CleanMem(trunk *table, int n_vertex){
    
    for (int i = 0; i < n_vertex; i++)
        CutTree(table[i].root);

    CutTrunk(table);
}