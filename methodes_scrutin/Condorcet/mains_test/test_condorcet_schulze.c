#include "../condorcet_schulze.h"


int main(int argc, char const *argv[])
{
    FILE *logfp = NULL;
    logfp = stdout;
    
    char file[MAX_STRING_SIZE];
    strncpy(file, argv[1], MAX_STRING_SIZE);

    condorcetSchulzeMethod(file, logfp);

    return 0;
}