
#ifndef __VERIF_H__
#define __VERIF_H__

/*
Transforme une chaine de caractères hexadécimaux en chaine de bits

Paramètres:
    (char*) str: chaine de caractères hexadécimaux (aucune vérification ne sera effectuée sur la validité des caractères)
    (char*) resultat: chaine où sera placé le résultat
    (int) espaces: booléen - 0: pas d'espaces entre les octets
                             1: espaces entre chaque octets

*/
void str_to_binary(char* str, char *resultat, int espaces);








#endif