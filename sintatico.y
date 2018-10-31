%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "utils.c"
#include "lexico.c"
#include "gerar.c"

int yylex();
void yyerror(char *);

/* minhas variaveis */
int i,j=0;
int tipo_variavel = 0; //0 para inteiro e 1 para logico
char auxID[100]; 
long int tam;

%}

// Simbolo de partida
%start programa

// Simbolos terminais
%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_FUNCAO
%token T_FIMFUNCAO
%token T_IDENTIF
%token T_LEIA
%token T_ESCREVA
%token T_ENQTO
%token T_FACA
%token T_FIMENQTO
%token T_PARA
%token T_DE
%token T_ATE
%token T_PASSO
%token T_FIMPARA
%token T_SE
%token T_ENTAO
%token T_SENAO
%token T_FIMSE
%token T_ATRIB
%token T_VEZES
%token T_DIV
%token T_MAIS
%token T_MENOS
%token T_MAIOR
%token T_MENOR
%token T_IGUAL
%token T_E
%token T_OU
%token T_V
%token T_F
%token T_NUMERO
%token T_NAO
%token T_ABRE
%token T_FECHA
%token T_VETOR
%token T_LOGICO
%token T_INTEIRO

// Precedencia e associatividade
%left T_E T_OU
%left T_IGUAL
%left T_MAIOR T_MENOR
%left T_MAIS T_MENOS
%left T_VEZES T_DIV

%%

// Regras de producao
programa
      : cabecalho {emit(cabecalho); }  
        variaveis
        //funcoes
        T_INICIO lista_comandos 
        T_FIM {emit(fechar_contexto); }
      ;

cabecalho
      : T_PROGRAMA T_IDENTIF 
      ;

variaveis
      :  /* vazio */
      |  declaracao_variaveis 
      ;

declaracao_variaveis
      : declaracao_variaveis   
        tipo {CONTA_VARS=0;}
        lista_variaveis { 
            if(tipo_variavel == 1) {
                for(i=0; i<CONTA_VARS; i++){
                    emit(declarar_boolean,TSIMB[j].id, TSIMB[j].tam); 
                    j++;
                }
            } else {
                for(i=0; i<CONTA_VARS; i++){
                    emit(declarar_inteiro,TSIMB[j].id, TSIMB[j].tam) ;
                    j++;
                }  
            }
        }
        
     | tipo  {CONTA_VARS=0;}
        lista_variaveis { 
            if(tipo_variavel == 1) {
 	       for(i=0; i<CONTA_VARS; i++){
              emit(declarar_boolean,TSIMB[j].id, TSIMB[j].tam); 
              j++;  
	       }
            } else {
              for(i=0; i<CONTA_VARS; i++){
                emit(declarar_inteiro,TSIMB[j].id, TSIMB[j].tam) ;
                j++;
              }  
           }
         }
      ;

tipo
      : T_LOGICO {tipo_variavel=1;}
      | T_INTEIRO {tipo_variavel=0;}
      ;

lista_variaveis
      // insere_variavel: 
      // params: atom          -> O próximo token identificado no léxico. 
      //         tipo_variavel -> O tipo da variável identificado anteriormente
      :  lista_variaveis T_IDENTIF {insere_variavel (atomo,tipo_variavel,0); CONTA_VARS++; } 
      |  T_IDENTIF {insere_variavel (atomo,tipo_variavel,0); CONTA_VARS++;  }
      |  lista_variaveis T_VETOR {identificaVetor(atomo,auxID,&tam);insere_variavel(auxID,tipo_variavel,tam);CONTA_VARS++;} 
      |  T_VETOR {identificaVetor(atomo,auxID,&tam);insere_variavel(auxID,tipo_variavel,tam);CONTA_VARS++;} 
      ;


/*funcoes
      :  /* vazio 
      |  T_FUNCAO tipo T_IDENTIF T_ABRE tipo T_IDENTIF T_FECHA lista_comandos T_FIMFUNCAO
      ;*/

lista_comandos
      : /* vazio */
      | comando lista_comandos
      ;

comando
      : entrada_saida
      | repeticao
      | selecao
      | atribuicao
      | para
      ;

entrada_saida
      : leitura
      | escrita
      ;

leitura
      : T_LEIA T_VETOR
      {
          identificaVetor(atomo,auxID,&tam);
          POS_SIMB = busca_simbolo (auxID);
          if (POS_SIMB == -1){
              ERRO ("Variavel [%s] nao declarada!", auxID);
          } else {
              emit(leitura,atomo,TSIMB[POS_SIMB].tipo); 
          }
      }
      | T_LEIA T_IDENTIF
      {
          identificaVetor(atomo,auxID,&tam);
          POS_SIMB = busca_simbolo (auxID);
          if (POS_SIMB == -1){
              ERRO ("Variavel [%s] nao declarada!", auxID);
          } else {
              emit(leitura,atomo,TSIMB[POS_SIMB].tipo); 
          }
      }
      ;

escrita
      : T_ESCREVA T_VETOR
        {
          identificaVetor(atomo,auxID,&tam);
          POS_SIMB = busca_simbolo (auxID);
          if (POS_SIMB == -1){
              ERRO ("Variavel [%s] nao declarada!", auxID);
          } else {
              emit(imprime,atomo,TSIMB[POS_SIMB].tipo);
          } 
      }
      | T_ESCREVA T_IDENTIF
      {
          identificaVetor(atomo,auxID,&tam);
          POS_SIMB = busca_simbolo (auxID);
          if (POS_SIMB == -1){
              ERRO ("Variavel [%s] nao declarada!", auxID);
          } else {
              emit(imprime,atomo,TSIMB[POS_SIMB].tipo);
          }  
      }
      ;
      

