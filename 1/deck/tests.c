#include "deck.h"


int main(){
    Deck *test = deckInit();
    deckInsertHead(test, 5);
//    deckInsertHead(test, 4);
//    deckInsertHead(test, 3);
//    deckInsertHead(test, 2);
//    deckInsertTail(test, 6);
//    deckInsertTail(test, 7);
//    deckInsertTail(test, 8);
//    deckInsertTail(test, 9);
    deckPrint(test);
    deckDeleteHead(test);
    deckPrint(test);
    deckDeleteTail(test);
    deckPrint(test);
    deckFree(test);
    return 0;
}