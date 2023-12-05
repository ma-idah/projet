#ifndef __CONDORCETBASE__H__
#define __CONDORCETBASE__H__

#include "../lecture_csv.h"

typedef struct s_DualMatrix {
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

/// @brief renvoie un entier représentant le résultat du duel entre 2 candidats (pos(+): 1 gagne; neg(-): 2 gagne; 0: égalité)
///         place dans tabResult les scores des deux candidats
/// @param mat matrice découlant d'un fichier csv 
/// @param index1 index du candiaat n°1
/// @param index2 index du candiaat n°2
/// @param[out] tabResult score de chacun
/// @return différence de score (en valeur absolue ça donne le poids de l'arc sur un graph)
int SingleDualResult(const CsvMatrix *mat, int index1, int index2, int tabResult[2]);

/// @brief simule des duels entre chaque candidat, et remplis la matrice avec les résultats de ces duels
///         ex: dualMat->matrix[i][j] = score de i pour son duel contre j
/// @param mat matrice découlant d'un fichier csv
/// @param[out] dualMat matrice de duel à remplir 
void fillDualMatrix(const CsvMatrix *mat, struct s_DualMatrix *dualMat);

/// @brief trouve le gagnant, si il y en a un, d'une matrice de duel grâce à la méthode de Condorcet
/// @param dualMat matrice de duels
/// @return l'indice du gagant si il y en a un, sinon retourne -1
int DualMatrixWinner(DualMatrix *dualMat);

/// @brief met en forme et affiche sur stdout la matrice de duels
/// @param mat matrice de duels
void printDualMatrix(const DualMatrix *mat);

/// @brief Affiche qui est le vainqueur de Condorcet s'il y en a un
/// @param mat matrice découlant d'un fichier csv
/// @return indice du vainqueur (-4 par rapport à une matrice CSV) si il y en a un, sinon -1
int computeCondorcetWinner(CsvMatrix *mat);


#endif