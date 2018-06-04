#ifndef STACK
#define  STACK

#include <stdlib.h>

typedef struct cell   cell;
typedef struct recall recall;
typedef struct stack  stack;

struct stack{
    cell *top;
};    // estrutura da pilha, sempre aponta pro topo

struct cell{
  recall *data;
  cell  *bot;
};        // estrutura a ser alocado na pilha

struct recall{
    char  recall_bloco[17];
    int   n_bloco;
    char  recall_state[5];
};  // estrutura dos dados alocados na pilha


stack *initStack(void);   // inicializa pilha
void   pushStack(stack *pilha, recall *new_data); // add no topo da pilha
recall *popStack(stack *pilha);  // remove topo da pilha

#endif
