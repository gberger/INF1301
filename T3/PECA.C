/***************************************************************************
*  $MCI Módulo de implementação: Módulo peça
*
*  Arquivo gerado:              PECA.C
*  Letras identificadoras:      PEC
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>

#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

#include "CLASSE_PECA.H"

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor peça
*
*  $ED Descrição do tipo
*     Descreve a organização da peça
*
***********************************************************************/

  typedef struct PEC_tagPeca {
	   CPC_tppClassePeca pClassePeca;
	   PEC_tpJogador jogador;
	} PEC_tpPeca;

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*  $FC Função: PEC Criar peça
***********************************************************************/

    PEC_tpCondRet PEC_CriarPeca( PEC_tppPeca * ppPeca , CPC_tppClassePeca pClassePeca , PEC_tpJogador jogador ) {
      PEC_tpPeca * pPeca;

      if(pClassePeca == NULL){
        return PEC_CondRetPonteiroNulo;
      }

      pPeca = (PEC_tpPeca*)malloc(sizeof(PEC_tpPeca));

      if (ppPeca = NULL) {
        return PEC_CondRetFaltouMemoria; 
      }

      pPeca->pClassePeca = pClassePeca;
      pPeca->jogador = jogador;

      *ppPeca = pPeca;
     	
      return PEC_CondRetOk;
    }



/***********************************************************************
*  $FC Função: PEC Destruir peça
***********************************************************************/

   PEC_tpCondRet PEC_DestruirPeca( PEC_tppPeca pPeca ) {
      if(pPeca == NULL){
        return PEC_CondRetPonteiroNulo;
      }

      free(pPeca);

      return PEC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: PEC Obter classe da peça
***********************************************************************/

   PEC_tpCondRet PEC_ObterClassePeca( PEC_tppPeca pPeca , CPC_tppClassePeca * ppClassePeca ) {
      if(pPeca == NULL){
        return PEC_CondRetPonteiroNulo;
      }

      *ppClassePeca = pPeca->pClassePeca;

      return PEC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: PEC Obter jogador de peça
***********************************************************************/

   PEC_tpCondRet PEC_ObterJogador( PEC_tppPeca pPeca , PEC_tpJogador * pJogador ) {
      if(pPeca == NULL){
        return PEC_CondRetPonteiroNulo;
      }

      *pJogador = pPeca->jogador;

      return PEC_CondRetOk;
   }


/********** Fim do módulo de implementação: Módulo grafo dirigido **********/
