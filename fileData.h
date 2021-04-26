/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   fileData.h
 *
 ******************************************************************************/

#ifndef FILE_DATA_H
#define FILE_DATA_H
#include "graphs.h"
#include "binaryTree.h"
typedef struct lista_problemas probs;
struct lista_problemas {
    char problema[3];
    int vertice;
    int verticeOrK;     //segundo input: vertice ou distancia (k)
    probs* next;
};


probs* extractProbs (char* opt, FILE* fp);
void probFree(probs *p);
void openMapandOut(char* mapFile, FILE** fpMaps, FILE** fpout);
void selectProblems(probs* headProbs, FILE* fpout, data* g);
#endif
