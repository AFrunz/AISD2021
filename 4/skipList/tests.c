#include "skipList.h"



int main(){
    skList *t = listInit();
    listAdd(t, 12, 100);
    listAdd(t, 13, 100);
    listAdd(t, 14, 100);
    listAdd(t, 15, 100);
    listAdd(t, 10, 100);
    listAdd(t, 1, 100);
    listAdd(t, 4, 100);
    listAdd(t, 5, 100);
    listPrint(t);
    listDelete(t, 1);
    listPrint(t);
    return 0;
}
