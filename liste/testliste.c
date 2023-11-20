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
