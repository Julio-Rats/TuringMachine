#include "exec.h"

#define NO_LOOP 0 // 1-True, 0-False

/*
  Função onde procura pelo nome do bloco, e seta as variaveis de controle da
    MT, de acordo com as variaveis do bloco a ser executado.
        variaveis de um bloco:
                name          : Nome do bloco.
                initState     : Posição no arquivo onde inicia o bloco.
                position_file  : Numero da fila do bloco sendo executando.
                ================> variaveis de controle da MT <==============
                name_bloco    : Nome do bloco a ser executado.
                estado_atual  : Estado atual na MT.
                seek          : Posição do arquivo para busca de blocos.
                n_bloco       : Numero de blocos salvos no vetor (length).
*/
void setseekbloco(FILE *arq, u_int8_t*name_bloco)
{
  strcpy(bloco_atual,name_bloco);
  for(u_int16_t i = 0; i < n_blocos; i++)
     if(strcmp(blocos[i].name,name_bloco)==0)
     {
          strcpy(estado_atual, blocos[i].initState);
          seek = blocos[i].position_file;
          return;
    }
    fprintf(stderr, "\nERRO BLOCO '%s' NÃO ENCONTRADO\n", name_bloco);
    para(arq);
}

void exec(FILE *arq)
{
   n_exec = 0;        // Contador de numeros de execução.
   pilha_blocos       = initStack(); // Pilha para chamadas de blocos.
   cabecote           = 0;           // Reset posição do cabeçote sobre a fita.
   u_int8_t** vetoken = NULL;        // Vetor com as tokens das linhas de intstrução.
   u_int8_t*  line    = (u_int8_t*) malloc(sizeof(u_int8_t)*(TAM_LINE)); // "String" leitura do aquivo.
   int8_t type_cod;                  // Tipo de intstrução a ser executada, 0 = intstrução normal, 1 = intstrução chamada bloco.

   setseekbloco(arq, "main");    // Seta variaveis de controle do bloco main.
   fseek(arq, seek, SEEK_SET);   //  Aplica posição inicio do bloco main.

   fgets(line, TAM_LINE-1, arq); // Leitura de uma linha do arq.
   while(!feof(arq)){

       if(NO_LOOP)
           if (n_exec >= 500000)// Verifica quant de interações, tratar loops.
           {
              if (modo != 3)
              {
                  print(0,arq);  // Chama função para imprimir
                  modo = 2;      // Seta para imprimir.
              }    // Verifica se esta no modo de não impressão.
              fprintf(stderr, "\nMT PARADA, POSSIVEL LOOP INFINITO\n\n" );
              para(arq);
           }

       if (line[0] == ';') // Verifica linha de comentario.
       {
         fgets(line,TAM_LINE-1,arq);
         continue;
       }

       vetoken = decodline(line);  // Decodifica linha e retorna tokens

       if (!vetoken)  // Verifica se a linha foi de comentario.
       {
          fgets(line,TAM_LINE-1,arq);
          continue;
       }

       if(strcmp(vetoken[0],"fim")==0)  // Verifica se não existe transição definida.
       {
            strtok(estado_atual,"\n");   //  Remove \n para apresentação no printf.
            modo = 2;                    //   Muda modo para que acha sempre essa impressão.
            print(0, arq);               //    Printa essa ultima execução.
            // ----- MANDA MSG COM ERRO PARA O USUARIO ----- //
            fprintf(stderr, "\nERROR TRANSIÇÃO BLOCO '%s' ESTADO '%s' COM '%c' NÃO DEFINIDA\n\n",bloco_atual, estado_atual, fita[cabecote]);
            fprintf(stderr, "ESTADO '%s' NÃO EXISTE ", estado_atual);
            fprintf(stderr, "OU SIMBOLO '%C' NÃO DEFINIDO NO ALFABETO\n", fita[cabecote]);
            para(arq);   // Finaliza MT.
       }

       if(atoi(vetoken[0]) == atoi(estado_atual))  // Verifica se esta numa transição desse estado.
       {
            if (cont < 3) // Verifica erro de SINTAXE.
            {
                fprintf(stderr, "ERRO SINTAXE BLOCO '%s' ESTADO '%s'\n\n",
                         bloco_atual, estado_atual);
                fclose(arq);
                exit(EXIT_FAILURE);
            }
            if (strcmp(vetoken[2],"--")==0) // Define o tipo da intstrução.
                type_cod = 0;   // Intstrução normal.
            else
                type_cod = 1;   // Intstrução

            simbolo_atual[0] = fita[cabecote]; // Seta simbolo atual da fita.
            simbolo_atual[1] = '\0';
            if ((type_cod == 0) && ((strcmp(simbolo_atual, vetoken[1]) == 0) ||
                      (strcmp(vetoken[1],"*") == 0))) { // Verifica se pertece a esta transição.

                n_exec++;  // Incrimenta num de execução feitas.
                execinstr(vetoken, arq);  // Executa linha de intstruções normais.
            }
            else
                if (type_cod == 1)
                  execblock(vetoken, arq); // Executa linha de intstruções de blocos.
       }

       if (vetoken)   // Desaloca Tokens.
       {
          free(vetoken);
          vetoken = NULL;
      }

      fgets(line,TAM_LINE-1,arq);  // Leitura da proxima linha e loop.
   }
}
/*
    Para execução da MT.
*/
void para(FILE *arq)
{
      printf("\nMT ENCERROU:  %d execuções efetuadas\n\n", n_exec);
      fclose(arq);
      exit(EXIT_SUCCESS);
}
/*
      Executa transição 'setando' as variaveis de controle
        da MT, printa se estiver no modo correto, e volta para
        inicio do bloco no aquivo para busca de nova transição
        com novo estado e simbolo.
*/
void execinstr(u_int8_t** vetline, FILE* arq)
 {

    int8_t fin = 0;   // Define se Fim de execução; 1==fim.
    // Verifica erro de SINTAXE.
    if (cont < 6)
    {
      fprintf(stderr, "ERRO SINTAXE BLOCO '%s' ESTADO '%s'\n\n",
                bloco_atual, estado_atual);
      fclose(arq);
      exit(EXIT_FAILURE);
    }
    // simbolo_novo
    if (strcmp(vetline[3],"*") != 0)
        fita[cabecote] = vetline[3][0];

    // movimento cabeçote
    if(strcmp(vetline[4],"e")==0)
         cabecote--;
    else if (strcmp(vetline[4],"d")==0)
         cabecote++;

    // Verifica erro de SINTAXE.
    else if (strcmp(vetline[4],"i")!=0)
    {
        fprintf(stderr, "\nERRO SINTAXE MOVIMENTO BLOCO '%s' ESTADO '%s' COM SIMBOLO '%s'\n\n",
                  bloco_atual, estado_atual, estado_atual);
        fclose(arq);
        exit(EXIT_FAILURE);
    }
    // Tratamento se o cabecote ir alem do inicio da fila, indice -1 em C.
    if (cabecote<0)
    {
        for(int32_t i = (strlen(fita)-2) ; i >= 0 ; i--)
            fita[i+1] = fita[i];

      fita[0]   = '_';
      cabecote = 0;
    }
    // Estado novo
    if (strcmp(vetline[5],"pare")==0) // Verifica Fim do algoritimo.
         fin = 1;
    else
    {
      if (strcmp(vetline[5],"retorne")==0)  // Verifica retorno de um bloco.
      {
          do{
              recall *retorno = popStack(pilha_blocos); // Desempilha bloco da pilha.
              if (!retorno)  // Trata algum erro se ocorrer.
              {
                      printf("\nERRO DE RETORNO DO BLOCO '%s' \n", bloco_atual);
                      para(arq);
              }
              /* Seta variaveis de controle:
                      bloco_atual : Nome do bloco atual.
                      n_bloco_atual : Posição no vetor (indice).
                      novo_estado   : Novo Estado da MT, estado de retorno.
                      estado_atual  : Estado atual da MT.
              */
              strcpy(bloco_atual,  (u_int8_t*)retorno->recall_bloco);
              strcpy(novo_estado,  retorno->recall_state);
              strcpy(estado_atual, novo_estado);
              // Verifica se a retornada é um pare.
              if (strcmp(novo_estado,"pare") == 0)
              {
                  fin = 1;
                  strcpy(novo_estado,  (u_int8_t*) retorno->final_state);
                  strcpy(estado_atual, novo_estado);
              }
          }while (strcmp(novo_estado,"retorne") == 0);
      }
      else
      {
          // Caso não seja um retorno seta o novo estado.
          if (strcmp(vetline[5],"*")==0)
              strcpy(novo_estado, estado_atual);
          else
            strcpy(novo_estado, vetline[5]);

      }
    }
    // Tratar o comando "!".
    if (cont > 6)
        if (strcmp("!",vetline[6]) == 0)
            modo = 2;
    /*
      Imprime a execução e seta o inicio do bloco no arq para
          nova busca de transição para novo estado e simbolo.
    */
    print(fin, arq);
    setseekbloco(arq, bloco_atual);
    strcpy(estado_atual, novo_estado);
    fseek(arq,seek, SEEK_SET);
}
/*
    Executa instrução de chamada de blocos, empilha a o bloco atual.
*/
void execblock(u_int8_t** vetline, FILE* arq)
{
    print(0, arq);  // Imprime execução atual.
    recall *retorno = NULL;
    retorno         = (recall*) malloc(sizeof(recall)); // Aloca ED de chamada de bloco.
    if (!retorno)  // Trata possivel erro de alocação.
    {
        fprintf(stderr, "\nERRO ALOCAMENTO DE CHAMADA DE BLOCO\n\n");
        exit(EXIT_FAILURE);
    }

    strcpy((u_int8_t*)retorno->recall_bloco, bloco_atual); // Seta na strtc nome do Bloco atual.
    if (strcmp(vetline[2],"pare") == 0)
         strcpy(retorno->final_state, estado_atual);       //  Seta na strtc estado de retorno.

    strcpy(retorno->recall_state, vetline[2]);      //   Seta na strtc estado de retorno.
    pushStack(pilha_blocos, retorno);               //    Empilha esse bloco na ED pilha.
    setseekbloco(arq, vetline[1]);                  //     Seta variaveis de controle.
    print(0, arq);                                  //      Imprime execução.
    fseek(arq,seek,SEEK_SET);                       //       Seta posição no arq com novo bloco.

    if (cont > 3)   // Trata operador "!"
      if (strcmp("!",vetline[3])==0)
          modo = 2;
}

