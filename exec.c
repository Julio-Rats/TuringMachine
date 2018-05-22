#include <stdlib.h>
#include <string.h>
#include "exec.h"
#include "decodc.h"
#include "decodArgs.h"
#include "trim.h"
#include "stack.h"

void setseekbloco(FILE *arq, char*name_bloco){
  strcpy(bloco_atual,name_bloco);
  for(int i=0;i<n_blocos;i++)
     if(strcmp(blocos[i].name,name_bloco)==0){
        strcpy(estado_atual, blocos[i].initState);
        seek = blocos[i].position_file;
        n_bloco_atual = i;
        return;
    }
    printf("\nErro bloco não encontrado %s\n\n", name_bloco);
    erro();
}

void exec(FILE *arq){
   pilha_blocos = initStack();
   static int n_exec=0;
   short type_cod;  //0 inst 1 block
   cabecote = 0;
   seek=0;
   setseekbloco(arq, "main");
   char *line=(char*)malloc(sizeof(char)*tam_line);
   char  aux[tam_line];
   char *tokens;
   char *simb,*opr;
   char *token;
   fseek(arq,seek,SEEK_SET);
back:
   fgets(line,tam_line,arq);
   while(!feof(arq)){
       n_exec++;
       line = Trim(line);
       if (line[0] == ';'){
         fgets(line,tam_line,arq);
         continue;
       }
       strtok(line,"\n");
       strcpy(aux,line);
       strtok(aux,";");
       strtok(aux," ");
       if(strcmp(aux,"fim")==0){
            strtok(estado_atual,"\n");
            print(0);
            printf("\nERROR TRANSIÇÃO BLOCO %s ESTADO %s COM %c NÃO DEFINIDA\n",bloco_atual, estado_atual, fita[cabecote]);
            erro();
       }
       if(atoi(aux) == atoi(estado_atual)){
             simb = strtok(NULL," ");
             opr  = strtok(NULL," ");
             if (!opr){
                  goto back;
             }
             if (strcmp(opr,"--")==0){
                  type_cod = 0;
               }else{
                  type_cod = 1;
               }
                  if ((type_cod == 0) && (simb[0] == fita[cabecote])){
                      execinstr(line, arq);
                      goto back;
                  }if (type_cod == 1){
                      execblock(line, arq);
                      goto back;
                  }
           }
      fgets(line,128,arq);
   }
}
void erro(void){
      //system("clear");
      printf("MT ENCERROU\n\n");
      exit(0);
}
void execinstr(char *line, FILE *arq){
  int cont=0;
  short fin=0;
  strtok(line,"\n");
  line = strtok(line,";");
  strtok(line," ");
  char novo_estado[5];
  while(line){
    switch (cont) {
      case 3:
          fita[cabecote] = line[0];
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
          if (strcmp(line,"pare")==0){
                fin = 1;
          }else{
            if (strcmp(line,"retorne")==0){
                recall *retorno = popStack(pilha_blocos);
                if (!retorno){
                        printf("\nErro de retorno de bloco\n");
                        erro();
                }
                strcpy(bloco_atual,(char*)retorno->recall_bloco);
                n_bloco_atual      =  retorno->n_bloco;
                strcpy(novo_estado, retorno->recall_state);

            }else{
                  strcpy(novo_estado, line);
                }
            }
          break;
      case 6:
          if (strcmp("!",line)==0){
              modo = 2;
          }
          break;
        }
    line = strtok(NULL," ");
    cont++;
    }
    print(fin);
    setseekbloco(arq, bloco_atual);
    fseek(arq,seek,SEEK_SET);
    strcpy(estado_atual,novo_estado);
}
void execblock(char *line, FILE *arq){
    strtok(line,"\n");
    line = strtok(line,";");
    line = strtok(line," ");
    char *novo_bloco     = strtok(NULL," ");
    char *estado_retorno = strtok(NULL," ");
    recall *returno=NULL;
    if (returno){
          free(returno);
    }
    returno = (recall*)malloc(sizeof(recall));
    line = strtok(NULL," ");
    strcpy((char*)returno->recall_bloco, bloco_atual);
    returno->n_bloco = n_bloco_atual;
    strcpy(returno->recall_state, estado_retorno);
    pushStack(pilha_blocos, returno);
    setseekbloco(arq, novo_bloco);
    print(0);
    fseek(arq,seek,SEEK_SET);
    if (line)
      if (line[0]=='!'){modo=2;}

}

void print(int fin){
    static int step=1;
    step++;
    int dots;
    int fitantes,fitapos;
    int flagvaziantes=1;
    int flagvaziapos=1;
    char fitaprint[46];
    char ponts[17];
    if (((modo == 2) || ((step > n_step)&&(modo==3))) && (modo != 1)) {
          dots = 16 - strlen(bloco_atual);
          fitantes = 20 - cabecote;
          fitapos  = cabecote + 20 - strlen(fita);
          if (fitantes<0){
              fitantes *= -1;
              flagvaziantes = 0;
          }
          if (fitapos<0){
              fitapos *= -1;
              flagvaziapos=0;
          }
          int cont=0;
          if (flagvaziantes){
              strcpy(fitaprint,"");
              for (int i=0;i<fitantes;i++){
                cont++;
                strcat(fitaprint,"_");
              }
              strncat(fitaprint,fita,cabecote);
              cont+=cabecote+5;
          }else{
             strcpy(fitaprint,"");
             for (int i=fitantes;i<=cabecote;i++)
                fitaprint[cont++]=fita[i];
             fitaprint[cabecote]='\0';
          }

          char pont[6];
          pont[0] = (char)delim_cabecote[0];
          pont[1] = ' ';
          pont[2] =(char)fita[cabecote];
          pont[3] = ' ';
          pont[4] = (char)delim_cabecote[1];
          pont[5] = '\0';

          strcat(fitaprint,pont);

          for (int i=cabecote+1;i<(cabecote+21);i++)
             fitaprint[cont++]=fita[i];
          fitaprint[45]='\0';

          memset(ponts,'.',dots);
          ponts[dots]='\0';
          printf("%s%s.%04d:%s\n",ponts,bloco_atual ,atoi(estado_atual),fitaprint);
    }
    if (fin){
       printf("\n");
       erro();
     }
}
