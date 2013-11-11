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

   } TAB_tpTabuleiro ;


/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da casa de um tabuleiro
*
*
*  $ED Descrição do tipo
*     A casa do tabuleiro é o ponto de acesso para uma determinada casa.
*	  Esta armazena uma referência para PECA e o valor secundário.
*
***********************************************************************/

   typedef struct TAB_tagCasa {

        PEC_tppPeca pPeca ;
               /* Ponteiro para a peca que ocupa a casa */
		int vSec;
			   /* Valor secundário da casa */

   } TAB_tpCasa ;


/***** Protótipo das funções encapuladas no módulo *****/
   void ExcluirCasa( void * pValor );


/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TAB Criar tabuleiro
*
***********************************************************************/

   TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * ppTabuleiro ) {
	   TAB_tppTabuleiro pTab;
	   TAB_tpCasa *pCasa;
	   int i, j;

	   if(ppTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   pTab = (TAB_tpTabuleiro *)malloc(sizeof(TAB_tpTabuleiro));
	   if(pTab == NULL || MAT_CriarMatriz(&(pTab->pMatriz), 8, ExcluirCasa) != MAT_CondRetOK) {
		   return TAB_CondRetFaltouMemoria;
	   }

	   for( i = 0; i < 8; i++ ) {
		   for( j = 0; j < 8; j++ ) {

			   pCasa = (TAB_tpCasa *)malloc(sizeof(TAB_tpCasa));
			   if(pCasa==NULL) {
				   MAT_DestruirMatriz(pTab->pMatriz);
				   free(pTab);
				   return TAB_CondRetFaltouMemoria;
			   }

			   MAT_AtribuirValorCorrente(pTab->pMatriz, (void *)pCasa);

		   }
	   }

	   pTab->i = 'A';
	   pTab->j = 1;

	   *ppTabuleiro = pTab;

	   return TAB_CondRetOK;

   }


/***********************************************************************
*
*  $FC Função: TAB Destruir tabuleiro
*
***********************************************************************/

   TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro ) {

	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   MAT_DestruirMatriz( pTabuleiro->pMatriz );

	   free( pTabuleiro );

	   return TAB_CondRetOK;
	   
   }


/***********************************************************************
*
*  $FC Função: TAB Definir posição corrente.
*
***********************************************************************/

   TAB_tpCondRet TAB_DefinirCorrente( TAB_tppTabuleiro pTabuleiro, char i, int j )
   {
	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   if(  i > 'H' || i < 'A' || j > 8 || j < 1 || MAT_DefinirCorrente( pTabuleiro->pMatriz, (int) (i-'A'), j - 1) == MAT_CondRetPosicaoInvalida )
		   return TAB_CondRetPosicaoInvalida;

	   pTabuleiro->i = i;
	   pTabuleiro->j = j;

	   return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Obter posição corrente.
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterCorrente( TAB_tppTabuleiro pTabuleiro, char *i, int *j )
   {
	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   *i = pTabuleiro->i;
	   *j = pTabuleiro->j;

	   return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Atribuir valor
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca pPeca ) {
	   TAB_tpCasa *pCasa;

	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)&pCasa);

	   pCasa->pPeca = pPeca;

	   return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Obter valor corrente
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca ) {
	   TAB_tpCasa *pCasa;
	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)&pCasa);

	   *ppPeca = pCasa->pPeca;

	   return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Obter valor de casa
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorDeCasa( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca , char i, int j ) {
   		char oldI;
   		int oldJ;	   
	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

   		TAB_ObterCorrente(pTabuleiro, &oldI, &oldJ);
   		TAB_DefinirCorrente(pTabuleiro, i, j);
   		TAB_ObterValorCorrente(pTabuleiro, ppPeca);
   		TAB_DefinirCorrente(pTabuleiro, oldI, oldJ);

	   return TAB_CondRetOK;
   }

/***********************************************************************
*
*  $FC Função: TAB Atribuir valor secundário
*
***********************************************************************/

   TAB_tpCondRet TAB_AtribuirValorSecundario( TAB_tppTabuleiro pTabuleiro, int valorSec ) {
	   TAB_tpCasa *pCasa;

	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)&pCasa);

	   pCasa->vSec = valorSec;

	   return TAB_CondRetOK;
   }
	   


/***********************************************************************
*
*  $FC Função: TAB Obter valor secundário
*
***********************************************************************/

   TAB_tpCondRet TAB_ObterValorSecundario( TAB_tppTabuleiro pTabuleiro, int * pValorSec ) {
	   TAB_tpCasa *pCasa;
	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)&pCasa);

	   *pValorSec = pCasa->vSec;

	   return TAB_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: TAB Zerar valores secundários
*
***********************************************************************/

   TAB_tpCondRet TAB_ZerarValoresSecundarios( TAB_tppTabuleiro pTabuleiro ) {
	   TAB_tpCasa *pCasa;
	   int i, j;

	   if(pTabuleiro == NULL) {
		   return TAB_CondRetPonteiroNulo;
	   }

	   for( i = 0; i < 8; i++ ) {
		   for( j = 0; j < 8; j++ ) {
				MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)&pCasa);
				pCasa->vSec = 0;
		   }
	   }

	   return TAB_CondRetOK;
   }

/***** Código das funções encapuladas no módulo *****/

/***********************************************************************
*
*  $FC Função: TAB - Excluir casa
*
*  $ED Descrição da função
*  Função auxiliar para destruir casa
*
***********************************************************************/

   void ExcluirCasa( void * pValor )
   {
	   if(pValor != NULL) {
		   free( ( (TAB_tpCasa *)pValor )->pPeca);
		   free( pValor );
	   }
   }

/********** Fim do módulo de definição: Módulo tabuleiro **********/

