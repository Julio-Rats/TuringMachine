#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "decodArgs.h"

void decodArgs(int argc,char *argv[]){
    strcpy(delim_cabecote,"()");
    modo=2;
    for(int i=1;i<argc;i++){
        if(argv[i][0]=='-'){
              switch (argv[i][1]) {
                case 'r':
                    modo   = 1;
                  break;
                case 'v':
                    modo   = 2;
                  break;
                case 's':
                    modo   = 3;
                    if(argc >= (i+1)){
                      n_step = atoi(argv[i+1]);
                    }else{n_step = 1;}
                  break;
                case 'h':
                    delim_cabecote[0] = argv[i+1][0];
                    delim_cabecote[1] = argv[i+1][strlen(argv[i+1])-1];
                  break;
                default:
                    printf("\nERRO PARAMETRO %s INVALIDO\n\n", argv[i]);
                    exit(1);
              }
        }
    }
}
