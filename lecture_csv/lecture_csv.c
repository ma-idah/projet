
#include "lecture_csv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct s_CsvMatrix {
    char *matrix[MAX_ROWS][MAX_COLUMNS][MAX_STRING_SIZE];
    int nbRows;
    int nbCols;
} CsvMatrix;

int createFillMatrix(CsvMatrix *mat, const char *fileName) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) { //gestion d'erreur
        perror("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }

    //mat->matrix = malloc(MAX_ROWS * MAX_COLUMNS * MAX_STRING_SIZE * sizeof(char));
    char line[1000];
    char *token;
    int row = 0;
    int column = 0;

    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        column = 0;
        fgets(line, 1000, f); // on prend ligne par ligne
        token = strtok(line, ","); //on commence à découper la ligne avec "," comme séparateur
        

        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            printf("%s\n", token);
            strcpy(&(mat->matrix[row][column]),token);
            token = strtok(NULL, ",");
            column++;
        }
        row++;
    }

    fclose(f);

    mat->nbCols = row+1;
    mat->nbRows = column+1;
    return 0;
}

void printMatrix(const CsvMatrix *mat) {
    for (int i=0; i<mat->nbRows; i++) {
        for (int j=0; j<mat->nbCols; j++) {
            printf("%s | ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{

    // Test arguments valides
    if (argc != 2) {
        fprintf(stderr, "Usage: %s nom_fichier\n", argv[0]);
        exit(1);
    }
    char fileName[100];
    strcpy(fileName,argv[1]);


    CsvMatrix mat;
    int a = createFillMatrix(&mat, fileName);
    printf("%d\n\n",a);
    printMatrix(&mat);
    return 0;
}
