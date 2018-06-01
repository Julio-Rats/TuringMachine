#include "stack.h"

// inicializa e retorna ponteiro alocado

stack *initStack(void){
    stack *aux = (stack *) malloc(sizeof(stack));
    aux->top   = NULL;
    return aux;
}

// add no topo da pilha

void  pushStack(stack *pilha, recall *new_data){
  cell *aux  = (cell *) malloc(sizeof(cell));
  aux->data  = new_data;
  aux->bot   = pilha->top;
  pilha->top = aux;
  return ;
}

// remove do topo da pilha e retorna ponteiro da estrutura dos dados

recall *popStack(stack *pilha){
    if(!pilha){
        return NULL;
    }
    recall *aux_data = pilha->top->data;
    cell *aux        = pilha->top;
    pilha->top       = pilha->top->bot;
    free(aux);
    return aux_data;
}
