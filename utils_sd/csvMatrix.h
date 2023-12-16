#ifndef __CSV_MATRIX__
#define __CSV_MATRIX__

#define MAX_ROWS 500
#define MAX_COLUMNS 50
#define MAX_STRING_SIZE 200

typedef struct s_CsvMatrix {
    char matrix[MAX_ROWS][MAX_COLUMNS][MAX_STRING_SIZE];
    int nbRows;
    int nbCols;
} CsvMatrix;



CsvMatrix *initCsvMatrix(unsigned int nbRows, unsigned int nbCols);


void printMatrix(const CsvMatrix *mat);


void deleteMatrix(CsvMatrix *mat);




#endif