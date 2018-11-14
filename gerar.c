/***********************************************
* Função responsável por gerar código em C
* Paulo Muniz de Ávila. 
************************************************/


enum instrucao {cabecalho=1,declarar_inteiro=2,declarar_boolean=3,fechar_contexto=4,leitura=5,imprime=6,selecao=7, atribuicao=8, repeticao=9, para=10, funcao=11, chamada_funcao = 12};
int identa = 0;
int i;
int ehVetor;
int tamanho;
int ehParametro;
int qtdParametro = 0;

void emit(int c,...) {
    char *id;
    char *expressao;
    int tipo;
    int tipo_parametro;
     va_list argp;

   switch(c) {
	case cabecalho:
        va_start (argp, c);
        tipo = va_arg(argp, int);
        if(tipo == 0){
            printf("#include <stdio.h>\n");
            printf("#include <stdlib.h>\n");
            printf("#include <math.h>\n");
            printf("#include <stdbool.h>\n");
        }else if(tipo == 1){
            printf("\nint main() {\n");
        }
		break;

        case declarar_inteiro:
            if(ehParametro){
                if(qtdParametro >= 1){
                    printf(", ");
                }
                printf("int ");
            }else{
                printf("\tint ");
            }
   	        va_start (argp, c);
  	        id = va_arg(argp, char *);
            tamanho = va_arg(argp, int); 
	        printf("%s", id);
            if(tamanho != 0){
                printf("[%d]", tamanho);
            }
            if(ehParametro == 0){
                printf(";\n");
            }else{
                ++qtdParametro;
            }
            va_end(argp);
		break;

        case declarar_boolean:
            if(ehParametro){
                if(qtdParametro >= 1){
                    printf(", ");
                }
                printf("bool ");
            }else{
                printf("\tbool ");
            }
            va_start (argp, c);
  	        id = va_arg(argp, char *);
            tamanho = va_arg(argp, int); 
	        printf("%s", id);
            if(tamanho != 0){
                printf("[%d]", tamanho);
            }
            if(ehParametro == 0){
                printf(";\n");
            }else{
                ++qtdParametro;
            }
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
            tipo = va_arg(argp, int);
            if(tipo == 1) {
                printf("\"%cd\",&%s", '%',id);
            } else {
                printf("\"%cd\",&%s", '%',id);
            }
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
            } else if(tipo == 0) {
                printf("\"%cd\",%s", '%',id);
            } else if(tipo == 2){
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
      case funcao:
          va_start (argp, c);
          id = va_arg(argp, char *);
          tipo_parametro = va_arg(argp, int);
          tipo = va_arg(argp, int);
          switch(tipo){
              case 0:
                  if(tipo_parametro){
                      printf("\n\nbool %s (", id);
                  }else{
                      printf("\n\nint %s (", id);
                  }
                  
                  ehParametro = 1;
                  break;
              case 1:
                  printf("){\n");
                  ehParametro = 0;
                  break;
              case 2:
                  printf("\n\treturn %s;", id);
                  break;
              case 3:
                  printf("\n}\n");
                  break;
          }
          break;
      case chamada_funcao:
          va_start (argp, c);
          id = va_arg(argp, char *);
          tipo = va_arg(argp, int);
          switch(tipo){
              case 0:
                  printf("\n\t%s(", id);
                  break;
              case 1:
                  printf(");");
                  break;
              case 2:
                  printf(", %s", id);
                  break;
              case 3:
                  printf("%s", id);
                  break;
          }
          break;
                  
   }
}


