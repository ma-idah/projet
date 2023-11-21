
#include "liste.h"
#include <stdlib.h>


typedef struct s_listElement {
    void *value;
    struct ListElement *next;
    struct ListElement *prev;
} ListElement;

struct s_circularList {
    ListElement *head;
    ListElement *tail;
    unsigned int size;
};

CircList *createCircList() {
    CircList *cl = malloc(sizeof(CircList));
    cl->head = NULL;
    cl->tail = NULL;
    cl->size = 0;
}

void deleteCircList(ptrCircList *cl) {
    ListElement *toDel = (*cl)->head;
    while (toDel) {
        ListElement *del = toDel;
        toDel = toDel->next;
        free(toDel);
    }
    free(*cl);
    *cl = NULL;
}

CircList *circListPush_head(CircList *cl, void *val) {
    ListElement *toInsert = malloc(sizeof(ListElement));
    toInsert->value = val;
    if (cl->size == 0) { //si vide, un seul élément: toInsert
        toInsert->next = toInsert->prev = toInsert;

        cl->head = cl->tail = toInsert;
    } else {
        //connexion du nouvel elt avec la tête et la queue
        toInsert->prev = cl->tail; 
        toInsert->next = cl->head;

        //raccordage des autres
        cl->head->prev = toInsert;
        cl->tail->next = toInsert;

        cl->head = toInsert; //nvl elt est la tête
    }
    cl->size++;
    return cl;
}

CircList *circListPush_tail(CircList *cl, void *val) {
    ListElement *toInsert = malloc(sizeof(ListElement));
    toInsert->value = val;
    if (cl->size == 0) { //si vide, un seul élément: toInsert
        toInsert->next = toInsert->prev = toInsert;

        cl->head = cl->tail = toInsert;
    } else {
        //connexion du nouvel elt avec la tête et la queue
        toInsert->prev = cl->tail;
        toInsert->next = cl->head;

        //raccordage des autres
        cl->head->prev = toInsert;
        cl->tail->next = toInsert;

        cl->tail = toInsert; //nvl elt est la queue
    }
    cl->size++;
    return cl;
}

CircList *circListPop_head(CircList *cl) { //retourne la liste sans l'élément de tête, attention faire un top avant pour récupérer la tête
    if (cl->size == 0) {
        return cl;
    } else {
        ListElement *newHead = cl->head->next;
        newHead->prev = cl->tail;
        cl->tail->next = newHead;

        free(cl->head);
        cl->head = newHead;

        cl->size--;
        return cl;
    }
}

CircList *circListPop_tail(CircList *cl) { //retourne la liste sans l'élément de queue, attention faire un bottom avant pour récupérer la queue
    if (cl->size == 0) {
        return cl;
    } else {
        ListElement *newTail = cl->tail->prev;
        newTail->next = cl->head;
        cl->head->prev = newTail;

        free(cl->tail);
        cl->tail = newTail;

        cl->size--;
        return cl;
    }
}

void *circListTop(CircList *cl) { //vérifier que retour non NULL 
    if (cl->size == 0) {
        return NULL;
    }
    return cl->head->value;
}

void *circListBottom(CircList *cl) { //vérifier que retour non NULL 
    if (cl->size == 0) {
        return NULL;
    }
    return cl->tail->value;
}

void *circListPrint_int(CircList *cl) {
    ListElement *cur = cl->head;
    for (int i=0; i<cl->size; i++) {

        printf("| %d ", &(cur->value));
        cur = cur->next;
    }
    printf("|\n");
}