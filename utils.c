/*---------------------------------------------------------
 *  Estruturas e Rotinas Utilitarias do Compilador
 *
 *  Por Luiz Eduardo da Silva
 *--------------------------------------------------------*/

/*---------------------------------------------------------
 *  Limites das estruturas
 *--------------------------------------------------------*/
#define TAM_TSIMB 1000  /* Tamanho da tabela de simbolos */
#define TAM_PSEMA 1000  /* Tamanho da pilha semantica    */

/*---------------------------------------------------------
 *  Variaveis globais
 *--------------------------------------------------------*/
int TOPO_TSIMB     = 0;  /* TOPO da tabela de simbolos */
int TOPO_TFUNCOES  = 0;  /* TOPO da tabela de simbolos */
int TOPO_PSEMA     = 0;  /* TOPO da pilha semantica */
int TOPO_PAUX      = 0;  /* TOPO da pilha auxiliar */
int ROTULO         = 0;  /* Proximo numero de rotulo */
int CONTA_VARS     = 0;  /* Numero de variaveis */
int POS_SIMB;            /* Pos. na tabela de simbolos */
int aux;                 /* variavel auxiliar */
int numLinha = 1; /* numero da linha no programa */
char atomo[1000];   /* nome de um identif. ou numero */
char expr[1000];	   /*Vetor aux para guardar a expressao*/
char exprParenteses[1000];
char exprVetor[1000];
char vetAuxUtil[1000];
char vetIdentificador[1000];
char* vetAux; /* vetor para concaTENAR O ( E ) */


/*---------------------------------------------------------
 *  Rotina geral de tratamento de erro
 *--------------------------------------------------------*/
void ERRO (char *msg, ...) {
  char formato [255];
  va_list arg;
  va_start (arg, msg);
  sprintf (formato, "\n%d: ", numLinha);
  strcat (formato, msg);
  strcat (formato, "\n\n");
  printf ("\nERRO no programa"); 
  vprintf (formato, arg);
  va_end (arg);
  exit (1);
}

/*---------------------------------------------------------
 *  Tabela de Simbolos
 *--------------------------------------------------------*/
struct elem_tab_simbolos {
  char id[1000];
  int tipo;
  int tam;
} TSIMB [TAM_TSIMB], elem_tab;

struct elem_tab_funcoes {
  char id[1000];
  int tipo;
} TFUNCOES [TAM_TSIMB], elem_tab_funcao;

/*---------------------------------------------------------
 *  Pilha Semantica & Pilha Auxiliar
 *--------------------------------------------------------*/
int PSEMA[TAM_PSEMA];
char PAUX[TAM_PSEMA][50];

/*---------------------------------------------------------
 * Funcao que BUSCA um simbolo na tabela de simbolos.       
 *      Retorna -1 se o simbolo nao esta' na tabela        
 *      Retorna i, onde i e' o indice do simbolo na tabela
 *                 se o simbolo esta' na tabela             
 *--------------------------------------------------------*/
int busca_simbolo (char *ident)
{
  int i = TOPO_TSIMB-1; // Posição do topo da minha tabela de símbolos
  for (;strcmp (TSIMB[i].id, ident) && i >= 0; i--);
  return i;
}
int busca_simbolo_funcao (char *ident)
{
  int i = TOPO_TFUNCOES-1; // Posição do topo da minha tabela de símbolos
  for (;strcmp (TFUNCOES[i].id, ident) && i >= 0; i--);
  return i;
}

/*---------------------------------------------------------
 * Funcao que INSERE um simbolo na tabela de simbolos.      
 *    Se ja' existe um simbolo com mesmo nome e mesmo nivel 
 *    uma mensagem de erro e' apresentada e o  programa  e' 
 *    interrompido.                                         
 *--------------------------------------------------------*/
