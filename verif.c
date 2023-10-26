#include <string.h>
#include <stdlib.h>
#include "sha256_utils.h"
#include "sha256.h"
#include <stdio.h>



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

void compute_sha256_hash(const char *voter_name, const char *voter_key) {
    // Concaténer le nom de l'électeur et la clé de l'électeur
    char input_string[256]; // En supposant une longueur maximale de 256 pour la chaîne d'entrée
    snprintf(input_string, sizeof(input_string), "%s%s", voter_name, voter_key);

    // Initialiser le contexte SHA-256
    SHA256_CTX sha256_ctx;
    sha256_init(&sha256_ctx);

    // Mettre à jour le contexte avec la chaîne d'entrée
    sha256_update(&sha256_ctx, (const BYTE *)input_string, strlen(input_string));

    // Finaliser le hash SHA-256
    BYTE sha256_hash[SHA256_BLOCK_SIZE];
    sha256_final(&sha256_ctx, sha256_hash);

    // Afficher le hash
    printf("SHA-256 Hash: ");
    for (int i = 0; i < SHA256_BLOCK_SIZE; i++) {
        printf("%02x", sha256_hash[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <voter_name> <voter_key>\n", argv[0]);
        return 1;
    }

    const char *voter_name = argv[1];
    const char *voter_key = argv[2];

    compute_sha256_hash(voter_name, voter_key);

    return 0;
}
