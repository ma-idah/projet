#include "../lecture_csv.h"
#include "condorcet_base.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CANDIDATES 46 //MAX_COLUMNS - 4 
typedef struct s_OrientedArrow {
    int fromIndex;
    //char fromName[MAX_STRING_SIZE]; //on peut retrouver le nom des candidats avec le tableau nodes
    int toIndex;
    //char toName[MAX_STRING_SIZE];
    int weighting;
} OrientedArrow;

typedef struct s_DualGraph {
    char nodes[MAX_CANDIDATES][MAX_STRING_SIZE];
    int nb_nodes;
    struct s_OrientedArrow *arrows[MAX_CANDIDATES * (MAX_CANDIDATES-1) / 2];
    int nb_arrows;
} DualGraph;



/*void GetCandidatesNameTab(CsvMatrix *mat, char **tab) {
    for (int i=4; i<mat->nbCols; i++) {
        strncpy(tab[i-4], mat->matrix[0][i], MAX_STRING_SIZE - 1);
    }
}*/

void GetCandidatesNameTab(CsvMatrix *mat, char **tab) {
    for (int i = 0; i < mat->nbCols - 4; i++) {
        tab[i] = malloc(MAX_STRING_SIZE * sizeof(char));
        if (tab[i] == NULL) {
            perror("Problème malloc pour tab[i]");
            exit(1);
        }
        strncpy(tab[i], mat->matrix[0][i + 4], MAX_STRING_SIZE);
    }
}

DualGraph *initDualGraph() {
    DualGraph *graph = malloc(sizeof(DualGraph));
    if (graph == NULL) {
        perror("Problème malloc");
        exit(1);
    }
    graph->nb_nodes = 0;
    graph->nb_arrows = 0;
    return graph;
}

void AddAllCandidatesDGraph(char **tabCandidates, int nb_candidates, DualGraph *graph) {
    graph->nb_nodes = 0;
    for (int i=0; i<nb_candidates; i++) {
        strncpy(graph->nodes[i], tabCandidates[i], MAX_STRING_SIZE);
        graph->nb_nodes++;
    }
}

void AddArrowDGraph(int CandIndex1, int CandIndex2, int score, DualGraph *graph) {
    //les indexs de candidats donnés doivent être ceux correspondant au tableau donné à graph
    OrientedArrow *arc = malloc(sizeof(OrientedArrow));
    if (score == 0) { //si score == 0, pas besoin d'arc
        free(arc);
        return;
    } else if (score > 0) {
        arc->fromIndex = CandIndex1;
        arc->toIndex = CandIndex2;
    } else { //si score négatif, c'est candidat 2 qui a gagné le duel
        arc->fromIndex = CandIndex2;
        arc->toIndex = CandIndex1;
        score = abs(score);
    }
    arc->weighting = score;
    graph->arrows[graph->nb_arrows] = arc;
    
}

void printDGArrow(OrientedArrow *arr, char **namesTab) {
    printf("\t(%s) ---%d--> (%s)", namesTab[arr->fromIndex], arr->weighting, namesTab[arr->fromIndex]);
}

void deleteDualGraph(DualGraph *graph) {
    //delete toutes les s_orientedArrows du tableau arrows avant 
    free(graph);
    graph = NULL;
}




//TODO VERIFIER QUE CA MARCHE BIEN
int main(int argc, char const *argv[])
{

    char file[MAX_STRING_SIZE];
    strncpy(file, argv[1], MAX_STRING_SIZE);
    int rows, cols;
    CsvRowsColsCounter(&rows, &cols, file);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, file);
    //printMatrix(mat);

    //CONDORCET BASE
    DualMatrix *dualMat = initDualMatrix(cols-4);
    fillDualMatrix(mat, dualMat);
    printDualMatrix(dualMat);

    int vainqueur = DualMatrixWinner(dualMat);
    if (vainqueur != -1) {
        printf("vainqueur : n°%d", vainqueur);
    } else {

    }
    

    //CONDORCET SCHULZE
    
    //printf("\n\n %d\n", dualMat->matrix[1][0]);
    DualGraph *graph = initDualGraph();

    char **namesTab = malloc( 2 * (mat->nbCols-4) * MAX_STRING_SIZE * sizeof(char));
    //SEGFAULT ICI ON VERRA DEMAIN
    //GetCandidatesNameTab(mat, namesTab); //pas oublier de free chaque case du tab
    //AddAllCandidatesDGraph(namesTab, mat->nbCols-4, graph);
    
    //CLEANUP
    deleteDualMatrix(dualMat);
    deleteMatrix(mat);
    deleteDualGraph(graph);

    free(namesTab);
    namesTab = NULL;

    return 0;
}

