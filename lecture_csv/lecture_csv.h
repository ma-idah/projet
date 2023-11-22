#ifndef __LECTURECSV__H__
#define __LECTURECSV__H__

#define MAX_ROWS 500
#define MAX_COLUMNS 50
#define MAX_STRING_SIZE 200

typedef struct s_CsvMatrix {
    char matrix[MAX_ROWS][MAX_COLUMNS][MAX_STRING_SIZE];
    int nbRows;
    int nbCols;
} CsvMatrix;

CsvMatrix *initCsvMatrix(unsigned int nbRows, unsigned int nbCols);

void CsvRowsColsCounter(unsigned int *rows, unsigned int *cols, const char *fileName);

int FillMatrix(CsvMatrix *mat, const char *fileName);

void printMatrix(const CsvMatrix *mat);









#endif