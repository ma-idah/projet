#include "condorcet_base.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


DualMatrix *initDualMatrix(int nbRowsCols) {
    DualMatrix *mat = malloc(sizeof(DualMatrix));
    if (mat == NULL) {
        perror("Problème malloc");
        exit(1);
    }
    mat->nbRows = nbRowsCols;
    mat->nbCols = nbRowsCols;
    return mat;
}

void deleteDualMatrix(DualMatrix *mat) {
    free(mat);
    mat = NULL;
}

//renvoie un entier représentant le résultat du duel (pos(+): 1 gagne; neg(-): 2 gagne; 0: égalité)
//place dans tabResult les scores des deux candidats
int SingleDualResult(const CsvMatrix *mat, int index1, int index2, int tabResult[2]) { 
    int score = 0;
    for (int i=1; i<mat->nbRows; i++) {
        //on compare pour chaque votant le classement des deux candidats
        if (atoi(mat->matrix[i][index1]) < atoi(mat->matrix[i][index2])) {
            score++;
            tabResult[0]++;
        } else if (atoi(mat->matrix[i][index1]) > atoi(mat->matrix[i][index2])) {
            score--;
            tabResult[1]++;
        } else {
            tabResult[0]++;
            tabResult[1]++;
        }
    }
    return score;
}

void fillDualMatrix(const CsvMatrix *mat, struct s_DualMatrix *dualMat) {
    int nbCandidates = mat->nbCols-4;
    int *tabResult = malloc(sizeof(int)*2);
    int score;

    for (int i=0; i<nbCandidates; i++) { //pour chaque candidat
        for (int j=i; j<nbCandidates; j++) { //pour chaque adversaire dont on a pas encore simulé le duel
            if (i != j) {
                //printf("Duel entre %s et %s:\n", mat->matrix[0][i+4], mat->matrix[0][j+4]);
                tabResult[0] = tabResult[1] = 0;
                score = SingleDualResult(mat, i+4, j+4, tabResult);
                //printf("%d contre %d, score : %d\n", tabResult[0], tabResult[1], score);
                //on remplie les cases de la matrice de duel avec les scores des deux adversaires
                dualMat->matrix[i][j] = tabResult[0]; 
                dualMat->matrix[j][i] = tabResult[1];
                /*if (tabResult[0] > tabResult[1]) {
                    printf("candidat 1 a gangné ce duel!\n\n");
                }*/
            } else {
                dualMat->matrix[i][j] = 0; //ces cases ne seront pas consultées de toute manière, je vais peut être simplement supprimer cette ligne 
            }
        }
    }

    free(tabResult);
}

//renvoie l'indice du gagnant, et -1 si pas de gagnant
int DualMatrixWinner(DualMatrix *dualMat) {
    int victoires;
    for (int i=0; i<dualMat->nbRows; i++) { //parcours des lignes
        victoires = 0;
        for (int j=0; j<dualMat->nbCols; j++) { //parcours des colonnes
            if (i != j) {
                if (dualMat->matrix[i][j] < dualMat->matrix[j][i]) { //i a perdu contre j
                    break;
                } else {
                    victoires++;
                }
            }
        }
        if (victoires == dualMat->nbCols-1) { // i a gagné tous ses duels
            return i;
        }
    }
    return -1;
}

void printDualMatrix(const DualMatrix *mat) {
    for (int k=0; k<mat->nbCols; k++) {
            printf("----------------"); 
        }
        printf("\n");

    for (int i=0; i<mat->nbRows; i++) {
        for (int j=0; j<mat->nbCols; j++) {
            printf("|\t%d\t", mat->matrix[i][j]);
        }
        
        printf("|\n");
        for (int k=0; k<mat->nbCols; k++) {
            printf("----------------");
        }
        printf("\n");
    }
}

int computeCondorcetWinner(CsvMatrix *mat) {
    DualMatrix *dualMat = initDualMatrix(mat->nbCols-4);
    fillDualMatrix(mat, dualMat);

    int vainqueur = DualMatrixWinner(dualMat);
    if (vainqueur != -1) {
        char *nomVainqueur = mat->matrix[0][vainqueur+4];
        printf("Le vainqueur du vote selon la méthode de Condorcet est: %s !\n", nomVainqueur);
    } else {
        printf("La méthode de Condorcet n'a pas trouvé de vainqueur. C'est le paradoxe de Condorcet.\n");
    }

    deleteDualMatrix(dualMat);

    return vainqueur;
}