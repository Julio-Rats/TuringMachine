#include <stdlib.h>
#include <string.h>
#include "exec.h"
#include "decodc.h"
#include "trim.h"


void exec(FILE *arq){
   cabecote = 0;
   short type_cod;  //0 inst 1 block
   unsigned long start=0;
   strcpy(bloco_atual,"main");
   for(int i=0;i<n_blocos;i++)
      if(strcmp(blocos[i].name,"main")==0){
         strcpy(estado_atual, blocos[i].initState);
         start = blocos[i].position_file;
         break;
      }
   fseek(arq, start, SEEK_SET);
   char line[128];



   // ---------
   char *tokens;
   char aux[128];
   char *init,*last;
   char *token;
coding:
   fgets(line,sizeof(line),arq);
   while(!feof(arq)){
       type_cod = 1;
       strcpy(aux,line);
       strtok(line,";");
       tokens = strtok(aux,"\n");
       tokens = strtok(aux,";");
       strtok(tokens," ");
       if (line[0] == ';'){tokens=NULL;}
       while(tokens){
            if (strcmp(tokens," ")==0){
                token="";
            }else{
              strcpy(token,tokens);
            }
            token = Trim(token);
            if(strcmp(token,"fim")==0){erro();}
            if(atoi(token) == atoi(estado_atual)){
                  if (init = strchr(line,'-'))
                     if (last = strrchr(line,'-'))
                        if ((init-last)==-1){
                           type_cod = 0;
                        }

                  tokens = strtok(NULL," ");
                  if (type_cod == 0 && (tokens[0] == fita[cabecote])){
                      execinstr(line, start, arq);
                      printf("cod 0\n");
                      goto coding;
                  }if (type_cod == 1){
                      // execblock(line, arq);
                      // printf("cod 1\n");
                  }
            }
            // printf("%s\n", token);
            tokens = strtok(NULL," ");
       }
       fgets(line,sizeof(line),arq);
   }
}
void print(void);
void erro(void){
      system("clear");
      printf("MT NÃO ACEITOU A ENTRADA\n");
      exit(0);
}
void execinstr(char *line,long start, FILE *arq){
  int cont=0;
  line = Trim(line);
  strtok(line," ");
  while(line){
    printf("%s\n", line);
    switch (cont) {
      case 3:
          strcpy(novo_estado, line);
          break;
      case 4:
          if(line[0]=='e'){
            cabecote--;
          }else{
            if (line[0]=='d'){
              cabecote++;
            }
          }
          break;
      case 5:

          break;
    }
    line = strtok(NULL," ");
    cont++;
  }
  fseek(arq,start,SEEK_SET);
  strcpy(estado_atual, novo_estado);

}
void execblock(char *line){
  // printf("%s\n", line);
}
