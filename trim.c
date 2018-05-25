#include "trim.h"

char *Trim(char *line){
    int init=0, last=0;
    // pega o primeiro e ultimo indice com algum simbolo
    for(int i=0;i<strlen(line);i++){
        if(line[i]==' '){
            if(last==0){
              init=i;
              init++;
            }
        }else{
            last=i;
        }
    }
    // cria a nova string sem espaços no começo e no fim
    char *trim_txt = (char *)malloc(sizeof(char)*(last-init+2));
    for(int i=0;i<((last-init+1));i++){
       trim_txt[i]=line[init+i];
    }
    trim_txt[(last-init+1)]='\0';
    return trim_txt;
}
