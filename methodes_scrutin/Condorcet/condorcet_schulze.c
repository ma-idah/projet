#include "../../lecture_csv/lecture_csv.h"
#include "condorcet_base.h"
#include "condorcet_schulze.h"
#include "../../utils_sd/utils_sd.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


//Heuristique du chemin gagnant

void findStrongestPath(DynNode* cur, DynNode* dest, int* maxMinWeight, int currentWeight, FILE *logfp) {
    cur->visited = 1;
    fprintf(logfp, "[FINDPATH] On visite le noeud %s\n", cur->id);

    // Parcours des arcs du nœud actuel
    for (unsigned int i = 0; i < cur->arrowsNb; ++i) {
        DynArrow* arr = cur->arrowsTab[i];

        if (!(arr->to->visited)) {
            int newWeight = arr->weight < currentWeight ? arr->weight : currentWeight;
            fprintf(logfp, "[FINDPATH]\tnoeud: %s | newWeight : %d\n", arr->to->id, newWeight);
            if (arr->to == dest) {
                if (newWeight > *maxMinWeight) {
                    *maxMinWeight = newWeight;
                }
            } else {
                findStrongestPath(arr->to, dest, maxMinWeight, newWeight, logfp);
            }
        }
    }

    cur->visited = 0;
}

void fillPathMatrix(DynGraph *g, DualMatrix *pathMat, FILE *logfp) {
    //pathMat : réutilisation du type dualMatrix mais ce n'est pas une matrice de duels
    //pathMat.matrix doit être vide et pathMat doit être init puis son tableau des noms rempli avec fillOnlyNamesDualMat()

    int maxMinWeight = 0;
    DynNode *depart;
    DynNode *dest;
    
    

    //remplir strgstPathMat
    for (int i = 0; i<g->nodesNb; i++) {
        for (int j = 0; j<g->nodesNb; j++) {
            if (i != j) {
                maxMinWeight = 0;
                DynNode *depart = g->nodesTab[i];
                DynNode *dest = g->nodesTab[j];

                fprintf(logfp, "[FILLPATHMATRIX] Recherche du plus gros maillon faible du chemin %s ---> %s", depart->id, dest->id);
                findStrongestPath(depart, dest, &maxMinWeight, 50, logfp);

                fprintf(logfp, "[FILLPATHMATRIX] Plus gros maillon faible du chemin %s ---> %s:", depart->id, dest->id);
                fprintf(logfp, " %d\n\n", maxMinWeight);

                pathMat->matrix[i][j] = maxMinWeight;
            }
        }
    }
}

//renvoie le nombre de gagnants
int computeSchulzeWinner(DynGraph *g, char **winners, DualMatrix *pathMat, FILE *logfp) { 
    //pathMat : réutilisation du type dualMatrix mais ce n'est pas une matrice de duels
    //pathMat.matrix doit être vide et strgstPathMat doit être init puis son tableau des noms rempli avec fillOnlyNamesDualMat()

    int nbWinners = 0;

    
    
    fillPathMatrix(g, pathMat, logfp);

    for (int i=0; i<pathMat->nbRows; i++) {
        int currentIsWinning = 1; //booléen pour vérifier si le candidat 1 est gagnant potentiel
        for (int j=0; j<pathMat->nbCols; j++) {
            if (i != j) {
                if (pathMat->matrix[i][j] < pathMat->matrix[j][i]) {
                    currentIsWinning = 0;
                    //printf("%s: perdant\n", pathMat->namesTab[i]);
                }
            }
        }
        if (currentIsWinning) {
            strncpy(winners[nbWinners], pathMat->namesTab[i], MAX_STRING_SIZE);
            //printf("gagnant : %s\n", winners[nbWinners]);
            nbWinners++;
        }
    }
    
    

    return nbWinners;

}


void condorcetSchulzeMethod(char *file, FILE *logfp) {

    //matrice CSV
    int rows, cols;
    CsvRowsColsCounter(&rows, &cols, file);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, file);

    //CONDORCET SIMPLE

    //Matrice de duels
    DualMatrix *dualMat = initDualMatrix(cols-4);
    fillDualMatrix(mat, dualMat);

    int vainqueur = DualMatrixWinner(dualMat);
    if (vainqueur != -1) {
        fprintf(logfp, "[CONDORCET SIMPLE] Vainqueur de Condoret (avant schulze) : %s\n", dualMat->namesTab[vainqueur]);
    }
    fprintf(logfp, "\n");

    //SCHULZE

    //Graph dynamique
    DynGraph *g = initDynGraph();
    addAllNodesAndArrowsDynGraph(g, dualMat);
    fprintf(logfp, "Graphe de duels : \n\n");
    printDynGraph(g);
    fprintf(logfp, "\n");

    //CHEMIN GAGNANT
    DualMatrix *pathMat = initDualMatrix(cols-4);
    fillOnlyNamesDualMat(pathMat, mat);

    char *winners[g->nodesNb];
    int nbWinners;
    for (int i=0; i<g->nodesNb; i++) {
        winners[i] = (char *)malloc(MAX_STRING_SIZE * sizeof(char));
    }

    nbWinners = computeSchulzeWinner(g, winners, pathMat, logfp);

    fprintf(logfp, "\nMatrice des chemins les plus forts: \n");
    printDualMatrix(pathMat);

    //AFFICHAGE GAGNANT(S)
    fprintf(logfp, "\nGagnants : ");
    if (winners[0] != NULL) {printf("%s", winners[0]); }
    for (int i=1; i<nbWinners; i++) {
        fprintf(logfp, ", %s",winners[i]);
    }
    fprintf(logfp, "\n\n");

    //CLEANUP
    deleteDualMatrix(dualMat);
    deleteDualMatrix(pathMat);
    deleteMatrix(mat);
    deleteDynGraph(g);
    for (int i=0; i<g->nodesNb; i++) {
        free(winners[i]);
    }
    

}





