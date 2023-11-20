#ifndef __LISTE__H__
#define __LISTE__H__

#include <stdio.h>

/* définition opaque du type CircularList */
typedef struct s_circularList CircList;
typedef CircList *ptrCircList;

/**
 * @brief Constructeur
 * 
 */
CircList *createCircList();

/**
 * @brief Destructeur
 * 
 * @param[in] cl: CircList à supprimer
 */
void deleteCircList(ptrCircList *cl);

/**
 * @brief Introduit un élément à la tête (début) de la liste
 * 
 * @param[out] cl: liste
 * @param[in] val: valeur à insérer
 * @return CircList* 
 */
CircList *circListPush_head(CircList *cl, void *val);

/**
 * @brief Introduit un élément à la queue (fin) de la liste
 * 
 * @param[out] cl: liste
 * @param[in] val: valeur à insérer
 * @return CircList* 
 */
CircList *circListPush_tail(CircList *cl, void *val);

/**
 * @brief Retourne la liste sans l'élément de tête, attention faire un top avant pour récupérer la tête
 * 
 * @param cl: liste
 * @return CircList* 
 */
CircList *circListPop_head(CircList *cl);

/**
 * @brief Retourne la liste sans l'élément de queue, attention faire un bottom avant pour récupérer la tête
 * 
 * @param cl: liste
 * @return CircList* 
 */
CircList *circListPop_tail(CircList *cl);

/**
 * @brief Renvoie la valeur du premier élément de la liste, attention renvoie null si liste vide
 * 
 * @param cl: liste
 * @return void* 
 */
void *circListTop(CircList *cl);

/**
 * @brief Renvoie la valeur du dernier élément de la liste, attention renvoie null si liste vide
 * 
 * @param cl: liste
 * @return void* 
 */
void *circListBottom(CircList *cl);


/**
 * @brief Affiche les éléments de la liste si ils sont des int, /!\ fonction de test: non sécurisée
 * 
 * @param cl: liste
 */
void *circListPrint_int(CircList *cl);

#endif