
#ifndef __VERIF_H__
#define __VERIF_H__

#include "sha256.h"

#ifndef SHA256_BLOCK_SIZE
#define SHA256_BLOCK_SIZE 32
#endif

#define STRLONG 50

/**
 *\brief Transforme une chaîne de caractères en chaîne de type BYTE* (unsigned char* en fait)
 *
 *\param[in] str: chaîne à transformer (simple cast en réalité)
 *\param[out] resultat: chaîne dans laquelle sera placé le résultat
 *
*/
void str_to_binary(const char *str, BYTE *resultat);



/**
 *\brief Calcule le hash d'un votant grâce à son nom et sa clé privée
 *
 *\param[in] voter_name: nom et prénom du votant, sous la forme "NOM Prénom"
 *\param[in] voter_key: clé privée du votant
 *\param[out] hashResult: chaîne où sera stocké le hash résultant
 *
*/
void compute_sha256_hash(const char *voter_name, const char *voter_key, char* hashResult);



/**
 *\brief Cherche le hash donné dans le fichier spécifié et retourne le numéro de ligne si le hash est trouvé\n
 *       Affiche également le vote effectué (sans formatage)
 *
 *\param[in] hash: hash à chercher dans le fichier
 *\param[in] fileName: chemin d'accès et nom du fichier demandé
 *
 *\return -1: le fichier n'a pas pu être ouvert\n
 *\return 0: le hash n'a pas été trouvé\n
 *\return >0: numéro de ligne où le hash a été trouvé\n
 *
*/
int search_vote_in_file(const char *hash, const char *fileName);



#endif