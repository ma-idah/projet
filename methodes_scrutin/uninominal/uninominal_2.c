#include "../../lecture_csv/lecture_csv.h"
#include "uninominal.h"
#include "uninominal_2.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

DeuxIndices trouverDeuxColonnesMin(const int sommeColonnes[], int taille) {
    DeuxIndices indices;

    // Allocation dynamique de la structure DeuxIndices
    indices = (DeuxIndices)malloc(sizeof(struct s_indice));

    // Vérification de l'allocation
    if (indices == NULL) {
        perror("Erreur lors de l'allocation de DeuxIndices");
        exit(EXIT_FAILURE);
    }

    // Initialiser les indices avec des valeurs par défaut
    indices->indiceMin1 = 0;
    indices->indiceMin2 = 1;

    // Assurer que min1 est inférieur à min2
    if (sommeColonnes[indices->indiceMin1] > sommeColonnes[indices->indiceMin2]) {
        int temp = indices->indiceMin1;
        indices->indiceMin1 = indices->indiceMin2;
        indices->indiceMin2 = temp;
    }

    for (int i = 2; i < taille; ++i) {
        if (sommeColonnes[i] < sommeColonnes[indices->indiceMin1]) {
            indices->indiceMin2 = indices->indiceMin1;
            indices->indiceMin1 = i;
        } else if (sommeColonnes[i] < sommeColonnes[indices->indiceMin2]) {
            indices->indiceMin2 = i;
        }
    }

    // Ajouter 4 pour obtenir les numéros réels des colonnes
    indices->indiceMin1 += 4;
    indices->indiceMin2 += 4;

    return indices;
}

void deleteIndices(DeuxIndices ind) {
    // Libérer la mémoire allouée pour les champs de la structure
    free(ind);

    // Remettre à NULL pour éviter un accès accidentel
    ind = NULL;
}

void afficher_vainqueurs_T1(const CsvMatrix* matrice, int sommeColonnes[]) {
    calculerSommecolonnes(matrice, sommeColonnes);
    DeuxIndices colMins = trouverDeuxColonnesMin(sommeColonnes, matrice->nbCols - 4);
    int indice1 = colMins->indiceMin1;
    int indice2 = colMins->indiceMin2;
    printf("Les vainqueurs du tour 1 sont : %s et %s\n Passons au tour 2.\n", matrice->matrix[0][indice1], matrice->matrix[0][indice2]);

    deleteIndices(colMins);
}



void afficher_vainqueurs_T2(const CsvMatrix *mat, int sommeColonnes[]) {
    calculerSommecolonnes(mat, sommeColonnes);
    DeuxIndices colMins = trouverDeuxColonnesMin(sommeColonnes, mat->nbCols - 4);

    int scoreC1 = 0;
    int scoreC2 = 0;

    int ind1 = colMins->indiceMin1;
    int ind2 = colMins->indiceMin2;

    for (int i=0; i<mat->nbRows; i++) {
        if (atoi(mat->matrix[i][ind1]) < atoi(mat->matrix[i][ind2])) { //si un votant a placé plus haut un candidat que l'autre, il gagne un vote
            scoreC1++;
        } else if (atoi(mat->matrix[i][ind1]) > atoi(mat->matrix[i][ind2])) {
            scoreC2++;
        } //si égalité dans le classement, aucun point distribué
    }

    int indiceVainqueur, scoreVainqueur;
    if (scoreC1 > scoreC2) { //on élit le vainqueur
        indiceVainqueur = ind1;
        scoreVainqueur = scoreC1;
    } else if (scoreC1 < scoreC2) {
        indiceVainqueur = ind2;
        scoreVainqueur = scoreC2;
    } else {
        printf("Les deux vainqueurs du premier tour sont arrivés à égalité au deuxième tour. Il n'y a donc pas de vainqueur officiel\n");
        return;
    }
    int totalVotes = scoreC1 + scoreC2;
    printf("Le vainqueur du second tour est %s avec %d%% des voix à ce tour tour.\n", mat->matrix[0][indiceVainqueur], 100*scoreVainqueur/totalVotes);

    deleteIndices(colMins);
}

