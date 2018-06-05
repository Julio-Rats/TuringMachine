#ifndef EXEC
#define  EXEC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodc.h"
#include "decodArgs.h"
#include "stack.h"


#define   tam_fita  1024
#define   tam_line 128

stack *pilha_blocos;
char  estado_atual[5],novo_estado[5];
char  bloco_atual[17];
char  *simbolo_atual;
char  fita[tam_fita];
int   n_bloco_atual;
int   cabecote;
unsigned long seek;

void exec(FILE *arq);
void print(int fin, FILE *arq);
void para(FILE *arq);
void execinstr(char **vetline, FILE *arq);
void execblock(char **vetline, FILE *arq);


#endif
