#include "../lecture_csv.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CANDIDATES 46 //MAX_COLUMNS - 4 
typedef struct s_OrientedArrow {
    int from;
    char fromName[MAX_STRING_SIZE];
    int to;
    char toName[MAX_STRING_SIZE];
    int weighting;
} OrientedArrow;

typedef struct s_DualGraph {
    char nodes[MAX_CANDIDATES][MAX_STRING_SIZE];
    struct s_OrientedArrow arrows[MAX_CANDIDATES * (MAX_CANDIDATES-1) / 2];
} DualGraph;

typedef struct s_DualMatrix {
    int matrix[MAX_ROWS-1][MAX_COLUMNS-4];
    int nbRows;
    int nbCols;
} DualMatrix;

DualGraph *initDualGraph() {
    DualGraph *graph = malloc(sizeof(DualGraph));
    if (graph == NULL) {
        perror("Problème malloc");
        exit(1);
    }
    return graph;
}

void deleteDualGraph(DualGraph *graph) {
    free(graph);
    graph = NULL;
}

DualMatrix *initDualMatrix(int rows, int cols) {
    DualMatrix *mat = malloc(sizeof(DualMatrix));
    if (mat == NULL) {
        perror("Problème malloc");
        exit(1);
    }
    mat->nbRows = rows;
    mat->nbCols = cols;
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

    for (int i=0; i<nbCandidates; i++) {
        for (int j=i; j<nbCandidates; j++) {
            if (i != j) {
                printf("Duel entre %s et %s:\n", mat->matrix[0][i+4], mat->matrix[0][j+4]);
                tabResult[0] = tabResult[1] = 0;
                score = SingleDualResult(mat, i+4, j+4, tabResult);
                printf("%d contre %d, score : %d\n", tabResult[0], tabResult[1], score);
                dualMat->matrix[i][j] = tabResult[0];
                dualMat->matrix[j][i] = tabResult[1];
                if (tabResult[0] > tabResult[1]) {
                    printf("candidat 1 a gangné ce duel!\n\n");
                }
            } else {
                dualMat->matrix[i][j] = 0; //ces cases ne seront pas consultées de toute manière, je vais peut être simplement supprimer cette ligne 
            }
        }
    }
}

void printDualMatrix(const DualMatrix *mat) {
    printf("oui\n");
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

int main(int argc, char const *argv[])
{
    char file[MAX_STRING_SIZE];
    strncpy(file, argv[1], MAX_STRING_SIZE);
    int rows, cols;
    CsvRowsColsCounter(&rows, &cols, file);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, file);
    printMatrix(mat);

    DualMatrix *dualMat = initDualMatrix(cols-4, cols-4);
    fillDualMatrix(mat, dualMat);
    printDualMatrix(dualMat);

    //printf("\n\n %d\n", dualMat->matrix[1][0]);

    return 0;
}

