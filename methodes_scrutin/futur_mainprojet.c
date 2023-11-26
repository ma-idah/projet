#include "lecture_csv.h"
 #include <string.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include "uninominal.h"
  #include "uninominal_2.h"

 #include <getopt.h>
 int main(int argc, char *argv[]) {
    // Déclaration des variables pour les options de la ligne de commande
    int option;
    char *inputFile = NULL;
    char *outputFile = NULL;
    char *method = NULL;

    // Analyse des options de la ligne de commande
    while ((option = getopt(argc, argv, "i:d:o:m:")) != -1) {
        switch (option) {
            case 'i':
            case 'd':
                // Vérifier si l'option -i ou -d est déjà spécifiée
                if (inputFile != NULL) {
                    fprintf(stderr, "Erreur : Les options -i et -d sont incompatibles. Utilisez l'une ou l'autre, mais pas les deux.\n");
                    exit(EXIT_FAILURE);
                }
                inputFile = optarg;
                break;
            case 'o':
                outputFile = optarg;
                break;
            case 'm':
                method = optarg;
                break;
            case '?':
                fprintf(stderr, "Erreur : Option inconnue\n");
                exit(EXIT_FAILURE);
        }
    }

    // Vérifier la présence obligatoire de -i ou -d
    if (inputFile == NULL) {
        fprintf(stderr, "Erreur : L'option -i ou -d est obligatoire.\n");
        exit(EXIT_FAILURE);
    }

     // Ouvrir le fichier de log ou utiliser stdout
     FILE *logfp = (outputFile != NULL) ? fopen(outputFile, "w") : stdout;
     if (logfp == NULL) {
         perror("Erreur lors de l'ouverture du fichier de log");
         exit(EXIT_FAILURE);
         }
         

    // Traiter le fichier en fonction des options
    if (optind < argc) {
        fprintf(stderr, "Erreur : Des arguments supplémentaires inattendus.\n");
        exit(EXIT_FAILURE);
    }

    CsvMatrix matrice;
    CsvRowsColsCounter(&matrice.nbRows, &matrice.nbCols, inputFile);
    FillMatrix(&matrice, inputFile);
    

    // Déclaration des variables pour les résultats
    int sommeColonnes[matrice.nbCols - 4];


    // Appliquer la méthode de scrutin appropriée
    if (strcmp(method, "uni1") == 0) {
        // Appeler la méthode uninominale à un tour
        calculerSommecolonnes(&matrice, sommeColonnes);
        
         int colMin = trouverColonneMin(sommeColonnes, matrice.nbCols - 4);
        
        printf("Mode de scrutin : uninominale à un tour, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",
                 matrice.nbCols - 4, matrice.nbRows - 1, matrice.matrix[0][colMin], (sommeColonnes[colMin - 4] * 100) / matrice.nbRows - 1);
        
        } 
        else if (strcmp(method, "uni2") == 0) {
         // Appeler la méthode uninominale à deux tours
            DeuxIndices colMins = trouverDeuxColonnesMin(sommeColonnes, matrice.nbCols - 4);
         printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",    matrice.nbCols - 4, matrice.nbRows - 1, matrice.matrix[0][colMins->indiceMin1],
               sommeColonnes[colMins->indiceMin1 - 4] * 100 / (matrice.nbRows - 1));
         printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",
                matrice.nbCols - 4, matrice.nbRows - 1, matrice.matrix[0][colMins->indiceMin2],
               sommeColonnes[colMins->indiceMin2 - 4] * 100 / (matrice.nbRows - 1));

        // Simuler le deuxième tour virtuel
        int simuVotesA = sommeColonnes[colMins->indiceMin1 - 4];
        int simuVotesB = sommeColonnes[colMins->indiceMin2 - 4];
        int totalVotes = matrice.nbRows - 1;
        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %d%%\n",
               totalVotes, (simuVotesA > simuVotesB) ? matrice.matrix[0][colMins->indiceMin1] : matrice.matrix[0][colMins->indiceMin2],
               (simuVotesA > simuVotesB) ? simuVotesA * 100 / totalVotes : simuVotesB * 100 / totalVotes);
    } else if (strcmp(method, "all") == 0) {
        // Appliquer toutes les méthodes valides l'une après l'autre
        afficher_vainqueur(&matrice, sommeColonnes);

        DeuxIndices colMins = trouverDeuxColonnesMin(sommeColonnes, matrice.nbCols - 4);
        printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",
               matrice.nbCols - 4, matrice.nbRows - 1, matrice.matrix[0][colMins->indiceMin1],
               sommeColonnes[colMins->indiceMin1 - 4] * 100 / (matrice.nbRows - 1));

        printf("Mode de scrutin : uninominal à deux tours, tour 1, %d candidats, %d votants, vainqueur = %s, score = %d%%\n",
               matrice.nbCols - 4, matrice.nbRows - 1, matrice.matrix[0][colMins->indiceMin2],
               sommeColonnes[colMins->indiceMin2 - 4] * 100 / (matrice.nbRows - 1));

        // Simuler le deuxième tour virtuel
        int simuVotesA = sommeColonnes[colMins->indiceMin1 - 4];
        int simuVotesB = sommeColonnes[colMins->indiceMin2 - 4];
        int totalVotes = matrice.nbRows - 1;
        printf("Mode de scrutin : uninominal à deux tours, tour 2, 2 candidats, %d votants, vainqueur = %s, score = %d%%\n",
               totalVotes, (simuVotesA > simuVotesB) ? matrice.matrix[0][colMins->indiceMin1] : matrice.matrix[0][colMins->indiceMin2],
               (simuVotesA > simuVotesB) ? simuVotesA * 100 / totalVotes : simuVotesB * 100 / totalVotes);
    }
         else {
        fprintf(stderr, "Erreur : Méthode de scrutin inconnue.\n");
        exit(EXIT_FAILURE);
    }
     
     
     // Fermer le fichier de log s'il a été ouvert
    if (outputFile != NULL) {
        fclose(logfp);
         }


   

    return 0;
}
