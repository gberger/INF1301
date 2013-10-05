/***************************************************************************
*  $MCI Módulo de implementação: Módulo grafo dirigido
*
*  Arquivo gerado:              GRAFO.C
*  Letras identificadoras:      GRA
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da célula da grafo
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct tagVerticeGrafo {
	   LIS_tppLista pListaAnt;
	   LIS_tppLista pListaSuc;
	   VER_tppVertice pValor;
   } tpVerticeGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de uma grafo
*
*
*  $ED Descrição do tipo
*     A cabeça da grafo é o ponto de acesso para uma determinada grafo.
*     Por intermédio da referência para a célula corrente pode-se navegar
*     pela grafo.
*
***********************************************************************/

   typedef struct GRA_tagGrafo {
	   LIS_tppLista pListaOrigens;
	   LIS_tppLista pListaVertices;
	   tpVerticeGrafo * pVerticeCorrente;
   } GRA_tpGrafo ;



/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirVertice (void * pVertice){
	   VER_DestruirVertice((VER_tppVertice)pVertice);
   }

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
***********************************************************************/

   GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo * ppGrafo ) {
	   GRA_tppGrafo pGrafo = NULL;
	   
	   pGrafo = (GRA_tppGrafo) malloc(sizeof(GRA_tpGrafo));
	   if (pGrafo == NULL){
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->pVerticeCorrente = NULL;
	   
	   pGrafo->pListaOrigens = LIS_CriarLista( DestruirVertice ) ;
	   if (pGrafo->pListaOrigens == NULL){
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->pListaOrigens = LIS_CriarLista( DestruirVertice ) ;
	   if (pGrafo->pListaOrigens == NULL){
		   LIS_DestruirLista(pGrafo->pListaOrigens);
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   *ppGrafo = pGrafo;

	   return GRA_CondRetOK;
   };


/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
***********************************************************************/

   GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   GRA_EsvaziarGrafo(pGrafo);
	   free(pGrafo);

	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Esvaziar
*
***********************************************************************/

   GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo pGrafo ) {

	   //ToDo

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice * ppValor ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Alterar valor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice * ppVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_IrParaVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_AndarParaVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Excluir vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVerticeCorrente( GRA_tppGrafo pGrafo ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }
   

/***********************************************************************
*
*  $FC Função: GRA Excluir aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
	   
	   return GRA_CondRetOK;
   }


/*****  Código das funções encapsuladas no módulo  *****/



/********** Fim do módulo de implementação: Módulo grafo dirigido **********/
