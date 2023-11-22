
#include "lecture_csv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>



CsvMatrix *initCsvMatrix(unsigned int nbRows, unsigned int nbCols) {
    CsvMatrix *mat = malloc(sizeof(CsvMatrix));
    mat->nbCols = nbCols;
    mat->nbRows = nbRows;
    return mat;
}

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

    printf("1\n");
    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        maxColumn = column;
        column = 0;
        fgets(line, 1000, f); // on prend ligne par ligne
        printf("'%s'\n",line); //DEBUG
        if (strcmp(line,"") == 0) {
            break; //la ligne est vide
        }
        token = strtok(line, ","); //on commence à découper la ligne avec "," comme séparateur
        

        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            column++;
            token = strtok(NULL, ",");
        }
        row++;
    }
    fclose(f);

    *rows = row;
    *cols = maxColumn;
    printf("rows: %d colums: %d\n\n", *rows, *cols);
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

    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        column = 0;
        fgets(line, 1000, f); // on prend ligne par ligne
        token = strtok(line, ","); //on commence à découper la ligne avec "," comme séparateur

        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            strncpy(mat->matrix[row][column], token, MAX_STRING_SIZE -1 );
            token = strtok(NULL, ",");
            column++;
        }
        row++;
    }

    fclose(f);

    mat->nbRows--; //ATTENTION: c'est un fix temporaire pour le problème de la ligne en trop, c pas du tout sécurisé car si on un fichier sans ligne vide à la fin on perd une ligne

    return 0;
}

void printMatrix(const CsvMatrix *mat) {
    for (int i=0; i<mat->nbRows; i++) {
        for (int j=0; j<mat->nbCols; j++) {
            printf("| %s ", mat->matrix[i][j]);
        }
        printf("\n");
    }
}

/*int main(int argc, char const *argv[])
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
    return 0;
}*/

//TODO PAS FINI - marche avec les fichiers qui n'ont pas une ligne vide en tant que dernière ligne
//                quand le programme lit cette dernière ligne vide, fgets ne retourne pas une string vide 
//                mais composée de la première valeur de la ligne précédente (???)
//
//                Du coup un fix possible ça serait de faire -1 aux nombres de rows quand on les compte pour
//                passer le total à la struct, mais ça voudrait dire que si le fichier n'a pas de derniere ligne
//                vide ça casse tout :/

//      NOTE: fix temporaire ajouté ligne 85, ça marche qu'avec les fichiers qui ont une ligne vide en tant que dernière du coup


//TODO Nettoyer printf de debug, commentaires doxygen, supprimer main, faire .h