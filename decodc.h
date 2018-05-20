#ifndef DECODC
#define  DECODC
#include <stdio.h>

/*
  bloco : Estrutura com nome do bloco, o estado inicial,
          e a inicio do bloco no arquivo.
*/

typedef struct{
    char name[17];
    char initState[5];
    unsigned long position_file;
}bloco;

/*
  blocos: nome dado ao vetor com todos os blocos encontrados no arquivo;
  n_blocos: numero de elementos no vetor blocos.
*/

bloco *blocos;
int   n_blocos;

// funçao que pega todos os blocos no arquivo.
void getBlocos(FILE *arq);

#endif
