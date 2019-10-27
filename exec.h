#ifndef EXEC
#define  EXEC

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "decodc.h"
#include "decodArgs.h"
#include "stack.h"

static u_int64_t n_exec;

stack*       pilha_blocos;            //  Pilha para chamada de blocos.
u_int8_t     estado_atual[TAM_STATE];
u_int8_t     novo_estado[TAM_STATE];  //  Estado atual e proximo a ser carrego.
u_int8_t     bloco_atual[TAM_BLOCK];  //  Bloco atual de execução da MT.
u_int8_t     simbolo_atual[2];        //  Simbolo atual sobre o cabeçote.
u_int8_t     fita[TAM_FITA];           //  Fita da MT.
int64_t      cabecote;                //  Posição do cabeçote na fita da MT.
u_int32_t    seek;                    //  Semente para andar no arquivo.

void execinstr(u_int8_t** vetline, FILE* arq); // Executa intstrução do tipo manipulador de simbolos
void execblock(u_int8_t** vetline, FILE* arq); // Executa intstrução do tipo chamada de blocos
void print(int16_t fin, FILE* arq);             // Printa Status(FITA) na tela.
void exec(FILE *arq);                          // Executa todo o algoritimo(arquivo) da MT.
void para(FILE *arq);                          // Finaliza a MT.

#endif
