/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   binaryTree.h
 *
 ******************************************************************************/
#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#define INF 999999

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
    int nLinks;
    char *id;
    node *root;
};

struct _data{
    trunk *table;
    int nv;
    int na;
};

int Height(node *n);
int Max(int a, int b);
int Balance (node * root);
void CutTree(node * tree);
void CutTrunk(trunk *table);
void CleanMem(trunk * table, int n_vertex);
void InitVertex(trunk *table);
void InitTree(trunk * table, int n_vertex);
trunk *CreateTrunk(int n_vertex);
node *CreateLeaf(int name, double cost);
node* RotateRight(node * y);
node* RotateLeft(node * x);
node *FindNode(node *tree, int name);
node *AVLInsert(node * root, int name, double cost);

#endif /* Binary_Tree_h */