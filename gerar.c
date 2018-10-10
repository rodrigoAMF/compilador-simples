/***********************************************
* Função responsável por gerar código em C
* Paulo Muniz de Ávila. 
************************************************/


enum instrucao {cabecalho=1,declarar_inteiro=2,declarar_boolean=3,fechar_contexto=4,leitura=5,imprime=6,selecao=7, atribuicao=8, repeticao=9, para=10};
int identa = 0;
int i;
int ehVetor;
int tamanho;

void emit(int c,...) {
    char *id;
    char *expressao;
    int tipo;
     va_list argp;

   switch(c) {
	case cabecalho:
		printf("#include <stdio.h>\n");
		printf("#include <stdlib.h>\n");
		printf("#include <math.h>\n");
		printf("#include <stdbool.h>\n");
		printf("\nint main() {\n");
		break;

        case declarar_inteiro:
            printf("\n\tint ");
   	        va_start (argp, c);
  	        id = va_arg(argp, char *);
	        ehVetor = va_arg(argp, int); 
            tamanho = va_arg(argp, int); 
	        printf("\t%s", id);
            if(ehVetor){
                printf("[%d]", tamanho);
            }
            printf(";");
            va_end(argp);
		break;

        case declarar_boolean:
            printf("\n\tbool ");
            va_start (argp, c);
  	        id = va_arg(argp, char *);
            ehVetor = va_arg(argp, int); 
            tamanho = va_arg(argp, int); 
	        printf("\t%s", id);
            if(ehVetor){
                printf("[%d]", tamanho);
            }
            printf(";");
            va_end(argp);
		break;

        case fechar_contexto:
            printf("\n\treturn 0; \n}\n");
            break;

        case leitura:
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("scanf(");
   	        va_start (argp, c);
  	        id = va_arg(argp, char *); 
            printf("\"%cd\",&%s", '%',id);
            printf(");");
            va_end(argp);
		break;

 	  case imprime:
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("printf(");
   	        va_start (argp, c);
  	        id = va_arg(argp, char *); 
            tipo = va_arg(argp, int);
            if(tipo == 1) {
                printf("%s ? \"true\" : \"false\"", id);
            } else {
                printf("\"%cd\",%s", '%',id);
            }
            printf(");");
            va_end(argp);
		break;
      case selecao:
          va_start (argp, c);
          id = va_arg(argp, char *);
          tipo = va_arg(argp, int);
          if(tipo == 0){
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("if(");
            printf("%s) {", id);
            identa++;
          }else if(tipo == 1){
            identa--;
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("}else{");
            identa++;
          }else if(tipo == 2){
            identa--;
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("}");
          }
          va_end(argp);
          break;
      case atribuicao:
        va_start (argp, c);
        id = va_arg(argp, char *);
        expressao = va_arg(argp, char *);
        printf("\n\t");
        for(i = 0; i < identa; i++){
            printf("   ");
        }
        printf("%s = %s;", id, expressao);
        va_end(argp);
        break;
      case repeticao:
          va_start (argp, c);
          id = va_arg(argp, char *);
          tipo = va_arg(argp, int);
          if(tipo == 0){
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("while(");
            printf("%s) {", id);
            identa++;
          }else if(tipo == 1){
            identa--;
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("}");
          }
          va_end(argp);
          break;
      case para:
          va_start (argp, c);
          id = va_arg(argp, char *);
          int n1 = va_arg(argp, int);
          int n2 = va_arg(argp, int);
	  int incremento = va_arg(argp, int);
          tipo = va_arg(argp, int);
          if(tipo == 0){
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("for(int %s ", id);
          // atribuição
          }else if(tipo == 1){
              printf("= %d;", n1);
          // condição
          }else if(tipo == 2){
              if(n2 <= n1){
                  printf("%s > %d;",id, n2);
              }else if(n2 > n1){
                  printf("%s < %d;",id, n2);
              }
          // passo
          }else if(tipo == 3){
              if(n2 < n1){
                  printf("%s -= %d){", id, incremento);
              }else if(n2 > n1){
                  printf("%s += %d){", id, incremento);
              }else{
                  printf("){");
              }
              identa++;
          // fim for
          }else if(tipo == 4){
            identa--;
            printf("\n\t");
            for(i = 0; i < identa; i++){
                printf("   ");
            }
            printf("}");
          }
          va_end(argp);
          break;
   }
}


