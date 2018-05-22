#ifndef DECODARGS
#define  DECODARGS

void decodArgs(int argc,char *argv[]);

typedef enum{
    type_r=1,
    type_v=2,
    type_s=3
}type_mod;

type_mod modo;

int n_step;
char delim_cabecote[3];

#endif
