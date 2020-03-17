/* Data de submissao:
 * Nome: Theo Soares de Camargo
 * RA: 206191
 */

#include <stdio.h>
const int tam_buffer=100;

char pilha[100];
int n_pilha = 0; 			/* Indice da pilha */

typedef enum {

    FORA,	       	/* O cursor esta fora de uma palavra */
    DENTRO,		/* O cursor esta dentro de uma palavra */
    T_PALAVRA,		/* O cursor esta imediatamente apos uma palavra */
    U_PALAVRA,		/* O cursor esta imediatamente apos a ultima palavra */
    FIM  		/* O cursor chegou ao final do buffer */

} status;

/******************************************************************************/
/* Prototipos                                                                 */
/******************************************************************************/

void push(char c);		/* Coloca um dado na pilha */
char pop(void);		/* Tira um dado da pilha */
status atualiza_estado(char *s, int i); /* Atualiza o estado */

/******************************************************************************/
/* Programa Principal                                                         */
/******************************************************************************/

int main() {
  char buffer[tam_buffer];
  fgets(buffer, tam_buffer, stdin);

  status estado;		/* Armazena o estado do cursor */

  char buffer_aux[tam_buffer];	/* Armazena palavras com as letras trocadas */

  for(int i = 0; i < tam_buffer; i++) {
      buffer_aux[i] = '\0';
  }


  
  int k;			/* Indica a posicao livre no buffer aux */
  k = 0;
  
  for(int i=0; buffer[i] != '\0'; i++) { /* Para cada posicao do buffer */

      estado = atualiza_estado(buffer, i); /* Atualiza o estado */

      if(estado == FORA){
	  ;			/* Nao faz nada */

      } else if(estado == DENTRO) {

	  push(buffer[i]);	/* Coloca a letra na pilha */

      } else if(estado == T_PALAVRA) {

	  while(n_pilha > 0) {	/* Enquanto a pilha nao esta vazia */

	      buffer_aux[k] = pop(); /* Coloca a letra no buffer aux */
	      k++;		     /* Incrementa a posicao livre */
	  }

	  buffer_aux[k] = ' ';	/* Espaco entre palavras */
	  k++;			/* Incrementa a posicao livre */

      } else if(estado == U_PALAVRA) {

      	  while(n_pilha > 0) {	/* Enquanto a pilha nao esta vazia */

	      buffer_aux[k] = pop(); /* Coloca a letra no buffer aux */
	      k++;		     /* Incrementa a posicao livre */
	  }

	  buffer_aux[k] = '\n';	/* Ultimo caractere do buffer */
	  k++;			/* Incrementa a posicao livre */

      }

  }

  printf("%s", buffer_aux);
  
  return 0;
}


/******************************************************************************/
/* Funcoes                                                                    */
/******************************************************************************/

/* Uma pilha global atende os requerimentos do projeto */

void push(char c) {		/* Coloca um dado na pilha */

    if (n_pilha < tam_buffer)	/* Se a pilha nao estiver cheia */
    pilha[n_pilha] = c;
    n_pilha++;			/* Aponta para a proxima posicao livre */

}

char pop(void) {		/* Tira um dado da pilha */

    char c;

    if ( n_pilha > 0) {		/* Se a pilha nao estiver vazia */
	n_pilha--;
	c = pilha[n_pilha];
	return(c);
    }
}

status atualiza_estado(char *s, int i) {
    /* Recebe uma string 's' e um cursor 'i' e atualiza o estado */

    status estado;

    /* Caso 0; i = 0 */
    if (i == 0) {

	if( s[i] == ' ')	/* Se for um ' ' o cursor esta fora da palavra*/
	    estado = FORA;

	else if( s[i] == '\n')	/* Se for '\n' o cursor esta no fim do buffer */
	    estado = FIM;

	else
	    estado = DENTRO;	/* Senao o cursor esta dentro de uma palavra */

	/* Senao esta nos demais casos i > 0*/
    } else {

	if (s[i-1] == ' ') {	/* Se o caractere anterior for um ' ' */

	    if(s[i] == ' ')	/* E o caractere atual for ' ' */
		estado = FORA;

	    else if(s[i] == '\n') /* E o caractere atual for '\n' */
		estado = FIM;

	    else		/* Senao o cursor esta dentro de uma palavra */
		estado = DENTRO;

	} else {		/* Senao o caractere anterior eh uma letra */

	    if(s[i] == ' ')     /* E o caractere atual eh um ' ' */
		estado = T_PALAVRA;

	    else if(s[i] == '\n') /* E o caractere atual eh um '\n' */
		estado = U_PALAVRA;

	    else		/* Senao o cursor esta dentro de uma palavra */
		estado = DENTRO;

	}

    }

    return(estado);
}
