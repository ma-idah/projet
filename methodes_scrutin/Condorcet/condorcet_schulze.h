#ifndef __CONDORCETSCHULZE__H__
#define __CONDORCETSCHULZE__H__

#include "../../lecture_csv/lecture_csv.h"
#include "condorcet_base.h"
#include "condorcet_schulze.h"
#include "../../utils_sd/graphdyn.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/// @brief trouve le chemin avec le maillon faible le plus fort entre cur et destination
/// @param[in] cur noeud courant (départ)
/// @param[in] dest noeud de destination
/// @param[out] minWeight le maillon faible 
/// @param[in] currentWeight 
void findStrongestPath(DynNode* cur, DynNode* dest, int* minWeight, int currentWeight, FILE *logfp);

/// @brief remplis pathMat avec les valeurs du chemin le plus fort pour chaque noeud
/// @param g graphe de duels
/// @param[out] pathMat matrice de chemins (vide)
void fillPathMatrix(DynGraph *g, DualMatrix *pathMat, FILE *logfp);

/// @brief remplis pathMat et désigne le.s gagnant.s en plaçant leurs noms dans le tableau winners
/// @param g graphe de duels
/// @param[out] winners tableau de char* contenant le.s nom.s du.des gagnant.s
/// @param[out] pathMat matrice de chemins (vide)
/// @return le nombre de gagnants
int computeSchulzeWinner(DynGraph *g, char **winners, DualMatrix *pathMat, FILE *logfp);

/// @brief applique la méthode de Condorcet, puis celle de Schulze, et affiche sur logfp le résultat
/// @param file fichier csv à traiter
/// @param logfp fichier de sortie log (par défaut stdout)
void condorcetSchulzeMethod(char *file, FILE *logfp);



#endif