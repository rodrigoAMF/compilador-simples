%{

#include "sintatico.h"

%}

identificador  [a-zA-Z]([a-zA-Z0-9])*
numero         [0-9]+
espaco         [ \t]+
novalinha      [\n]

%x comentario

%%

programa	return T_PROGRAMA;
inicio  	return T_INICIO;
fimprograma	return T_FIM;
funcao      return T_FUNCAO;
retorne     return T_RETORNE;
fimfuncao   return T_FIMFUNCAO;

leia		return T_LEIA;
escreva		return T_ESCREVA;

se		return T_SE;
entao		return T_ENTAO;
senao		return T_SENAO;
fimse		return T_FIMSE;

enquanto	return T_ENQTO;
faca		return T_FACA;
fimenquanto	return T_FIMENQTO;

para        return T_PARA;
de          return T_DE;
ate         return T_ATE;
passo       return T_PASSO;
fimpara     return T_FIMPARA;

"+"		return T_MAIS;
"-"		return T_MENOS;
"*"		return T_VEZES;
div		return T_DIV;

">"		return T_MAIOR;
"<"		return T_MENOR;
"="		return T_IGUAL;

e		return T_E;
ou		return T_OU;
nao		return T_NAO;

"<-"	return T_ATRIB;
"("		return T_ABRE;
")"		return T_FECHA;
{identificador}"["{numero}"]"  { strcpy(atomo,yytext);   return T_VETOR;}

inteiro		return T_INTEIRO;
logico		return T_LOGICO;
V		return T_V;
F		return T_F;

{identificador} { strcpy (atomo, yytext); 
                  return T_IDENTIF; }
{numero}	{ strcpy (atomo, yytext); 
                  return T_NUMERO; }
{espaco}        /* nao faz nada */
{novalinha}     numLinha++;

"//".*          /* comentario de linha */

"/*"             BEGIN(comentario);
<comentario>"*/" BEGIN(INITIAL);
<comentario>.    /* nao faz nada */
<comentario>\n   numLinha++;

.		 ERRO ("ERRO LEXICO");

