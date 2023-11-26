// uninominal.c

#include "lecture_csv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void calculerSommecolonnes(const CsvMatrix* matrice, int sommeColonnes[]) {
    // Vérifier si la matrice a suffisamment de lignes et de colonnes
    if (matrice->nbRows > 1 && matrice->nbCols > 4) {
        // Initialiser le tableau des sommes
        for (int i = 0; i < matrice->nbCols - 4; ++i) {
            sommeColonnes[i] = 0;
        }

        // Parcourir la matrice en commençant par la deuxième ligne et la cinquième colonne
        for (int i = 1; i < matrice->nbRows; ++i) {
            for (int j = 4; j < matrice->nbCols; ++j) {
                // Ajouter la valeur de la cellule à la somme correspondante
                sommeColonnes[j - 4] += atoi(matrice->matrix[i][j]);
            }
        }
    } else {
        printf("La matrice n'a pas assez de lignes ou de colonnes pour effectuer le calcul.\n");
    }
}

int trouverColonneMin(const int sommeColonnes[], int taille) {
    int indiceMin = 0;
    int min = sommeColonnes[0];

    for (int i = 1; i < taille; ++i) {
        if (sommeColonnes[i] < min) {
            min = sommeColonnes[i];
            indiceMin = i;
        }
    }

    return indiceMin + 4;  // Ajouter 4 pour obtenir le numéro réel de la colonne
}

void afficher_vainqueur(CsvMatrix* matrice, int sommeColonnes[]) {
    calculerSommecolonnes(matrice, sommeColonnes);
    int colMin = trouverColonneMin(sommeColonnes, matrice->nbCols - 4);
    //printf("colMin : %d\n", colMin);
    printf("Le vainqueur est %s\n", matrice->matrix[0][colMin]);
}
