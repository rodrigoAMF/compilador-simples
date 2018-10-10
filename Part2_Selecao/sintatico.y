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

%}

// Simbolo de partida
%start programa

// Simbolos terminais
%token T_PROGRAMA
%token T_INICIO
%token T_FIM
%token T_IDENTIF
%token T_LEIA
%token T_ESCREVA
%token T_ENQTO
%token T_FACA
%token T_FIMENQTO
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
                    emit(declarar_boolean,TSIMB[j++].id);  
                }
            } else {
                for(i=0; i<CONTA_VARS; i++){
                    emit(declarar_inteiro,TSIMB[j++].id);
                }  
            }
        }
        
     | tipo  {CONTA_VARS=0;}
        lista_variaveis { 
            if(tipo_variavel == 1) {
 	       for(i=0; i<CONTA_VARS; i++){
	          emit(declarar_boolean,TSIMB[j++].id);  
	       }
            } else {
              for(i=0; i<CONTA_VARS; i++){
                emit(declarar_inteiro,TSIMB[j++].id);
              }  
           }
         } 
      ;

tipo
      : T_LOGICO {tipo_variavel=1;}
      | T_INTEIRO {tipo_variavel=0;}
      ;

lista_variaveis
      : lista_variaveis T_IDENTIF {insere_variavel (atomo,tipo_variavel); CONTA_VARS++; }  
      // insere_variavel: 
      // params: atom          -> O próximo token identificado no léxico. 
      //         tipo_variavel -> O tipo da variável identificado anteriormente
      | T_IDENTIF {insere_variavel (atomo,tipo_variavel); CONTA_VARS++; } 
         
      ;

lista_comandos
      : /* vazio */
      | comando lista_comandos
      ;

comando
      : entrada_saida
      | repeticao
      | selecao
      | atribuicao
      ;

entrada_saida
      : leitura
      | escrita
      ;

leitura
      : T_LEIA  
        T_IDENTIF 
          { 
            POS_SIMB = busca_simbolo (atomo);
            if (POS_SIMB == -1)
                ERRO ("Variavel [%s] nao declarada!",
                           atomo);
	    else {
                emit(leitura,atomo,TSIMB[POS_SIMB].tipo); 
            }
          }
      ;

escrita
      : T_ESCREVA expressao
          {
          vetAux = desempilhaChar();
          emit(imprime,vetAux,tipo_variavel); }
      ;

repeticao
      : T_ENQTO
           { 
             printf ("L%d\tNADA\n", ++ROTULO);
             empilha (ROTULO);
           } 
        expressao 
        T_FACA 
           {
             printf ("\tDSVF\tL%d\n",++ROTULO);
             empilha (ROTULO);
           }
        lista_comandos 
        T_FIMENQTO
           {
             aux = desempilha();
             printf ("\tDSVS\tL%d\n", desempilha()); 
             printf ("L%d\tNADA\n", aux);           
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

atribuicao
      : T_IDENTIF 
          { 
            POS_SIMB = busca_simbolo (atomo);
            if (POS_SIMB == -1)
                ERRO ("Variavel [%s] nao declarada!", atomo);
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
      | termo
      ;

termo
      : T_IDENTIF
          {
            empilhaChar(atomo);
            POS_SIMB = busca_simbolo (atomo);
            if (POS_SIMB == -1)
               ERRO ("Variavel [%s] nao declarada!",
                         atomo);
            else {
                tipo_variavel = TSIMB[POS_SIMB].tipo;
               /*printf ("\tCRVG\t%d\n", 
                       TSIMB[POS_SIMB].tipo); */
            }   
          }
      | T_NUMERO
          { printf ("\tCRCT\t%s\n", atomo); } 
      | T_V
          { printf ("\tCRCT\t1\n"); } 
      | T_F
          { printf ("\tCRCT\t0\n"); } 
      | T_NAO termo
          { printf ("\tNEGA\n"); }
      | T_ABRE
        {
            strcat(exprParenteses, "(");
        }
        expressao
        T_FECHA{
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
