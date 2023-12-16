#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "dualMatrix.h"




DualMatrix *initDualMatrix(int nbRowsCols) {
    DualMatrix *mat = malloc(sizeof(DualMatrix));
    if (mat == NULL) {
        perror("Problème malloc");
        exit(1);
    }
    mat->nbRows = nbRowsCols;
    mat->nbCols = nbRowsCols;
    return mat;
}


void deleteDualMatrix(DualMatrix *mat) {
    free(mat);
    mat = NULL;
}

void printDualMatrix(const DualMatrix *mat) {

    printf("Participants: ");
    for(int i=0; i<mat->nbCols; i++) {
        printf("%s, ", mat->namesTab[i]);
    }
    printf("\n\n");

    for (int k=0; k<mat->nbCols; k++) {
            printf("----------------"); 
        }
        printf("\n");

    for (int i=0; i<mat->nbRows; i++) {
        for (int j=0; j<mat->nbCols; j++) {
            printf("|\t%d\t", mat->matrix[i][j]);
        }
        
        printf("|\n");
        for (int k=0; k<mat->nbCols; k++) {
            printf("----------------");
        }
        printf("\n");
    }
}

void fillOnlyNamesDualMat(DualMatrix *dMat, CsvMatrix *mat) {
    for (int i=4; i<mat->nbCols; i++) { //remplissage du tableaux des noms
        strncpy(dMat->namesTab[i-4], mat->matrix[0][i], MAX_STRING_SIZE);
    }
}