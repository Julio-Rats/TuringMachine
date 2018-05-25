#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "decodArgs.h"

void decodArgs(int argc,char *argv[]){
    // modo e delimitador setados em modo padrão.
    modo=2;
    strcpy(delim_cabecote,"()");

    for(int i=1;i<argc;i++){
      if (strcmp(argv[i],"-head")==0){
        delim_cabecote[0] = argv[i+1][0];
        delim_cabecote[1] = argv[i+1][strlen(argv[i+1])-1];
        delim_cabecote[2] = '\0';
        continue;
      }
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
                      step_arg = n_step;
                      if (n_step == 0){
                        printf("\nERRO PARAMETRO %s VALOR \"N\" NÃO INFORMADO OU IGUAL A ZERO\n\n", argv[i]);
                        exit(1);
                      }
                    }else{n_step = 1;}
                  break;
                default:
                    printf("\nERRO PARAMETRO %s INVALIDO\n\n", argv[i]);
                    exit(1);
            }
      }
   }
}
