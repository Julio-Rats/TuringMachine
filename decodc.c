#include "decodc.h"

void getBlocos(FILE *arq){
    rewind(arq);          // Reinicia ponteiro do arquivo.
    char line[tam_line];  // Vetor de char, pra leitura do arquivo.
    n_blocos = 0;         // Tamanho do vetor blocos.
    char **vetline;       // Saida da função decodline.

    // Faz leitura no aquivo, ate "\n ou \0", ou tamanho passado parametro.
    fgets(line,sizeof(line)-1,arq);
    while(!feof(arq)){
        // Trata comentario com, com ";" no incio da linha.
        if (line[0] == ';'){
          fgets(line,tam_line,arq);
          continue;
        }
        // Chamada da função quebrando a linha em tokens.
        vetline = decodline(line);
        // Verifica se a linha é uma declaração de um bloco.
        if (strcmp(vetline[0],"bloco")==0){
              // Tramento de erro sintaxe.
              if (cont < 2){
                 fprintf(stderr, "ERROR SINTAXE BLOCOS\n\n");
                 exit(EXIT_FAILURE);
              }else{
                  if (cont < 3){
                    fprintf(stderr, "ERROR SINTAXE BLOCOS, BLOCO %s\n\n", vetline[1]);
                    exit(EXIT_FAILURE);
                  }
              }
              // Criando o vetor, e expandindo o seu tamanho a cada novo bloco.
              if(n_blocos == 0){
                 blocos = (bloco *) malloc(sizeof(bloco)*(++n_blocos));
              }else{
                 blocos = (bloco *) realloc(blocos,sizeof(bloco)*(++n_blocos));
              }
              // Setando o bloco no vetor blocos.
              strcpy(blocos[n_blocos-1].name, vetline[1]);
              blocos[n_blocos-1].position_file = ftell(arq); // posição no arquivo.
              strcpy(blocos[n_blocos-1].initState, vetline[2]);
        }
        fgets(line,sizeof(line)-1,arq);
    }
}

char **decodline(char *line){
    char **vetoken=NULL;
    char **teste=(char**)malloc(sizeof(char*));
    char *token=NULL;
    cont=0;
    token =  strtok(line,";\n");
    token =  strtok(token," \t");
    while (token) {
      cont++;
      if(cont==1){
          vetoken = (char**)malloc(sizeof(char*));
          vetoken[cont-1] = token;
      }else{
          if (cont == 2){
            memcpy(teste, vetoken, sizeof(char*));
            free(vetoken);
          }
          teste = realloc(teste,(cont)*sizeof(char*));
          teste[cont-1] = token;
      }
      token = strtok(NULL," \t");
    }
    if(cont == 0){
      teste[0]=malloc(sizeof(char)*2);
      strcpy(teste[0],"-1");
    }
    if (cont == 1){
      return vetoken;
    }
    return teste;
}
