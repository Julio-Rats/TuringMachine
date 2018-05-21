#ifndef EXEC
#define  EXEC
#include <stdio.h>

char  estado_atual[5],novo_estado[5];
char  bloco_atual[17];
char  fita[1024];
int   cabecote;

void exec(FILE *arq);
void print(void);
void erro(void);
void accept(void);
void execinstr(char *line,long start, FILE *arq);
void execblock(char *line);

#endif
