#ifndef STACK
#define  STACK

#include <stdlib.h>
#include "decodc.h"

typedef struct cell   cell;    //  Celula com dados e ponteiro da pilha.
typedef struct recall recall;  //  Estrutura com dados dos blocos.
typedef struct stack  stack;   //  Ponteiro topo da pilha.

struct stack{ // Estrutura da pilha, sempre aponta pro topo.
    cell *top;
};

struct cell{ // Estrutura a ser empilhada na pilha.
  recall *data;
  cell  *bot;
};

struct recall{ // Estrutura dos dados alocados na celula.
    u_int8_t  recall_bloco[TAM_BLOCK];  // Nome do bloco.
    u_int8_t  recall_state[TAM_STATE];
    u_int8_t  final_state[TAM_STATE];
};

stack *initStack(void);           // Inicializa pilha
void   pushStack(stack *pilha, recall *new_data); // Add no topo da pilha
recall *popStack(stack *pilha);   // Remove topo da pilha

#endif
