// uninominal_2.h

#ifndef UNINOMINAL_2_H
#define UNINOMINAL_2_H

#include "lecture_csv.h"
#include "uninominal.h"

// Déclaration de la structure pour stocker les deux indices
struct s_indice {
    int indiceMin1;
    int indiceMin2;

};

typedef struct s_indice *DeuxIndices;

// Déclaration de la fonction pour trouver les deux colonnes avec les sommes les plus faibles
DeuxIndices trouverDeuxColonnesMin(const int sommeColonnes[], int taille);

// Déclaration de la fonction pour afficher les vainqueurs du tour 1
void afficher_vainqueurs_T1(const CsvMatrix* matrice, int sommeColonnes[]);

//Free la structure DeuxIndices
void deleteIndices(DeuxIndices ind);

void afficher_vainqueurs_T2(const CsvMatrix *mat, int sommeColonnes[]);

#endif  // UNINOMINAL_2_H
