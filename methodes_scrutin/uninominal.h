#ifndef UNINOMINAL_H
#define UNINOMINAL_H

#include "lecture_csv.h"

// Déclaration des fonctions

// Calcule les sommes des colonnes à partir de la cinquième colonne
void calculerSommecolonnes(const CsvMatrix* matrice, int sommeColonnes[]);

// Trouve la colonne avec la somme la plus faible
int trouverColonneMin(const int sommeColonnes[], int taille);

// Affiche le vainqueur en utilisant les fonctions précédentes
void afficher_vainqueur(const CsvMatrix* matrice, int sommeColonnes[]);

#endif  // UNINOMINAL_H
