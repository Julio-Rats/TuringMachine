#ifndef DECODARGS
#define DECODARGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DELIM_PADRAO "()"
/*
    Enum para definir qual PARAMETRO de impressão a MT executara.
*/

typedef enum
{
    type_r, //  Tipo silencioso
    type_v, //  Tipo "verboso"
    type_s  //  Tipo n step para e pega novo modo
} type_mod;

type_mod modo; // Variavel GLOBAL de controle de PARAMETRO

size_t n_step;          // variavel de controle para entrada do tipo -S (numero de passos)
size_t step_arg;        // Varial de controle para novas entradas do tipo -s
char delim_cabecote[3]; // Delimitador do cabeçote entrada -h

// Lê os paramentros e decodifica.

void decodArgs(int argc, char *argv[]);

#endif
