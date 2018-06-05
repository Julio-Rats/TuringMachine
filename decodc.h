#ifndef DECODC
#define  DECODC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define   tam_line 128 // Tamanho de leitura no aquivo.

/*
  bloco : Estrutura com nome do bloco, o estado inicial,
          e a inicio do bloco no arquivo.
*/

typedef struct{
    char name[17];               // Nome do bloco declarado.
    char initState[5];           // Estado inicial do bloco.
    unsigned long position_file;  // posição do bloco no arquivo.
}bloco;

/*
  blocos:   Nome dado ao vetor com todos os blocos encontrados no arquivo.
  n_blocos: Indicador do tamanho do vetor blocos, com struct bloco.
  cont:     Indicador do tamanho do vetor de saida da função decodline.
*/

bloco *blocos;
int   n_blocos;
int   cont;

/* Função getBlocos: pega todos os blocos no arquivo, salvando em uma lista
      com nome, posição no arquivo e estado inicial do bloco de intstrução.

   Função decodline: pega uma linha como entrada e quebra em
          tokens e retorna um vetor de strings com os tonkes.
*/

void getBlocos(FILE *arq);
char **decodline(char *line);

#endif
