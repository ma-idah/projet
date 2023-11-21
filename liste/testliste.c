#include "liste.h"

int main(int argc, char const *argv[])
{
    CircList *cl = createCircList();

    int v = 1;
    for (int i=0; i<10; i++) {
        circListPush_head(cl, (void *)&v);
        circListPrint_int(cl);
        v++;
    }
    

    return 0;
}

/*
Problème: les valeurs ne sont pas print correctement, j'ai des trucs du style "-1118154048" au lieu de petits int positifs.
ce ne sont pas des adresses je pense, donc le problème doit être au niveau du push car dans la struct Element on attend un void * ? j'en sais rien ptn


*/