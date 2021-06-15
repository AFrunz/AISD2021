#include "queue.h"


int main(){
    Queue *test = queueInit();
    queueInsert(test, 5);
//    queueInsert(test, 4);
//    queueInsert(test, 3);
//    queueInsert(test, 2);
//    queueInsert(test, 6);
//    queueInsert(test, 7);
    queuePrint(test);
    queueDelete(test);
    queuePrint(test);
    queueDelete(test);
    queuePrint(test);
    queueFree(test);
    return 0;
}