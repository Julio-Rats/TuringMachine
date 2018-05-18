#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exec.h"
#include "decodArgs.h"

void interface();

int main(int argc, char *argv[]){
  if(argc < 3){
      printf("\nError: Falta de parametros, exemplo\n\n\t%s <Opçõees> <Fonte(Programa)>\n\n",argv[0]);
      printf("Opções: < -r > Modo execucao silenciosa\n\t");
      printf("< -v > Modo debug, passo a passo\n\t");
      printf("< -s n > n computações com parada para uma nova entrada de modo\n\n");
      printf("Fonte(Progama): Entrada com arquivo.MT com codigo de execução\n\n");
      exit(1);
  }
  cabecote = 0;
  decodArgs(argc, argv);
  interface();

  printf("fita  = %s\n", fita);
//  modo = type_v;
  //modo = 1;
  //modo = 2;
//  if(modo == type_v)
  printf("modo = %d\n", modo);
  printf("n_step   = %d\n", n_step);
  printf("cabeçote = %s\n", delim_cabecote);
  return 0;
}

void interface(){
  system("clear");
  printf("Simulador de Maquína de Turing ver. 1.0\nDesenvolvido como trabalho pratíco para ");
  printf("a disciplina de Teoria da Computação\n" );
  printf("Autores: Julio Cesar M.C. e Renato Borges B.\tIFMG 2018.\n\nForneça a palavra inicial: ");
  scanf("%s", fita);
}
