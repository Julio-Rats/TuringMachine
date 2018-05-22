#include <stdlib.h>
#include "stack.h"
#include "decodc.h"

stack *initStack(void){
    stack *aux = (stack *) malloc(sizeof(stack));
    aux->top   = NULL;
    return aux;
}
void  pushStack(stack *pilha, recall *new_data){
  cell *aux  = (cell *) malloc(sizeof(cell));
  aux->data  = new_data;
  aux->bot   = pilha->top;
  pilha->top = aux;
  return;
}
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
