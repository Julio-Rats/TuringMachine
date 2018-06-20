#ifndef DECODARGS
#define  DECODARGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
    Enum para definir qual PARAMETRO de impressão a MT executara.
*/

typedef enum{
    type_r=1,   //  Tipo silencioso
    type_v=2,   //  Tipo "verboso"
    type_s=3    //  Tipo n step para e pega novo modo
}type_mod;

type_mod modo;  // Variavel GLOBAL de controle de PARAMETRO

unsigned int n_step;      // variavel de controle para entrada do tipo -S (numero de passos)
unsigned int step_arg;    // Varial de controle para novas entradas do tipo -s
char delim_cabecote[3];   // Delimitador do cabeçote entrada -h

// Lê os paramentros e decodifica.

void decodArgs(int argc,char *argv[]);

#endif
