/***********************************************
* Função responsável por gerar código em C
* Paulo Muniz de Ávila. 
************************************************/


enum instrucao {cabecalho=1,declarar_inteiro=2,declarar_boolean=3,fechar_contexto=4,leitura=5,imprime=6};



void emit(int c,...) {
    char *id;
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
	        printf("\t%s", id);
                printf(";");
                va_end(argp);
		break;

        case declarar_boolean:
            printf("\n\tbool ");
            va_start (argp, c);
  	        id = va_arg(argp, char *); 
	        printf("\t%s", id);
            printf(";");
            va_end(argp);
		break;

	  case fechar_contexto:
            printf("\n\treturn 0; \n}\n");
            break;

          case leitura:
            printf("\n\tscanf(");
   	        va_start (argp, c);
  	        id = va_arg(argp, char *); 
            printf("\"%cd\",&%s", '%',id);
            printf(");");
            va_end(argp);
		break;

 	  case imprime:
            printf("\n\tprintf(");
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

   }
}


