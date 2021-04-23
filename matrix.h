/******************************************************************************
 * (c) 2021 João Nabais & João Coelho
 *
 * NAME
 *   graphs.h
 *
 ******************************************************************************/

#ifndef MATRIX_H
#define MATRIX_H
#define ACS(x) (x-1)

void printMatrix(double* matrix, int nv);
void createMandV(graph* g, int numV);
int AccessM(int va, int vb);
void IniMatrix(double* matrix, int numV);

#endif
