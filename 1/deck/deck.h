#ifndef BD_DECK_H
#define BD_DECK_H

typedef struct Info{
    int k;
}Info;

typedef struct DeckUnit{
    struct DeckUnit *next;
    struct DeckUnit *parent;
    Info *info;
}DeckUnit;

typedef struct Deck{
    DeckUnit *head, *tail;
}Deck;

Deck* deckInit();

int deckInsertHead(Deck *d, int k);

int deckInsertTail(Deck *d, int k);

int deckDeleteHead(Deck *d);

int deckDeleteTail(Deck *d);

void deckFree(Deck *d);

void deckPrint(Deck *d);





#endif
