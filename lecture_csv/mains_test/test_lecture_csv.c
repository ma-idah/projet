#include "../lecture_csv.h"
#include "../../utils_sd/csvMatrix.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char const *argv[])
{
    // Test arguments valides
    if (argc != 2) {
        fprintf(stderr, "Usage: %s nom_fichier\n", argv[0]);
        exit(1);
    }
    char fileName[100];
    strcpy(fileName,argv[1]);

    unsigned int rows, cols;

    CsvRowsColsCounter(&rows, &cols, fileName);

    CsvMatrix *mat = initCsvMatrix((unsigned int)rows, (unsigned int)cols);
    int a = FillMatrix(mat, fileName);
    printMatrix(mat);
    printf("ohe\n");
    return 0;
}