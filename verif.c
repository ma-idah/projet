#include <string.h>
#include <stdlib.h>
#include "sha256_utils.h"
#include "sha256.h"



void str_to_binary(char* str, char *resultat, int espaces) {
    char char_traite;
    unsigned long val; //valeur du char traité pour pouvoir accéder à tab_valeurs
    const char tab_valeurs[16][5] = {"0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111",
                                     "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111"}; //valeur en binaire pour un entier de 0 à 15

    
    for (int i=0; i<strlen(str); i++) {
        char_traite = str[i];
        val = strtoul(&char_traite, NULL, 16); //transformation du char hex en sa valeur entière 
        strcat(resultat, tab_valeurs[val]); //concaténation du prochain demi-octets (valeur du char en hex)
        if (espaces && i %2 == 1) {strcat(resultat, " ");} //ajout d'espaces tous les octets si demandé
    }
}
