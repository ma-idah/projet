#include "csvMatrix.h"
#include <stdio.h>
#include <stdlib.h>


CsvMatrix *initCsvMatrix(unsigned int nbRows, unsigned int nbCols) {
    CsvMatrix *mat = malloc(sizeof(CsvMatrix));
    mat->nbCols = nbCols;
    mat->nbRows = nbRows;
    return mat;
}

void printMatrix(const CsvMatrix *mat) {
    for (int i=0; i<mat->nbRows; i++) {
        for (int j=0; j<mat->nbCols; j++) {
            printf("| %s ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}


void deleteMatrix(CsvMatrix *mat) {
    free(mat);
    mat = NULL;
}