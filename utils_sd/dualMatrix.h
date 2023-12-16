#ifndef __DUALMATRIX__H__
#define __DUALMATRIX__H__

#include "../lecture_csv/lecture_csv.h"
#include "csvMatrix.h"



typedef struct s_DualMatrix {
    char namesTab[MAX_COLUMNS-4][MAX_STRING_SIZE];
    int matrix[MAX_ROWS-1][MAX_COLUMNS-4];
    int nbRows;
    int nbCols;
} DualMatrix;


/// @brief Crée et alloue de la mémoire pour une matrice de Duels
/// @param nbRowsCols nombre de lignes/colonnes (= nombre de candiats)
/// @return pointeur vers matrice de Duels
DualMatrix *initDualMatrix(int nbRowsCols);

/// @brief supprime la matrice de duels mat et désalloue son pointeur
/// @param mat matrice de duels à supprimer
void deleteDualMatrix(DualMatrix *mat);

/// @brief met en forme et affiche sur stdout la matrice de duels
/// @param mat matrice de duels
void printDualMatrix(const DualMatrix *mat);

/// @brief Remplis uniquement le tableau des noms de dMat
/// @param dMat matrice de duels initialisée avec initDualMat
/// @param mat matrice Csv remplie
void fillOnlyNamesDualMat(DualMatrix *dMat, CsvMatrix *mat);



#endif