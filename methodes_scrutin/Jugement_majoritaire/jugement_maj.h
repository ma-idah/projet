#ifndef STRUCT_DATA_H
#define STRUCT_DATA_H

typedef struct{
    int nbCandidat;
    int nbVotants;
    int nbBurger;
    char** noms;
    int* choixElecteur;
}dataElection;

typedef struct{
    int* votes_electeur;
}voteElecteur;

void genererData(dataElection *data, int nbVotants, int nbCandidat, int nbBurger);
void ecrireVote(dataElection *data, voteElecteur *vote);
void voter(dataElection *data, voteElecteur *vote, int nbVotants, int nbCandidat);
float * appreciationCandidat(voteElecteur **votes,int numCandidat,int nbVotants,int nbCandidat);
void jugementMajoritaire(voteElecteur **votes,int nbVotants,int nbCandidat);

#endif // STRUCT_DATA_H