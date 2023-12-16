#ifndef __GRAPHDYN__H__
#define __GRAPHDYN__H__

#include <stdio.h>
#include <stdlib.h>
#include "utils_sd.h"


struct t_graph_dyn_arrow;

typedef struct t_graph_dyn_node {
    char id[MAX_STRING_SIZE];
    struct t_graph_dyn_arrow **arrowsTab;
    unsigned int arrowsNb;
    unsigned int visited;
} DynNode;

typedef struct t_graph_dyn_arrow {
    DynNode *from;
    DynNode *to;
    int weight;
} DynArrow;

typedef struct t_graph_dyn {
    DynNode **nodesTab;
    unsigned int nodesNb;
} DynGraph;

/// @brief crée un graphe dynamique vide
/// @return pointeur vers DynGraph créé
DynGraph *initDynGraph();

/// @brief crée un node de graph dynamique vide avec un id
/// @param id identifiant du node
/// @return pointeur vers le node
DynNode *initDynNode(char *id);

/// @brief supprime et libère la mémoire d'un DynGraph
/// @param graph graph à supprimer
void deleteDynGraph(DynGraph *graph);

/// @brief ajoute un arc dans la liste d'arc d'un node
/// @param from node duquel part l'arc
/// @param to node vers lequel pointe l'arc
/// @param weight poids de l'arc
void addArrowDynNode(DynNode *from, DynNode *to, int weight);

/// @brief remplis entièrement (noeuds + arcs) un graphe dynamique
/// @param graph graph à remplir (supposé vide)
/// @param dualMat matrice de duel pour remplir les arcs
void addAllNodesAndArrowsDynGraph(DynGraph *graph, DualMatrix *dualMat);

/// @brief affiche sur stdout le contenu du graphe en paramètre
/// @param graph graphe à afficher
void printDynGraph(DynGraph *graph);


/// @brief 
/// @param id 
/// @param graph 
void addNodeDynGraph(char *id, DynGraph *graph);


#endif