#if ! defined( TABULEIRO_ )
#define TABULEIRO_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo tabuleiro de xadrez
*
*  Arquivo gerado:              TABULEIRO.H
*  Letras identificadoras:      TAB
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e manipular tabuleiros de xadrez.
*     Podem existir inúmeros tabuleiros em operação simultaneamente.
*     Os tabuleiros possuem uma cabeça encapsulando o seu estado.
*     Cada posição do tabuleiro possui um valor inteiro auxiliar de
*	  uso livre e pode armazenar um valor genérico.
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

#include "MATRIZ.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct TAB_tagTabuleiro * TAB_tppTabuleiro ;

/***********************************************************************
*
*  $TC Tipo de dados: TAB Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da matriz
*
***********************************************************************/

   typedef enum {

         TAB_CondRetOK ,
               /* Executou corretamente */

         TAB_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         TAB_CondRetDirecaoInvalida ,
               /* A direção que se quer mover é inválida */

         TAB_CondRetPosicaoInvalida ,
               /* A posição onde se quer ir é inválida */

         TAB_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } TAB_tpCondRet ;


/***********************************************************************
*
*  $FC Função: TAB Criar tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro genérico de xadrez
*     O ponteiro para o tabuleiro criado será fornecido no valor do ponteiro
*     de ponteiro para tabuleiro.
*
*  $EP Parâmetros
*     $P ppTabuleiro - ponteiro para o ponteiro de tabuleiro.
*     $P ExcluirValor - ponteiro para a função de destruição do valor.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetFaltouMemoria
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * ppTabuleiro, void ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: TAB Destruir tabuleiro
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça do tabuleiro, liberando o espaço ocupado.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_DestruirMatriz( TAB_tppTabuleiro pTabuleiro ) ;





////////////////////////////////////////////////////////////////////////////////////////
// Continuar definição a partir daqui. /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////





/***********************************************************************
*
*  $FC Função: TAB Andar com a célula corrente.
*
*  $ED Descrição da função
*     Move a célula corrente da matriz, de acordo com a direcao fornecida.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P direcao - direcao para a qual mover.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetDirecaoInvalida
*
***********************************************************************/

   TAB_tpCondRet TAB_AndarCorrente( TAB_tppMatriz pMatriz, TAB_tpDirecao direcao ) ;


/***********************************************************************
*
*  $FC Função: TAB Definir célula corrente.
*
*  $ED Descrição da função
*     Define a célula corrente da matriz através de suas coordenadas.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P i - coordenada horizontal.
*     $P j - coordenada vertical.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetPosicaoInvalida
*
***********************************************************************/

   TAB_tpCondRet TAB_DefinirCorrente( TAB_tppMatriz pMatriz, int i, int j ) ;


/***********************************************************************
*
*  $FC Função: TAB Atribuir valor
*
*  $ED Descrição da função
*     Atribui valor à célula corrente da matriz.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P pLista  - ponteiro para o valor a ser atribuído
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorCorrente( TAB_tppMatriz pMatriz, void * pValor ) ;


/***********************************************************************
*
*  $FC Função: TAB Obter valor corrente
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P ppValor - ponteiro para o ponteiro do valor a ser obtido
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorCorrente( TAB_tppMatriz pMatriz, void ** ppValor ) ;

#undef Matriz_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
