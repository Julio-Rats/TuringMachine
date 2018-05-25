#ifndef DECODARGS
#define  DECODARGS

void decodArgs(int argc,char *argv[]);

/*
    Enum para definir qual PARAMETRO de impressão a MT executara.
*/

typedef enum{
    type_r=1,  // tipo silencioso
    type_v=2, //  tipo "verboso"
    type_s=3 //   tipo n step para e pega novo modo
}type_mod;

type_mod modo; // variavel GLOBAL de controle de PARAMETRO

unsigned int n_step;      // variavel de controle para entrada do tipo -S (numero de passos)
unsigned int step_arg;   //  varial de controle para novas entradas do tipo -s
char delim_cabecote[3];  // delimitador do cabeçote entrada -h

#endif
