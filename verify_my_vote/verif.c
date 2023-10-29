/**
 * \file verif.c
 * \brief A partir du **NOM Prénom** et de la **clé privée** de l'utilisateur,
 *        cherche dans le **fichier spécifié** la ligne correspondant au hash des infos
 *        de l'utilisateur, et affiche le classement qu'il a effectué ainsi que le numéro
 *        de la ligne.\n 
 *        Si le vote n'est pas trouvé, le programme renvoie un message d'erreur.
 * \author Groupe 10
 * \version 1.0
 * \date 29/10/2023
 * 
*/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sha256_utils.h"
#include "sha256.h"
#include "verif.h"



// Transforme une chaine str en un resultat de type BYTE* (unsigned char* en fait)
void str_to_binary(const char *str, BYTE *resultat) {
    memcpy(resultat, (unsigned char*)str, sizeof(str)*4);
}

// Calcule le hash d'un votant grâce à son nom et sa clé privée
void compute_sha256_hash(const char *voter_name, const char *voter_key, char* hashResult) {
    BYTE *inputStr = malloc(STRLONG*sizeof(unsigned char)); //sha256 a besoin d'une variable de type BYTE*
    char *item = malloc(STRLONG*sizeof(char)); // contiendra la chaîne à hasher

    // Concaténer le nom de l'électeur et la clé de l'électeur
    strcpy(item, voter_name);
    strcat(item, voter_key);

    //on transforme une la chaine à traiter en BYTE* (unsigned char* en fait)
    str_to_binary(item, inputStr);

    // Hashage de la chaine
	sha256ofString(inputStr,hashResult); // hashRes contient le hash de inputStr
	printf("Hash calculé : %s\n\n", hashResult);
}

// Cherche le hash donné dans le fichier spécifié et retourne le numéro de ligne si le hash est trouvé
int search_vote_in_file(const char *hash, const char *fileName) {
    FILE* f = fopen(fileName, "r");
    if (f == NULL) { //gestion d'erreur
        perror("Erreur lors de l'ouverture du fichier\n");
        return -1;
    }

    char line[1000];
    char *token;
    int lineNumber = 1;

    while ((feof(f)==0)) { //on lit jusqu'à la fin du fichier
        fgets(line, 1000, f); // on prend ligne par ligne
        token = strtok(line, ","); //on commence à découer la ligne avec "," comme séparateur

        while (token != NULL) { //token==NULL -> on est arrivé à la fin de la ligne
            if (strcmp(token, hash) == 0) { // si on a trouvé le hash
                printf("Vote trouvé : ");
                token = strtok(NULL, ","); //affichage du premier token après le hash donc du premier chihffre de vote
                printf("%s",token);

                token = strtok(NULL, ",");
                while (token != NULL) { //affichage du reste du vote
                    printf(", %s",token);
                    token = strtok(NULL, ",");
                }
                printf("\n");
                fclose(f);
                return lineNumber;
            }
            token = strtok(NULL, ",");
        }
        lineNumber++;
    }
    fclose(f);
    return 0;
}

int main(int argc, char const *argv[])
{
    // Déclaration variables
    int bufferSize = SHA256_BLOCK_SIZE;
	char hashRes[bufferSize*2 + 1]; // contiendra le hash en hexadécimal
    char nomPrenom[50];
    char privateKey[20];
    char fileChecked[50];
    

    // Test arguments valides
    if (argc != 4) {
        fprintf(stderr, "Usage: %s \"NOM Prénom\" clé_secrète nom_fichier\n", argv[0]);
        exit(1);
    }

    // Initialisation variables
    strcpy(nomPrenom,argv[1]);
    strcpy(privateKey,argv[2]);
    strcpy(fileChecked,argv[3]);

    // Calcul du Hash
    compute_sha256_hash(nomPrenom, privateKey, hashRes);

    // Recherche du vote associé au hash dans le fichier CSV
    int voteLineNumber = search_vote_in_file(hashRes, fileChecked);
    
    // Traitement du résultat de la recherche
    if (voteLineNumber == -1) {
        exit(-1);
    }

    if (voteLineNumber == 0) {
        printf("Le vote n'a pas été trouvé dans le fichier spécifié.\n");
    }
    else {
        printf("Le vote a été trouvé à la ligne: %d", voteLineNumber);
    }

    return 0;
}

