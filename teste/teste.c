#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **decodline(char *line){
    char **vetoken=NULL;
    char *token=NULL;
    int cont=0;
    // token =  strtok(line,";\n");
    token =  strtok(line," \t");
    printf("ola\n" );
    while (token) {
      printf("token[%d]=%s\n", cont,token);
      cont++;
      if(!vetoken){
          vetoken = (char**)malloc(sizeof(char*));
          vetoken[cont-1] = token;
      }else{
          vetoken = (char**)realloc(vetoken,(cont)*sizeof(char*));
          vetoken[cont-1] = token;
      }
      token = strtok(NULL," \t");
    }
    printf("exit\n");
    return vetoken;
}



int main(int argc, char const *argv[]) {
    char* pt=" ola        mundo            !!   ";
    decodline(pt);

  return 0;
}
