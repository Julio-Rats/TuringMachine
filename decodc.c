#include <stdlib.h>
#include <string.h>
#include "decodc.h"

void getBlocos(FILE *arq){
    rewind(arq);
    char line[tam_line];
    char *ptr;
    n_blocos = 0;
    while(!feof(arq)){
        memset(&line,0,sizeof(line));
        fgets(line,sizeof(line),arq);
        ptr = strtok(line,";");
        ptr = strtok(ptr," ");
        if (line[0] == ';'){ptr=NULL;}
        while(ptr){
              if (strcmp(ptr,"bloco")==0){
                  ptr = strtok(NULL," ");
                  if (!ptr){fprintf(stderr, "\n\nERROR SINTAXE BLOCOS\n\n");exit(1);}
                  if(n_blocos == 0){
                     blocos = (bloco *) malloc(sizeof(bloco)*(++n_blocos));
                  }else{
                     blocos = (bloco *) realloc(blocos,sizeof(bloco)*(++n_blocos));
                  }
                  strcpy(blocos[n_blocos-1].name, ptr);
                  blocos[n_blocos-1].position_file = ftell(arq);
                  ptr = strtok(NULL," ");
                  if (!ptr){fprintf(stderr, "\n\nERROR SINTAXE BLOCOS\n\n");exit(1);}
                  strcpy(blocos[n_blocos-1].initState, ptr);
              }
              ptr = strtok(NULL," ");
        }
    }
}
