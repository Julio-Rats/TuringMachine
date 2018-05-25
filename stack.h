#ifndef STACK
#define  STACK
#include <stdlib.h>
#include "decodc.h"

typedef struct cell cell; //

typedef struct {
    cell *top;
}stack;    // estrutura da pilha, sempre aponta pro topo

struct cell{
  recall *data;
  cell  *bot;
};        // estrutura a ser alocado na pilha

typedef struct{
    char  recall_bloco[17];
    int   n_bloco;
    char  recall_state[5];
}recall;  // estrutura dos dados alocados na pilha


stack *initStack(void);   // inicializa pilha
void   pushStack(stack *pilha, recall *new_data); // add no topo da pilha
recall *popStack(stack *pilha);  // remove topo da pilha

#endif
