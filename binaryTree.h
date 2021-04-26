/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   binaryTree.h
 *
 ******************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#define DUPLICATED_NODE -2
#define NO_MEMORY -1

typedef struct _node node;
typedef struct _trunk trunk;
typedef struct _data data;

struct _node{
    int name;       //used to access trunk
    int height;     //saves height of the node
    node *left;    //left is lower
    node *right;   //right is higher
    double cost;    //cost to travel along a a edge
};

struct _trunk{
    int n_links;
    char *id;
    node *root;
};

struct _data{
    trunk *table;
    int nv;
    int na;
};

trunk *CreateTrunk(int n_vertex);
node *FindNode(node *tree, int name);
void CleanMem(trunk * table, int n_vertex);
node *CreateLeaf(int name, double cost);
void CutTree(node * tree);
void InitVertex(trunk *table);
void SeeTree(node * tree, int array[], int *i);
node *GetRoot(trunk * table, int key);
int GetLinks(trunk * table, int key);
int GetName(node * branch);
node *AVLInsert(node * root, int name, double cost);

#endif /* Binary_Tree_h */