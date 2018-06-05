#include "decodc.h"

void getBlocos(FILE *arq){
    rewind(arq);          // Reinicia ponteiro do arquivo.
    char **vetline;       // Saida da função decodline.
    char line[tam_line];  // Vetor de char, pra leitura do arquivo.
    n_blocos = 0;         // Tamanho do vetor blocos.

    // Faz leitura no aquivo, ate "\n ou \0", ou tamanho passado parametro.
    fgets(line,sizeof(line)-1,arq);
    while(!feof(arq)){
        // Trata comentario com, com ";" no incio da linha.
        if (line[0] == ';'){
          fgets(line,sizeof(line)-1,arq);
          continue;
        }
        // Chamada da função quebrando a linha em tokens.
        vetline = decodline(line);
        if (!vetline){
          fgets(line,sizeof(line)-1,arq);
          continue;
        }
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
        // Refaz a leitura para o loop.
        fgets(line,sizeof(line)-1,arq);
    }
}

char **decodline(char *line){
    char **vetoken = NULL;  // Veotor de string de saida.
    char *token    = NULL;  // String usada para strtok.
    cont = 0;               // Tamanho do Veotor de string (vetoken).

    token =  strtok(line,";\n");  // Trata comentario no meio da linha.
    token =  strtok(token," \t"); // Quebra em tabulação e/ou espaço dos tokens.

    while (token) {
        // Aloca e expande o tamanho do vetor para saida.
        if(!vetoken){
            vetoken = (char**) malloc((++cont)*sizeof(char*));
        }else{
            vetoken = (char**) realloc(vetoken,(++cont)*sizeof(char*));
        }
        // Setando o token no vetor.
        vetoken[cont-1] = token;
        // Pega proximo token.
        token = strtok(NULL," \t");
    }
    return vetoken;
}
