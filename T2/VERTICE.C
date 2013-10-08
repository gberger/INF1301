/***************************************************************************
*  $MCI Módulo de implementação: VER  Vértice de grafo contendo string
*
*  Arquivo gerado:              VERTICE.c
*  Letras identificadoras:      VER
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include   <string.h>
#include   <malloc.h>

#define VERTICE_OWN
#include "VERTICE.h"
#undef VERTICE_OWN

/***********************************************************************
*
*  $TC Tipo de dados: VER Elemento de vértice
*
*
***********************************************************************/

   typedef struct VER_tagVertice {
      char * conteudo;
   } VER_tpVertice ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: VER  &Criar vértice
*  ****/

   VER_tpCondRet VER_CriarVertice( VER_tppVertice * ppVertice )
   {
      if(ppVertice == NULL) {
         return VER_CondRetPonteiroNulo;
      }

      *ppVertice = (VER_tppVertice) malloc( sizeof(VER_tpVertice) );
      if(*ppVertice == NULL) {
         return VER_CondRetFaltouMemoria;
      }

      (*ppVertice)->conteudo = NULL;

      return VER_CondRetOK;

   } /* Fim função: VER  &Criar vértice */

/***************************************************************************
*
*  Função: VER  &Destruir vértice
*  ****/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice )
   {
	   VER_EsvaziarVertice( pVertice );

	   free( pVertice );

	   return VER_CondRetOK;

   } /* Fim função: VER  &Destruir vértice */

/***************************************************************************
*
*  Função: VER  &Esvaziar vértice
*  ****/

   VER_tpCondRet VER_EsvaziarVertice( VER_tppVertice pVertice )
   {
	   if(pVertice->conteudo != NULL) {
		   free(pVertice->conteudo);
		   pVertice->conteudo = NULL;
	   }

	   return VER_CondRetOK;

   } /* Fim função: VER  &Esvaziar vértice */

/***************************************************************************
*
*  Função: VER  &Atribuir valor
*  ****/

   VER_tpCondRet VER_AtribuirValor( VER_tppVertice pVertice, char * valor )
   {
	   pVertice->conteudo = malloc( strlen( valor) + 1 );
	   if( pVertice->conteudo == NULL )
	   {
		   return VER_CondRetFaltouMemoria;
	   }

	   strcpy( pVertice->conteudo, valor);

	   return VER_CondRetOK;

   } /* Fim função: VER  &Atribuir valor */

/***************************************************************************
*
*  Função: VER  &Obter valor
*  ****/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice, char ** pValor )
   {
	   if(pVertice->conteudo == NULL)
	   {
		   return VER_CondRetVerticeVazio;
	   }

      *pValor = pVertice->conteudo;

      return VER_CondRetOK;
      
   } /* Fim função: VER  &Obter valor */

/********** Fim do módulo de implementação: VER  Vértice de grafo contendo string **********/

