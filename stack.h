#ifndef STACK
#define  STACK

#include <stdlib.h>

typedef struct cell   cell;    //  Celula com dados e ponteiro da pilha.
typedef struct recall recall;  //  Estrutura com dados dos blocos.
typedef struct stack  stack;   //  Ponteiro topo da pilha.

struct stack{
    cell *top;
};         // Estrutura da pilha, sempre aponta pro topo.

struct cell{
  recall *data;
  cell  *bot;
};         // Estrutura a ser empilhada na pilha.

struct recall{
    char  recall_bloco[17];
    int   n_bloco;
    char  recall_state[5];
};         // Estrutura dos dados alocados na celula.

stack *initStack(void);           // Inicializa pilha
void   pushStack(stack *pilha, recall *new_data); // Add no topo da pilha
recall *popStack(stack *pilha);   // Remove topo da pilha

#endif
