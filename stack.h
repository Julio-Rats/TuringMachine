#ifndef STACK
#define  STACK
#include "decodc.h"

typedef struct cell cell;

typedef struct {
    cell *top;
}stack;

struct cell{
    bloco *data;
    cell *bot;
};

stack *initStack(void);
void   pushStack(stack *pilha, bloco *new_data);
bloco *popStack(stack *pilha);

#endif
