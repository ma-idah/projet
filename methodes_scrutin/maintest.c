#include <stdlib.h>
#include <stdio.h>
#include "lecture_csv.h"
#include "uninominal.h"
#include "uninominal_2.h"
#include <string.h>


int main(int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr,"Usage: %s <fichier.csv>\n", argv[0]);
        exit(1);
    }

    char fichier[30];
    strncpy(fichier, argv[1], 30);

    int rows,cols;
    CsvRowsColsCounter(&rows, &cols, argv[1]);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, fichier);
    printf("Affichage de la matrice de vote:\n");
    printMatrix(mat);
    printf("\n");

    int sommeCols[cols-4];

    printf("Vainqueur de la méthode uninominale à un tour:\n");
    afficher_vainqueur(mat, sommeCols);

    printf("\nMaintenant, appliquons la méthode uninominale à deux tours:\n");
    afficher_vainqueurs_T1(mat, sommeCols);

    afficher_vainqueurs_T2(mat, sommeCols);



    // Libérer la mémoire allouée dynamiquement pour la matrice
    deleteMatrix(mat);

    return 0;
}
