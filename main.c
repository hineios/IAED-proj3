#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.c"


#define maxAero 1000
 /* Vértices são representados por objetos do tipo Vertex.  Os vértices de um digrafo são 0,1,..,V-1. */

/*
 * Protótipos das funções
 */
 
void insereVoo(char *codigo, char *origem, char *destino, HORAS partida, HORAS chegada, float preco, LISTA *lista);
void fechaAero(char* aero, LISTA *lista);
void abreAero(char* aero, LISTA *lista);
void cancelaVoo(char* voo, LISTA *lista);
void adiaVoo(char* voo, HORAS horas, LISTA *lista);
void insereDados(char* codigos, char* codigo, struct lista_voos *lista);
void separaDados(char* codigo, struct lista_voos *voos);
char* dadosPercurso(char *dados, char *aux);
char* pedidoInfoI(char* aero, char* info, int contaOrig, int contaDesti, float maisbarato, HORAS maistarde, char* baratoDesti, char * tardioDesti, LISTA* lista);
char* pedidoInfoP(char* orig, char* dest, int contador, char* output, struct lista_voos *voo, LISTA* lista);
HORAS converte(int h, int m);
void insereCodigo(char*, int, CODIFICACAO*);
void criaGrafo(LISTA*dados1, CODIFICACAO* lista, Digraph *grafo);
int Codifica(char* aero, CODIFICACAO* lista);
char* AnalisaGrafo (char* origem, char *destino, char* output, CODIFICACAO *lista, Digraph *grafo);

static int dist[maxAero];
/*
 * Função main que efectua a leitura do ficheiro indicado, pede às funções definidas em funcoes.c para actualizarem 
 * a lista dos dados e quando forem pedidas informações escreve-as no ficheiro indicado.
 */

int main()
{
  char buffer[7+4+4+6+6+5+(7*1000)+1]; 
  LISTA dados = NULL;
  CODIFICACAO lista = NULL;
  struct lista_voos voos = {NULL};
	
  while (fgets(buffer, sizeof buffer, stdin)) 
  {
    char Companhia[6+1]="";
    char Origem[3+1], Destino[3+1];
    int hPartidaHora, hPartidaMin, hChegadaHora, hChegadaMin;
    int Inteiro=0;
    float Preco;
    
    if (sscanf(buffer, "i %s", Origem) == 1) 
      {
         int contaOrig=0;
         int contaDesti=0;
         char Info[4+1+3+1+3+1+4+1+4+1];
         char baratoDesti[]="000";
         char tardioDesti[]="000";
         float maisBarato=9000000.00;
         HORAS maisTarde ={0,0};
         
         printf("%s\n", pedidoInfoI(Origem, Info, contaOrig, contaDesti, maisBarato, maisTarde, baratoDesti, tardioDesti, &dados));
      }  
    else 
      if (sscanf(buffer, "r %s", Origem) == 1) 
        {
          abreAero(Origem, &dados);
        }  
      else 
        if (sscanf(buffer, "c %s", Companhia) == 1) 
          {
            cancelaVoo(Companhia, &dados);
          }  
        else 
          if (sscanf(buffer, "f %s", Origem) == 1) 
            {
             fechaAero(Origem, &dados);
            }        
          else 
            if (sscanf(buffer, "a %s %d:%d", Companhia, &hChegadaHora, &hChegadaMin) == 3) 
              {
                adiaVoo(Companhia, converte(hChegadaHora, hChegadaMin), &dados);
              }  
            else 
              if (sscanf(buffer, "p %s %s %d", Origem, Destino, &Inteiro) == 3)
                {
                  char Codigo[6+1]="0";
                  char Codigos[7*1000]="0";
                  char Output[2+1+10+(10*1000)]="0";
                  
                  dadosPercurso(buffer, Codigos);

                  insereDados(Codigos, Codigo, &voos);

                  printf("%s\n",pedidoInfoP(Origem, Destino, Inteiro, Output, &voos, &dados));
                  
                  voos.inicio = NULL;
                  voos.fim = NULL;
                  
                }          
              else 
                if (sscanf(buffer, "v %s %s %s %d:%d %d:%d %f", Companhia, Origem, Destino, &hPartidaHora, &hPartidaMin, &hChegadaHora, &hChegadaMin, &Preco) == 8) 
                  { 
                    insereVoo(Companhia, Origem, Destino, converte(hPartidaHora, hPartidaMin), converte(hChegadaHora, hChegadaMin), Preco, &dados);
                    insereCodigo(Origem, 0, &lista);
                    insereCodigo(Destino, 0, &lista);
                  }
                else
                  if (sscanf(buffer, "m %s %s", Origem, Destino) == 2)
                    {
                      char output[2+1+3+1] = " ";
                      Digraph grafo = DIGRAPHinit(maxAero);
                      criaGrafo(&dados, &lista, &grafo);
                      printf("%s\n", AnalisaGrafo(Origem, Destino, output, &lista, &grafo));
                    }
  }
  while ( dados != NULL)
  {
    LISTA aux = dados->proximo;
    free(dados);
    dados = aux;
  }
  while ( lista != NULL)
  {
    CODIFICACAO aux = lista->proximo;
    free(lista);
    lista = aux;
  }

  return 0;
}





