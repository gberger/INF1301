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
*     Cada posição do tabuleiro pode armazenar uma variável tipo referência
*	  para PECA e possui um valor inteiro secundário de uso livre (valor
*	  inicial é zero).
*
***************************************************************************/
 
#if defined( TABULEIRO_OWN )
   #define TABULEIRO_EXT
#else
   #define TABULEIRO_EXT extern
#endif

#include "MATRIZ.H"
#include "PECA.H"

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
*     Cria um tabuleiro de xadrez
*     O ponteiro para o tabuleiro criado será fornecido no valor do ponteiro
*     de ponteiro para tabuleiro. A posição corrente incial é 'A1'
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

   TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * ppTabuleiro ) ;


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

   TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro ) ;


/***********************************************************************
*
*  $FC Função: TAB Definir posição corrente.
*
*  $ED Descrição da função
*     Define a posição corrente do tabuleiro através de suas coordenadas.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P i - coordenada horizontal (valor entre 'A' e 'H').
*     $P j - coordenada vertical (valor entre 1 e 8).
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*     TAB_CondRetPosicaoInvalida
*
***********************************************************************/

   TAB_tpCondRet TAB_DefinirCorrente( TAB_tppTabuleiro pTabuleiro, char i, int j ) ;


/***********************************************************************
*
*  $FC Função: TAB Obter posição corrente.
*
*  $ED Descrição da função
*     Obtem as coordenadas da posição corrente do tabuleiro.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P i - ponteiro que receberá a coord. horizontal (valor entre 'A' e 'H').
*     $P j - coordenada que receberá a coord. vertical (valor entre 1 e 8).
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterCorrente( TAB_tppTabuleiro pTabuleiro, char *i, int *j ) ;


/***********************************************************************
*
*  $FC Função: TAB Atribuir valor
*
*  $ED Descrição da função
*     Atribui valor à posição corrente do tabuleiro.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P pValor  - ponteiro para o valor a ser atribuído
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca pPeca ) ;


/***********************************************************************
*
*  $FC Função: TAB Obter valor corrente
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P ppValor - ponteiro para o ponteiro do valor a ser obtido
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca ) ;


/***********************************************************************
*
*  $FC Função: TAB Obter valor de casa
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P ppValor - ponteiro para o ponteiro do valor a ser obtido
*     $P i - coordenada horizontal (valor entre 'A' e 'H').
*     $P j - coordenada vertical (valor entre 1 e 8).
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorDeCasa( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca , char i, int j ) ;


/***********************************************************************
*
*  $FC Função: TAB Mover valor de uma casa a outra
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P iOrig - coordenada horizontal da origem (valor entre 'A' e 'H').
*     $P jOrig - coordenada vertical da origem (valor entre 1 e 8).
*     $P iDest - coordenada horizontal do destino (valor entre 'A' e 'H').
*     $P jDest - coordenada vertical do destino (valor entre 1 e 8).
*     $P pPecaComida - ponteiro para ponteiro de peça onde será posto a peça eventualmente comida.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosicaoInvalida
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_MoverValor( TAB_tppTabuleiro pTabuleiro, char iOrig, int jOrig, char iDest, int jDest ) ;


/***********************************************************************
*
*  $FC Função: TAB Mover valor de uma casa a outra
*
*  $ED Descrição da função
*     Desfaz a última mudança feita por TAB_MoverValor.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P iOrig - coordenada horizontal da origem (valor entre 'A' e 'H').
*     $P jOrig - coordenada vertical da origem (valor entre 1 e 8).
*     $P iDest - coordenada horizontal do destino (valor entre 'A' e 'H').
*     $P jDest - coordenada vertical do destino (valor entre 1 e 8).
*     $P pPecaComida - ponteiro de peça que deve ser recuperada.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosicaoInvalida
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_DesMoverValor( TAB_tppTabuleiro pTabuleiro ) ;

/***********************************************************************
*
*  $FC Função: TAB - Checar posição válida
*
*  $ED Descrição da função
*     Função auxiliar para checar validez de uma posição
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPosicaoInvalida
*
***********************************************************************/

   TAB_tpCondRet ChecarPosicaoValida( char i, int j ) ;


#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo tabuleiro de xadrez **********/

#else
#endif
