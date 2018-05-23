#ifndef EXEC
#define  EXEC
#include <stdio.h>
#include "stack.h"
#define   tam_fita  1024
#define   tam_line 128

char  estado_atual[5],novo_estado[5];
char  bloco_atual[17];
char  *simbolo_atual;
char  fita[tam_fita];
stack *pilha_blocos;
int   cabecote;
unsigned long seek;

void exec(FILE *arq);
void print(int fin);
void para(void);
void accept(void);
void execinstr(char *line, FILE *arq);
void execblock(char *line, FILE *arq);

#endif
