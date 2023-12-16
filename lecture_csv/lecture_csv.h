#ifndef __LECTURECSV__H__
#define __LECTURECSV__H__

#include "../utils_sd/csvMatrix.h"

#define MAX_ROWS 500
#define MAX_COLUMNS 50
#define MAX_STRING_SIZE 200




void CsvRowsColsCounter(unsigned int *rows, unsigned int *cols, const char *fileName);

int FillMatrix(CsvMatrix *mat, const char *fileName);




//TODO commentaires doxygen



#endif