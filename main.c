#include "main.h"

int main(u_int8_t argc, u_int8_t* argv[])
{
    if(argc < 3)
        erroArgs(argv[0]);

    FILE *file;
    if (!(file = fopen(argv[argc-1],"r")))
    {
        fprintf(stderr, "\nERROR AO TENTAR ABRIR O ARQUIVO %s\n\n", argv[argc-1]);
        exit(EXIT_FAILURE);
    }

    decodArgs(argc, argv);
    getBlocos(file);

    memset(fita,'_',TAM_LINE);
    interface();
    exec(file);

    return 0;

}

void interface(){
  u_int8_t input[TAM_INPUT];
  system("clear");
  printf("Simulador de Máquina de Turing ver. 1.0\nDesenvolvido como trabalho prático para ");
  printf("a disciplina de Teoria da Computação\n" );
  printf("Autor: Júlio César M.Cândido - IFMG 2018 Campus Formiga.\n\nForneça a palavra inicial: ");
  scanf("%s", input);
  printf("\n");
  strncpy(fita,input,strlen(input));
}

void erroArgs(u_int8_t* exec_name){
  system("clear");
  printf("Error: Falta de parametro, exemplo:\n\n\t%s <Opções> <Fonte(Programa)>\n\n", exec_name);
  printf("Opções: < -r > Modo execuçao silenciosa\n\t");
  printf("< -v > Modo debug, passo a passo\n\t");
  printf("< -s n > n computações com parada para uma nova entrada de modo\n\t");
  printf("[ -head \"xx\"] marcadores do cabeçote na impressão da fita\n\n");
  printf("Fonte(Progama): Entrada com arquivo.MT com codigo de execução\n\n");
  exit(1);
}
