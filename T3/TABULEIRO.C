/***************************************************************************
*  $MCI Módulo de implementação: Módulo tabuleiro
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>

#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeça de um tabuleiro
*
*
*  $ED Descrição do tipo
*     A cabeça do tabuleiro é o ponto de acesso para um determinado tabuleiro.
*     Por intermédio da referência para uma matriz pode-se navegar
*     pelo tabuleiro.
*
***********************************************************************/

   typedef struct TAB_tagTabuleiro {

        MAT_tppMatriz pMatriz ;
               /* Ponteiro para a matriz utilizada */
		char i;
			   /* Coordenada vertical da posição corrente */
		int j;
			   /* Coordenada horizontal da posição corrente */
		void ( * ExcluirValor ) ( void * pValor ) ;

   } TAB_tpTabuleiro ;


////////////////////////////////////////////////////////////
/// Cru a partir daqui.
/////////////////////////////////////////////////////////


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
*     $P i - ponteiro que receberá a coord. horizontal
*		(valor entre 'A' e 'H').
*     $P j - coordenada que receberá a coord. vertical
*		(valor entre 1 e 8).
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
*     $P pValor  - ponteiro genérico para o valor a ser atribuído
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorCorrente( TAB_tppTabuleiro pTabuleiro, void * pValor ) ;


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

   TAB_tpCondRet TAB_ObterValorCorrente( TAB_tppTabuleiro pTabuleiro, void ** ppValor ) ;


/***********************************************************************
*
*  $FC Função: TAB Atribuir valor secundário
*
*  $ED Descrição da função
*     Atribui valor fornecido ao valor secundário da posição corrente.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P valorSec  - valor a ser atribuído
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorSecundario( TAB_tppTabuleiro pTabuleiro, int valorSec ) ;


/***********************************************************************
*
*  $FC Função: TAB Obter valor secundário
*
*  $ED Descrição da função
*     Obtem valor auxiliar da posição corrente.
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*     $P pValorSec - ponteiro para variável inteira que receberá o valor
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorSecundario( TAB_tppTabuleiro pTabuleiro, int * pValorSec ) ;


/***********************************************************************
*
*  $FC Função: TAB Zerar valores secundários
*
*  $ED Descrição da função
*     Atribui zero ao valor secundário de todas as posições do tabuleiro
*
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*
*  $FV Valor retornado
*     TAB_CondRetOK
*     TAB_CondRetPonteiroNulo
*
***********************************************************************/

   TAB_tpCondRet TAB_ZerarValoresSecundarios( TAB_tppTabuleiro pTabuleiro ) ;

#undef TABULEIRO_EXT

/********** Fim do módulo de definição: Módulo tabuleiro **********/

#else
#endif
