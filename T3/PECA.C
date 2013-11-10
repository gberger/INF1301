/***************************************************************************
*  $MCI Módulo de implementação: Módulo peca
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
#include <string.h>

#define PECA_OWN
#include "PECA.H"
#undef PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da célula do grafo
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct PEC_tagPeca {
	   CPC_tppClassePeca pClassePeca;
	   PEC_tpJogador jogador;
	} PEC_tpPeca;

   typedef PEC_tpPeca * PEC_tppPeca;


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
***********************************************************************/

     PEC_tpCondRet PEC_CriarPeca( PEC_tppPeca * ppPeca , CPC_tppClassePeca pClassePeca , PEC_tpJogador jogador ) {

     	ppPeca = malloc(sizeof(PEC_tpPeca));

     	if (ppPeca = NULL) {
     		return PEC_CondRetFaltouMemoria; 
     	}

     	

     }


/********** Fim do módulo de implementação: Módulo grafo dirigido **********/
