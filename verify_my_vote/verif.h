
#ifndef __VERIF_H__
#define __VERIF_H__

#include "sha256.h"

#ifndef SHA256_BLOCK_SIZE
#define SHA256_BLOCK_SIZE 32
#endif

#define STRLONG 50

/*
Transforme une chaîne de caractères en chaîne de type BYTE* (unsigned char* en fait)

Paramètres:
    (char *) str: chaîne à transformer (simple cast en réalité)
    (BYTE *) resultat: chaîne dans laquelle sera placé le résultat

*/
void str_to_binary(const char *str, BYTE *resultat);



/*
Calcule le hash d'un votant grâce à son nom et sa clé privée

Paramètres:
    (char *) voter_name: nom et prénom du votant, sous la forme "NOM Prénom"
    (char *) voter_key: clé privée du votant
    (char *) hashResult: chaîne où sera stocké le hash résultant

*/
void compute_sha256_hash(const char *voter_name, const char *voter_key, char* hashResult);



/*
Cherche le hash donné dans le fichier spécifié et retourne le numéro de ligne si le hash est trouvé
Affiche également le vote effectué (sans formatage)

Paramètres:
    (char *) hash: hash à chercher dans le fichier
    (char *) fileName: chemin d'accès et nom du fichier demandé

Retour:
    -1: le fichier n'a pas pu être ouvert
    0: le hash n'a pas été trouvé
    >0: numéro de ligne où le hash a été trouvé

*/
int search_vote_in_file(const char *hash, const char *fileName);



#endif