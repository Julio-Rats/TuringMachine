#include "decodc.h"

void getBlocos(FILE *arq){
    rewind(arq);
    char *ptr;
    char line[tam_line];
    n_blocos = 0;
    // ler linha a linha ate achar o "bloco"
    while(!feof(arq)){
        fgets(line,sizeof(line),arq);
        ptr = strtok(line,"\t");
        strtok(ptr,";");
        strtok(ptr," ");
        if (line[0] == ';'){ptr=NULL;}
        while(ptr){
              if (strcmp(ptr,"bloco")==0){
                  ptr = strtok(NULL," ");
                  if (!ptr){fprintf(stderr, "\n\nERROR SINTAXE BLOCOS\n\n");exit(1);}
                  // verifica se ja existe o vetor de bloco, e aloca mais uma posição
                  if(n_blocos == 0){
                     blocos = (bloco *) malloc(sizeof(bloco)*(++n_blocos));
                  }else{
                     blocos = (bloco *) realloc(blocos,sizeof(bloco)*(++n_blocos));
                  }
                  //  coloca no vetor o bloco encontrado
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
