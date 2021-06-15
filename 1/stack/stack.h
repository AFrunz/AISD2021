#ifndef BD_STACK_H
#define BD_STACK_H

typedef struct Info{
    int k;
}Info;

typedef struct StackUnit{
    struct StackUnit *next;
    Info *info;
}StackUnit;

typedef struct Stack{
    StackUnit *head;
}Stack;

void stackPrint(Stack *d);

Stack* stackInit();

int stackInsert(Stack *d, int k);

int stackDelete(Stack *d);

void stackFree(Stack *d);

#endif