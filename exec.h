#ifndef EXEC
#define  EXEC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodc.h"
#include "decodArgs.h"
#include "stack.h"

#define   tam_fita  1024   // Tamanho da fita da MT.
#define   tam_line 128   //  Tamanho da linha maxima de leitura no arquivo.

char  estado_atual[5],novo_estado[5];  // Estado atual e proximo a ser carrego.
stack *pilha_blocos;                  //  Pilha para chamada de blocos.
char  bloco_atual[17];               //   Bloco atual de execução da MT.
char  simbolo_atual[2];             //    Simbolo atual sobre o cabeçote.
char  fita[tam_fita];                //     Fita da MT.
int   cabecote;                   //      Posição do cabeçote na fita da MT.
unsigned long seek;              //       Semente para andar no arquivo.

void execinstr(char **vetline, FILE *arq);     // Executa intstrução do tipo manipulador de simbolos
void execblock(char **vetline, FILE *arq);   //   Executa intstrução do tipo chamada de blocos
void print(int fin, FILE *arq);             //     Printa Status(FITA) na tela.
void exec(FILE *arq);                    //       Executa todo o algoritimo(arquivo) da MT.
void para(FILE *arq);                  //         Finaliza a MT.

#endif
