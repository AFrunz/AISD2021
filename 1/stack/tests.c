#include "stack.h"


int main(){
    Stack *test = stackInit();
    stackInsert(test, 5);
    stackInsert(test, 4);
    stackInsert(test, 3);
    stackInsert(test, 2);
    stackInsert(test, 6);
    stackInsert(test, 7);
    stackPrint(test);
    stackDelete(test);
    stackPrint(test);
    stackDelete(test);
    stackPrint(test);
    stackFree(test);
    return 0;
}