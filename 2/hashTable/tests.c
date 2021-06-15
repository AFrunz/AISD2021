#include "hashTable.h"

int main(){
    hashT* t = tableInit(4);
    tableAdd(t, 1, 10);
    tablePrint(t);
    tableAdd(t, 1, 15);
    tablePrint(t);
    tableAdd(t, 5, 17);
    tablePrint(t);
    tableAdd(t, 2, 12);
    tablePrint(t);
    tableAdd(t, 12, 13);
    tablePrint(t);
    tableDelete(t, 1);
    tableDelete(t, 3);
    tableDelete(t, 5);
    tableDelete(t, 2);
    tableDelete(t, 12);
    tableDelete(t, 12);
    tablePrint(t);
    tableFree(t);



    return 0;
}