repeticao
      : T_ENQTO
        expressao 
        T_FACA 
           {
             emit(repeticao, desempilhaChar(), 0);
           }
        lista_comandos 
        T_FIMENQTO
           {
             emit(repeticao, "", 1);          
           }
      ;

selecao
      : T_SE expressao  
        T_ENTAO
        {
            emit(selecao, desempilhaChar(), 0);
        }
        lista_comandos 
        T_SENAO
        {
            emit(selecao, "", 1);
        }
        lista_comandos 
        T_FIMSE
        {
            emit(selecao, "", 2);
        }
      ;
      
para
    : T_PARA termo
    {
        char *auxIdentificador = getTopoPAux();
        emit(para, auxIdentificador, -1, -1, -1, 0);
    }
    T_DE termo
    {
	char *n1 = desempilhaChar();
    char *auxIdentificador = desempilhaChar();
	int n1_int = atoi(n1);
	char identificador_copia[100] = {};
	char n1_copia[100] = {};
	
	strcat(identificador_copia, auxIdentificador);
	strcat(n1_copia, n1);

        emit(para, auxIdentificador, n1_int, -1, -1, 1);
	empilhaChar(identificador_copia);
	empilhaChar(n1_copia);
        
    }
    T_ATE termo
    {
	char *n2_aux = desempilhaChar();
	char *n1_aux = desempilhaChar();
	char *identificador_aux = desempilhaChar();

	char n1_copia[100] = {};
	char n2_copia[100] = {};
	char identificador_copia[100] = {};
	
	strcat(n1_copia, n1_aux);
	strcat(n2_copia, n2_aux);
	strcat(identificador_copia, identificador_aux);

        int n2 = atoi(n2_aux);
        int n1 = atoi(n1_aux);
        emit(para, identificador_aux, n1, n2, -1, 2);
	
	empilhaChar(identificador_copia);
	empilhaChar(n1_copia);
	empilhaChar(n2_copia);
    }
    T_PASSO termo T_FACA
    {
        int incremento = atoi(desempilhaChar());
	int n2 = atoi(desempilhaChar());
        int n1 = atoi(desempilhaChar());
        char *auxIdentificador = getTopoPAux();
        emit(para, auxIdentificador, n1, n2, incremento, 3);
    }
    lista_comandos T_FIMPARA
    {
        emit(para, "", -1, -1, -1, 4);
    }
    ;

atribuicao
      : T_IDENTIF 
          {
            identificaVetor(atomo,auxID,&tam);
            POS_SIMB = busca_simbolo (auxID);
            if (POS_SIMB == -1)
                ERRO ("Variavel [%s] nao declarada!", auxID);
            else
                empilhaChar(atomo);
          }
        T_ATRIB 
        expressao
          { 
                emit(atribuicao, desempilhaChar(), desempilhaChar());
          }
       | T_VETOR
         {
            identificaVetor(atomo,auxID,&tam);
            POS_SIMB = busca_simbolo (auxID);
            if (POS_SIMB == -1)
                ERRO ("Variavel [%s] nao declarada!", auxID);
            else
                empilhaChar(atomo);
          }
        T_ATRIB 
        expressao
          { 
                emit(atribuicao, desempilhaChar(), desempilhaChar());
          }
      
      ;


expressao
      : expressao T_VEZES expressao {
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "*");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_DIV expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "/");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_MAIS expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "+");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_MENOS expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "-");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_MAIOR expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, ">");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_MENOR expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "<");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_IGUAL expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "==");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_E expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "&&");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | expressao T_OU expressao{
            char* exp1 = desempilhaChar();
            char* exp2 = desempilhaChar();
            strcat(expr, exp2);
            strcat(expr, "||");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
        }
      | T_NAO expressao{
            char* exp1 = desempilhaChar();
            strcat(expr, "!");
            strcat(expr, exp1);
            empilhaChar(expr);
            strcpy(expr,"");
      }
      | termo
      ;

termo
      : T_IDENTIF
          {
            POS_SIMB = busca_simbolo (atomo);
            if (POS_SIMB == -1)
               ERRO ("Variavel [%s] nao declarada!",
                         atomo);
            else {
                empilhaChar(atomo);
                tipo_variavel = TSIMB[POS_SIMB].tipo;
               /*printf ("\tCRVG\t%d\n", 
                       TSIMB[POS_SIMB].tipo); */
            }   
          }
        | T_VETOR
        {
            identificaVetor(atomo,auxID,&tam);
            POS_SIMB = busca_simbolo (auxID);
            if (POS_SIMB == -1)
               ERRO ("Variavel [%s] nao declarada!",
                         auxID);
            else {
                empilhaChar(atomo);
                tipo_variavel = TSIMB[POS_SIMB].tipo;
               /*printf ("\tCRVG\t%d\n", 
                       TSIMB[POS_SIMB].tipo); */
            }   
        }
      | T_NUMERO
        {
          empilhaChar(atomo); 
        } 
      | T_V
      {
          empilhaChar("true");
      } 
      | T_F
      { 
          empilhaChar("false");
      }
      /*| T_NAO termo
      { 
          empilhaChar()
      }*/
      | T_ABRE
      {
          strcat(exprParenteses, "(");
      }
      expressao T_FECHA{
            char* aux1 = desempilhaChar(); // Expressão
            strcat(exprParenteses,aux1);
            strcat(exprParenteses, ")");
            empilhaChar(exprParenteses);
            strcpy(exprParenteses, "");
        }
      ;

%%
/*+--------------------------------------------------------+
  |          Corpo principal do programa COMPILADOR        |
  +--------------------------------------------------------+*/

int yywrap () {
   return 1;
}

void yyerror (char *s)
{
  ERRO ("ERRO SINTATICO");
}


int main ()
{
  yyparse ();
}
