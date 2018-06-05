#include "decodArgs.h"

void decodArgs(int argc,char *argv[]){
    modo=2;        // Modo setado em modo padrão .
    n_step   = 1;  // Numero padrão paramentro -s.
    step_arg = 1;  // Numero padrão paramentro -s.

    strcpy(delim_cabecote,"()"); // Setando os delimitadores do cabeçote padrão "( )".

    for(int i=1;i<argc;i++){
      // Pega os PARAMETROS.
      if(argv[i][0]=='-'){
          if (strcmp(argv[i],"-r")==0)
              modo   = 1; // Tipo -r
          else if (strcmp(argv[i],"-v")==0)
              modo   = 2; // Tipo -v
          else if (strcmp(argv[i],"-s")==0){
              modo   = 3; // Tipo -s
              if (argc >= (i+1)){
                  // Pegando e tratando paramentro -s
                  n_step = atoi(argv[i+1]);
                  step_arg = n_step;
                  if (n_step == 0){
                      fprintf(stderr, "\nERROR PARAMETRO -S VALOR \"N\" NÃO INFORMADO OU IGUAL A ZERO\n\n");
                      exit(EXIT_FAILURE);
                  }
             }
          }else if (strcmp(argv[i],"-head")==0){
                  delim_cabecote[0] = argv[i+1][0];
                  delim_cabecote[1] = argv[i+1][strlen(argv[i+1])-1];
                  delim_cabecote[2] = '\0';
               }else{
                  // Paramentro invalido.
                  fprintf(stderr, "\nERROR SINTAXE PARAMETRO %s INVALIDO\n\n", argv[i]);
                  exit(EXIT_FAILURE);
               }
      }
    } // for
} // function