void insere_simbolo (struct elem_tab_simbolos *elem)
{
  if (TOPO_TSIMB == TAM_TSIMB) {
     ERRO ("OVERFLOW - tabela de simbolos");
  }
  else {
     // Verifico se o simbolo já existe
     POS_SIMB = busca_simbolo (elem->id);
     // Se já existe sai do programa
     if (POS_SIMB != -1) {
       ERRO ("Identificador [%s] duplicado", elem->id);
     }
     // se não existe insere no topo da tabela de simbolos TSIMB, e incrementa o topo da tabela de símbolos
     TSIMB [TOPO_TSIMB] = *elem;
     TOPO_TSIMB++;
  }
}

void insere_simbolo_funcao (struct elem_tab_funcoes *elem)
{
  if (TOPO_TFUNCOES == TAM_TSIMB) {
     ERRO ("OVERFLOW - tabela de funções");
  }
  else {
     // Verifico se o simbolo já existe
     POS_SIMB = busca_simbolo_funcao (elem->id);
     // Se já existe sai do programa
     if (POS_SIMB != -1) {
       ERRO ("Identificador de função [%s] duplicado", elem->id);
     }
     // se não existe insere no topo da tabela de simbolos TSIMB, e incrementa o topo da tabela de símbolos
     TFUNCOES [TOPO_TFUNCOES] = *elem;
     TOPO_TFUNCOES++;
  }
}


/*---------------------------------------------------------
 * Funcao de insercao de uma variavel na tabela de simbolos
 *---------------------------------------------------------*/
// EX: LOGICO a -> *ident = a, tipo = 1
void insere_variavel (char *ident,int tipo, int tam) {
   strcpy (elem_tab.id, ident);
   elem_tab.tipo = tipo;
   elem_tab.tam = tam;
   insere_simbolo (&elem_tab);
}

void limpa_lista_variaveis(){
   TOPO_TSIMB = 0;
}

/*---------------------------------------------------------
 * Funcao de insercao de uma função na tabela de funções
 *---------------------------------------------------------*/
void insere_funcao (char *ident,int tipo) {
   strcpy (elem_tab_funcao.id, ident);
   elem_tab_funcao.tipo = tipo;
   insere_simbolo_funcao (&elem_tab_funcao);
}

/*---------------------------------------------------------
 * Rotinas para manutencao da PILHA SEMANTICA              
 *--------------------------------------------------------*/
void empilha (int n) {
    // verifica se a pilha está cheia, se estiver retorna um erro
    if (TOPO_PSEMA == TAM_PSEMA) {
        ERRO ("OVERFLOW - Pilha Semantica");
    }
    PSEMA[TOPO_PSEMA++] = n;
}

int desempilha () {
    // verifica se a pilha está vazia, se estiver retorna um erro
    if (TOPO_PSEMA == 0) {
        ERRO ("UNDERFLOW - Pilha Semantica");
    }
    return PSEMA[--TOPO_PSEMA];
}

void empilhaChar(char* termo){
    if(TOPO_PAUX == TAM_PSEMA){
        ERRO ("OVERFLOW - Pilha Auxiliar");
    }
    strcpy(PAUX[TOPO_PAUX++], termo);
}

char* desempilhaChar () {
    // verifica se a pilha está vazia, se estiver retorna um erro
    if (TOPO_PAUX == 0) {
        ERRO ("UNDERFLOW - Pilha Auxiliar");
    }
    return PAUX[--TOPO_PAUX];
}

char *getTopoPAux(){
    char *temp = PAUX[--TOPO_PAUX];
	TOPO_PAUX++;
    return temp;
}

void identificaVetor(char *atomo, char *ident, long int *tam){
   //printf("\nAtomo: %s", atomo); 

   char *tamanho = malloc(sizeof(char)*100);
   char *start_ident, *start_tamanho;

   start_ident = ident;
   start_tamanho = tamanho;

  while(*atomo != '\0' && *atomo != '[') {
    *ident = *atomo;
    ident++;atomo++;
  }
  *ident = '\0'; // Adiciona \0 para indicar final da string

  atomo++;
  ident = start_ident;

  while(*atomo != '\0' && *atomo != ']'){
    *tamanho = *atomo;
     tamanho++;atomo++;
  }

  tamanho = start_tamanho;
  *tam = atoi(tamanho);
}
