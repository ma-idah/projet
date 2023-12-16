#include <string.h>

#include "graphdyn.h"
#include "../lecture_csv/lecture_csv.h"

DynGraph *initDynGraph() {
    DynGraph *g = (DynGraph *)malloc(sizeof(DynGraph));
    g->nodesTab = (DynNode **)malloc(2 * sizeof(DynNode *));
    g->nodesNb = 0;
    return g;
}

DynNode *initDynNode(char *id) {
    DynNode *n = (DynNode *)malloc(sizeof(DynNode));
    strcpy(n->id, id);
    n->arrowsNb = 0;
    n->visited = 0;
    return n;
}


void deleteDynGraph(DynGraph *graph) {
    // deleting arrows and nodes
    for (int i=0; i<graph->nodesNb; i++) {
        for (int j=0; j<graph->nodesTab[i]->arrowsNb; j++) {
            free(graph->nodesTab[i]->arrowsTab[j]);
        }
        free(graph->nodesTab[i]->arrowsTab);
        free(graph->nodesTab[i]);
    }
    free(graph->nodesTab);

    free(graph);
    graph = NULL;
}

void addArrowDynNode(DynNode *from, DynNode *to, int weight) {
    DynArrow *arr = malloc(sizeof(DynArrow));
    arr->from = from;
    arr->to = to;
    arr->weight = weight;

    from->arrowsTab = realloc(from->arrowsTab, from->arrowsNb+1 * sizeof(DynArrow));
    from->arrowsTab[from->arrowsNb] = arr;
    from->arrowsNb++;
}

void addNodeDynGraph(char *id, DynGraph *graph) {
    DynNode *n = initDynNode(id);
    graph->nodesNb++;
    graph->nodesTab = (DynNode **)realloc(graph->nodesTab, graph->nodesNb * sizeof(DynNode));
    graph->nodesTab[graph->nodesNb-1] = n;

}

void addAllNodesAndArrowsDynGraph(DynGraph *graph, DualMatrix *dualMat) {
    //le indices de namesTab doivent correspondre aux indices de dualMat

    //ajout des noeuds
    graph->nodesTab = (DynNode **)realloc(graph->nodesTab, dualMat->nbCols * sizeof(DynNode));
    for (int i=0; i<dualMat->nbCols; i++) {
        DynNode *node = initDynNode(dualMat->namesTab[i]);
        graph->nodesTab[graph->nodesNb] = node;
        graph->nodesNb++;
    }

    //ajout des arcs
    for (int i=0; i<dualMat->nbRows; i++) {
        for (int j=i; j<dualMat->nbCols; j++) {
            if (i!=j) {
                if (dualMat->matrix[i][j] > dualMat->matrix[j][i]) { //si i gagne on ajoute un arc allant de i à j
                addArrowDynNode(graph->nodesTab[i], graph->nodesTab[j], abs(dualMat->matrix[i][j] - dualMat->matrix[j][i]));

                } else if (dualMat->matrix[i][j] < dualMat->matrix[j][i]) { // l'inverse
                addArrowDynNode(graph->nodesTab[j], graph->nodesTab[i], abs(dualMat->matrix[i][j] - dualMat->matrix[j][i]));
                
                } //si égalité, pas d'arc
            }
           
        }
    }
}

void printDynGraph(DynGraph *graph) {
    for (int i=0; i<graph->nodesNb; i++) {
        printf("(%s):\n", graph->nodesTab[i]->id);
        DynNode *curNode = graph->nodesTab[i];
        for (int j=0; j<graph->nodesTab[i]->arrowsNb; j++) {
            printf("\t(%s) ---%d--> (%s)\n", curNode->id, curNode->arrowsTab[j]->weight, curNode->arrowsTab[j]->to->id);
        }
    }
}


/*
int main(int argc, char const *argv[])
{
    //Matrice CSV
    char file[MAX_STRING_SIZE];
    strncpy(file, argv[1], MAX_STRING_SIZE);
    int rows, cols;
    CsvRowsColsCounter(&rows, &cols, file);
    CsvMatrix *mat = initCsvMatrix(rows, cols);
    FillMatrix(mat, file);
    printMatrix(mat);

    //Matrice de duels
    DualMatrix *dualMat = initDualMatrix(cols-4);
    fillDualMatrix(mat, dualMat);
    printDualMatrix(dualMat);

    int vainqueur = DualMatrixWinner(dualMat);
    if (vainqueur != -1) {
        printf("vainqueur : n°%d\n", vainqueur);
    }


    //Graph dynamique
    DynGraph *g = initDynGraph();
    addAllNodesAndArrowsDynGraph(g, dualMat);
    printDynGraph(g);


    //CLEANUP
    deleteDualMatrix(dualMat);
    deleteMatrix(mat);
    deleteDynGraph(g);


    return 0;
}
*/
