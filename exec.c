#include "exec.h"

FILE *file;

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
    para(arq);
}

void exec(FILE *arq){
   pilha_blocos = initStack();
   static int n_exec=0;
   short type_cod;  //0 inst 1 block
   cabecote = 0;
   seek=0;
   char **vetoken = NULL;
   char *line=(char*)malloc(sizeof(char)*tam_line);

   setseekbloco(arq, "main");
   fseek(arq,seek,SEEK_SET);

   fgets(line,tam_line-1,arq);
   while(!feof(arq)){
       if (n_exec >= 500){
          printf("\nMT PARADA, POSSIVEL LOOP INFINITO\n\n" );
          para(arq);
       }

       if (line[0] == ';'){
         fgets(line,tam_line-1,arq);
         continue;
       }

       vetoken = decodline(line);

       if (!vetoken){
          fgets(line,tam_line-1,arq);
          continue;
       }

       if(strcmp(vetoken[0],"fim")==0){
            strtok(estado_atual,"\n");
            modo = 2;
            print(0, arq);
            printf("\nERROR TRANSIÇÃO BLOCO %s ESTADO %s COM %c NÃO DEFINIDA\n",bloco_atual, estado_atual, fita[cabecote]);
            para(arq);
       }

       if(atoi(vetoken[0]) == atoi(estado_atual)){
            if (strcmp(vetoken[2],"--")==0){
                  type_cod = 0;
               }else{
                  type_cod = 1;
               }
            char simb_fita[2];
            simb_fita[0]=fita[cabecote];
            simb_fita[1]='\0';
            if ((type_cod == 0) && ((strcmp(simb_fita, vetoken[1])==0) || (strcmp(vetoken[1],"*")==0))) {
                n_exec++;
                execinstr(vetoken, arq);
            }else{
                if (type_cod == 1){
                  execblock(vetoken, arq);
                }
            }
       }
       if (vetoken){
          free(vetoken);
          vetoken = NULL;
      }
      fgets(line,tam_line-1,arq);
   }
}
void para(FILE *arq){
      printf("MT ENCERROU\n\n");
      fclose(arq);
      exit(EXIT_SUCCESS);
}
void execinstr(char **vetline, FILE *arq){

    short fin=0;

// simbolo_novo
    if (strcmp(vetline[3],"*")!=0){
        fita[cabecote] = vetline[3][0];
    }

// movimento cabeçote

  if(strcmp(vetline[4],"e")==0){
      cabecote--;
  }else
    if (strcmp(vetline[4],"d")==0){
      cabecote++;
    }
  if (cabecote<0){
      for(int i=strlen(fita)-2;i>=0;i--){
          fita[i+1] = fita[i];
      }
      fita[0] = '_';
      cabecote = 0;
  }
// estdado_novo

    if (strcmp(vetline[5],"pare")==0){
          fin = 1;
    }else{
      if (strcmp(vetline[5],"retorne")==0){
          recall *retorno = popStack(pilha_blocos);
          if (!retorno){
                  printf("\nErro de retorno de bloco\n");
                  para(arq);
          }
          strcpy(bloco_atual,(char*)retorno->recall_bloco);
          n_bloco_atual =  retorno->n_bloco;
          strcpy(novo_estado, retorno->recall_state);
          strcpy(estado_atual,novo_estado);
          if (strcmp(novo_estado,"pare")==0){
              fin = 1;
          }
      }else{
            strcpy(novo_estado, vetline[5]);
          }
      }

// possivel !
    if (cont > 6)
      if (strcmp("!",vetline[6])==0){
        modo = 2;
      }
    if (strcmp(vetline[5],"retorne")!=0)
          print(fin, arq);
    setseekbloco(arq, bloco_atual);
    strcpy(estado_atual,novo_estado);
    fseek(arq,seek,SEEK_SET);
}
void execblock(char **vetline, FILE *arq){

    print(0, arq);
    char novo_bloco[17];
    strcpy(novo_bloco, vetline[1]);
    char estado_retorno[5];
    strcpy(estado_retorno,vetline[2]);
    recall *returno=NULL;
    returno = (recall*)malloc(sizeof(recall));
    strcpy((char*)returno->recall_bloco, bloco_atual);
    returno->n_bloco = n_bloco_atual;
    strcpy(returno->recall_state, estado_retorno);
    pushStack(pilha_blocos, returno);
    setseekbloco(arq, novo_bloco);
    print(0, arq);
    fseek(arq,seek,SEEK_SET);

    if (cont > 3)
      if (strcmp("!",vetline[3])==0){
        modo = 2;
      }
}

void print(int fin, FILE *arq){
    static int step=0;
    step++;
    int dots;
    int fitantes,fitapos;
    int flagvaziantes=1;
    int flagvaziapos=1;
    char fitaprint[46];
    char ponts[17];
    if (modo != 1) {
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
             for (int i=fitantes;i<cabecote;i++)
                fitaprint[cont++]=fita[i];
             fitaprint[cont]='\0';
             cont+=5;
          }

          char pont[6];
          pont[0] = (char)delim_cabecote[0];
          pont[1] = ' ';
          pont[2] =(char)fita[cabecote];
          pont[3] = ' ';
          pont[4] = (char)delim_cabecote[1];
          pont[5] = '\0';

          strcat(fitaprint,pont);
          for (int i=cabecote+1;i<cabecote+21;i++)
             fitaprint[cont++]=fita[i];
          fitaprint[45]='\0';

          memset(ponts,'.',dots);
          ponts[dots]='\0';
          printf("%s%s.%04d:%s\n",ponts,bloco_atual ,atoi(estado_atual),fitaprint);


          if ((n_step <= step)&&(modo==3)){
              char op[3];
              int n_temp=-1;
              printf("\nForneça opção (-r,-v,-s ou -n (None)): ");
              scanf("%s", op);
              if (strlen(op)>1)
                  switch (op[1]) {
                    case 'r':
                          modo = 1;
                      break;
                    case 'v':
                          modo = 2;
                      break;
                    case 's':
                          printf("Digite o numeros de passos: ");
                          scanf("%d", &n_temp);
                          while(n_temp <=0 ){
                            printf("Digite um numero maior que zero: ");
                            scanf("%d", &n_temp);
                          }
                          n_step = step + n_temp;
                          step_arg = n_temp;
                      break;
                    case 'n':
                          n_step += step_arg ;
                      break;
                    default:
                          n_step += step_arg ;
                      break;
                  }else{
                          n_step += step_arg ;
                  }
                  printf("\n");
          }
    }

    if (fin){
      if (modo==1){
          modo=2;
          print(1, arq);
       }
       printf("\n" );
       para(arq);
     }
}