/*
  Imprime conforme requisitado no documento do trabalho.
*/
void print(int16_t fin, FILE* arq)
{
    static u_int16_t step = 0;   // Controle do modo -s
    step++;

    int16_t dots;
    int16_t fitantes,fitapos;
    int8_t flagvaziantes = 1;
    u_int8_t fitaprint[46];
    u_int8_t ponts[17];

    if (modo != 1)   // Modo de impressão.
    {
          dots    = 16 - strlen(bloco_atual);      // Sobra do nome do bloco, a ser preenchido de pontos.
          fitapos  = cabecote + 20 - strlen(fita);   // Excesso ou falta de simbolos depois do cabeçote.
          fitantes = 20 - cabecote;                 // Excesso ou falta de simbolos antes do cabeçote.
          // Verifica se houve excesso antes.
          if (fitantes < 0)
          {
              fitantes     *= -1; // "ABS"
              flagvaziantes =  0;// Desativa FLAG;
          }
          // Verifica se houve excesso apos.
          if (fitapos < 0)
              fitapos     *= -1;

          int16_t cont = 0;
          // Cria a "LINHA" de impressão.
          if (flagvaziantes)  // Trata se tiver menos de 20 antes do cabecote.
          {
              strcpy(fitaprint,"");
              for (int16_t i = 0 ; i < fitantes ; i++)
                  strcat(fitaprint,"_");

              cont = fitantes;
              strncat(fitaprint,fita,cabecote);
              cont += cabecote;
          }
          else
          {  // Trata se tiver mais de 20 antes do cabecote.
             strcpy(fitaprint,"");
             for (int32_t i = fitantes ; i < cabecote ; i++)
                  fitaprint[cont++] = fita[i];

             fitaprint[cont] = '\0';
          }

          u_int8_t pont[6];
          // Cria "visual" do cabeçote.
          pont[0] = (u_int8_t)delim_cabecote[0];
          pont[1] = ' ';
          pont[2] =(u_int8_t)fita[cabecote];
          pont[3] = ' ';
          pont[4] = (u_int8_t)delim_cabecote[1];
          pont[5] = '\0';
          cont   += 5;

          // Adiciona cabecote na impressão.
          strcat(fitaprint,pont);
          // Adiciona a frente do cabecote na impressão.
          for (int16_t i = cabecote + 1; i < cabecote + 21; i++)
                fitaprint[cont++] = fita[i];

          fitaprint[45] = '\0';

          // ADD pontos ante do nome do bloco
          memset(ponts,'.',dots);
          ponts[dots]  = '\0';
          // Imprimi.
          printf("%s%s.%04d:%s\n",ponts,bloco_atual ,atoi(estado_atual),fitaprint);

          // Trata modo -s, quando o valor inspirar.
          if ((n_step <= step) && (modo == 3))
          {
              u_int8_t op[3];
              int16_t  n_temp = -1;
              printf("\nForneça opção ('-r','-v','-s' ou '-n' (None)): ");
              scanf("%s", op);
              // Pega a nova op de modo, se for -s ou -n trata possiveis erros.
              if (strlen(op)>1)
                  switch (op[1])
                  {
                    case 'r':
                          modo = 1;
                      break;
                    case 'v':
                          modo = 2;
                      break;
                    case 's':
                          printf("Digite o numeros de passos: ");
                          scanf("%d", &n_temp);
                          while(n_temp <=0 )
                          {
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
                  }
                  else
                      n_step += step_arg ;
                  printf("\n");
          }
    }
    // Caso o modo encontre um pare , ele entrara aq e finalizara a MT.
    if (fin)
    {
      if (modo == 1)
      {
           modo = 2;
           print(1, arq);
       }
       para(arq);
    }
}
