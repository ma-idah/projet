#include "../lecture_csv.h"
#include "condorcet_base.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{

    if (argc != 2) {
        fprintf(stderr,"Usage: %s <nom_fichier.csv>\n",argv[0]);
        exit(1);
    }

    char file[MAX_STRING_SIZE];
    strncpy(file, argv[1], MAX_STRING_SIZE);
    int rows, cols;
    CsvRowsColsCounter(&rows, &cols, file);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, file);
    
    
    DualMatrix *dualMat = initDualMatrix(mat->nbCols-4);
    fillDualMatrix(mat, dualMat);
    printDualMatrix(dualMat);

    //CONDORCET BASE
    computeCondorcetWinner(mat);

    return 0;
}
