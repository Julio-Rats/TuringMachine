#ifndef  DECODARGS
#define  DECODARGS

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define DELIM_PADRAO "()"
/*
    Enum para definir qual PARAMETRO de impressão a MT executara.
*/

typedef enum
{
    type_r,    //  Tipo silencioso
    type_v,    //  Tipo "verboso"
    type_s     //  Tipo n step para e pega novo modo
}type_mod;

type_mod  modo;  // Variavel GLOBAL de controle de PARAMETRO

u_int64_t n_step;            // variavel de controle para entrada do tipo -S (numero de passos)
u_int64_t step_arg;          // Varial de controle para novas entradas do tipo -s
u_int8_t  delim_cabecote[3]; // Delimitador do cabeçote entrada -h

// Lê os paramentros e decodifica.

void decodArgs(u_int8_t argc,u_int8_t* argv[]);

#endif
