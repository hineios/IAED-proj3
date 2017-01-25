#define Vertex int
/*
 * Definição de uma estrutura auxiliar para guardar os valores das horas de partida dos voos constítuido por um
 * inteiro que aramazena a componente das horas e outro que aramazena os minutos
 */
typedef struct
{
  int horas;
  int mins;
} HORAS;


struct voo
{
  char codigo[6+1], origem[3+1], destino[3+1];
  HORAS	partida, chegada;
  float preco;
  struct voo *proximo;
  int estadoOrig, estadoDesti;
};

struct percurso {
  char codigo[6+1];
  struct percurso *proximo;
};

struct lista_voos {
  struct percurso *inicio;
  struct percurso *fim;
};


typedef struct voo * LISTA;


struct codificacao
{
  char codigo[3+1];
  int numero;
  struct codificacao* proximo;
};


typedef struct codificacao* CODIFICACAO;



/******************************/
typedef int Item;
typedef struct queue *Q;

typedef struct QUEUEnode* link;

static link head, tail;

struct QUEUEnode { 
  Item item; 
  link next; 
};

struct queue { 
  link head; 
  link tail; 
};


/*********************************/

    typedef struct { 
       Vertex v; 
       Vertex w; 
    } Arc;

    /* A função ARC recebe dois vértices v e w e devolve um arco com ponta inicial v e ponta final w. */

   


    /* A estrutura digraph representa um digrafo. O campo adj é um ponteiro para a matriz de adjacência do digrafo. O campo V contém o número de vértices e o campo A contém o número de arcos do digrafo. */

    struct digraph {
       int V; 
       int A; 
       int **adj; 
    };

    /* Um objeto do tipo Digraph contém o endereço de um digraph. */

    typedef struct digraph *Digraph;
    
    

