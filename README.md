# Compilador para linguagem *Simples*
Compilador desenvolvido na disciplina **Compiladores** do curso de [Engenharia de Computação](https://pcs.ifsuldeminas.edu.br/index.php?option=com_content&view=article&id=639&Itemid=267) do [IFSULDEMINAS - Poços de Caldas](https://pcs.ifsuldeminas.edu.br/)

O compilador é capaz de converter códigos da linguagem `simples` para a linguagem `C`. Com algumas modificações é possível fazer ele converter diretamente para Assembly, mas, por se tratar de um compilador simples, não há necessidade para tal. 

# Pré-Requisitos

- Ubuntu 10.4 ou superior (Recomendado 18.04)
- [Flex e Bison](https://ccm.net/faq/30635-how-to-install-flex-and-bison-under-ubuntu)

# Instalação

Basta clonar/baixar os arquivos do repositório.

# Utilização

Para compilar um arquivo .simples execute os seguintes comandos no terminal:
```
makefile
simples < arquivo.simples > arquivo.c
```

# Exemplo de código

O seguinte código na linguagem Simples:
```
programa repete
  inteiro a
  inteiro b
  inteiro c
  inteiro d
 
inicio
   leia a
   enquanto a > 0 faca
       escreva a
   	   a <- a + 1
   fimenquanto
fimprograma
```

Gera na linguagem C:

```
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int main() {
  int 	a;
  int 	b;
  int 	c;
  int 	d;
  scanf("%d",&a);
  while(a > 0){
      printf("%d",a);
      a = a + 1;
  }
	
  return 0; 
}
```

# Comandos reconhecidos pelo compilador

* Declaração de variáveis (Booleanas e inteiras)
```
logico exemplo
inteiro exemplo
```

* Declaração de vetores (Booleanas e inteiros)
```
logico exemplo[5]
inteiro exemplo[5]
```

* Declaração de funções com ou sem retorno 
```
funcao inteiro exemplo(inteiro a inteiro b) entao 
    <lista de comandos>
    retorne a
```
* Operadores lógicos  
`e`, `ou` , `nao`


* Estruturas de decisão if/else
```
se nao a[0] = F e b[0]
    entao
        escreva a[0]
    senao
        escreva b[2]
fimse
```
* Estruturas de repetição for/while\

**for**
```
para a de 10 ate 0 passo 7 faca
   escreva a
   a <- a * 1
fimpara
```
**while**
```
enquanto a > 0 faca
   escreva a
   a <- a * 1
fimenquanto
```

* Leitura e escrita
```
leia valor
escreva valor
```

* Escrita e expressões
```
a[2] <- 2 + 2
```

# Contribuições
Contribuições de todos os tipos são bem vindas neste projeto! Fique a vontade para enviar um `Pull request` ou sugerir algo através da aba `Issues`.

# Equipe

* **Rodrigo Araújo Marinho Franco** - *Desenvolvimento do compilador* - [rodrigoAMF](https://github.com/rodrigoAMF)
* **Luziane de Lourdes Freitas** - *Desenvolvimento do compilador* - [LuzianeFreitas](https://github.com/LuzianeFreitas)

## Licença

Este projeto está licenciado sob a licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.
