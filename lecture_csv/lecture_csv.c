
#include "lecture_csv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>





void CsvRowsColsCounter(unsigned int *rows, unsigned int *cols, const char *fileName) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) { //gestion d'erreur
        perror("Erreur lors de l'ouverture du fichier\n");
        exit(1);
    }

    char line[1000];
    char *token;
    int row = 0;
    int column = 0;
    int maxColumn;

    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        maxColumn = column;
        column = 0;
        char lineFirstToken[50];

        fgets(line, 1000, f); // on prend ligne par ligne
        token = strtok(line, ","); //on commence à découper la ligne avec "," comme séparateur
        strcpy(lineFirstToken, token);
        
        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            column++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(f);

    *rows = row;
    *cols = maxColumn;
}

int FillMatrix(CsvMatrix *mat, const char *fileName) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) { //gestion d'erreur
        perror("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }

    char line[1000];
    char *token;
    int row = 0;
    int column = 0;
    char lineFirstToken[50];

    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        column = 0;
        fgets(line, 1000, f); // on prend ligne par ligne
        if (strcmp(line,lineFirstToken) == 0) { //fix pour un problème de fgets: si la dernière ligne du fichier est vide, alors fgets ne change pas line, alors que feof(f)=false, 
            mat->nbRows--;                      //donc la boucle fait un tour de trop et on se retrouve avec une matrice dont la dernière ligne contient le premier élément de celle d'avant
            break;
        }

        token = strtok(line, ","); //on commence à découper la ligne avec "," comme séparateur
        strcpy(lineFirstToken, token);

        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            strncpy(mat->matrix[row][column], token, MAX_STRING_SIZE -1 );
            token = strtok(NULL, ",");
            column++;
        }
        row++;
    }

    fclose(f);

    for (int i=0; i<mat->nbRows; i++) { //on enlève le saut de ligne pour les chaînes de la dernière colonne
        mat->matrix[i][mat->nbCols-1][strlen(mat->matrix[i][mat->nbCols-1])-1] = '\0';
    }

    return 0;
}



