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

   typedef tpVerticeGrafo * tppVerticeGrafo;

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
	   tppVerticeGrafo pVerticeCorrente;
   } GRA_tpGrafo ;



/***** Protótipos das funções encapuladas no módulo *****/

   // Dada uma lista e um valor, move o corrente para o valor e exclui o corrente
   static void LIS_ExcluirValor(LIS_tppLista pLista , void* pValor){
	    LIS_tpCondRet cond = LIS_ProcurarValor( pLista , pValor ) ;

		if (cond != LIS_CondRetOK){
			return;
		}

		LIS_ExcluirElemento(pLista);
   }

   // Dada uma lista e um valor, insere-o no final
    static GRA_tpCondRet LIS_InserirFinal(LIS_tppLista pLista , void* pValor){
	   LIS_tpCondRet cond;

	   LIS_IrFinalLista(pLista);
	   cond = LIS_InserirElementoApos(pLista, pValor);

	   if (cond != LIS_CondRetOK){
		   return GRA_CondRetFaltouMemoria;
	   }
	   return GRA_CondRetOK;
   }

   // Auxiliar para function pointer
   static void DestruirVertice (void * pVertice){
	   VER_DestruirVertice((VER_tppVertice)pVertice);
   }

   // Encapsula verificações de memória
   static tppVerticeGrafo CriarVerticeGrafo (void){
	   tppVerticeGrafo pVertice = NULL;
	   
	   pVertice = (tppVerticeGrafo) malloc(sizeof(tpVerticeGrafo));
	   if (pVertice == NULL){
		   return NULL;
	   }

	   pVertice->pValor = NULL;
	   
	   pVertice->pListaAnt = LIS_CriarLista( DestruirVertice ) ;
	   if (pVertice->pListaAnt == NULL){
		   free(pVertice);
		   return NULL;
	   }

	   pVertice->pListaSuc = LIS_CriarLista( DestruirVertice ) ;
	   if (pVertice->pListaSuc == NULL){
		   LIS_DestruirLista(pVertice->pListaAnt);
		   free(pVertice);
		   return NULL;
	   }

	   return pVertice;
   }

   // Adiciona o vértice do grafo à lista de origens
   static GRA_tpCondRet AdicionarOrigem ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   return LIS_InserirFinal(pGrafo->pListaOrigens, pVertice);
   }

   // Remove o vértice do grafo da lista de origens
   static GRA_tpCondRet RemoverOrigem ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   //ToDo
	   return GRA_CondRetOK;
   };
   
   // Adiciona o vértice do grafo à lista de vértices
   static GRA_tpCondRet AdicionarVertice ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   return LIS_InserirFinal(pGrafo->pListaVertices, pVertice);
   }
   
   // Remove o vértice do grafo da lista de vértices
   static GRA_tpCondRet RemoverVertice ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   //ToDo
	   return GRA_CondRetOK;
   };

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
	   // excluir todos os vértices
	   // -> excluir listas dos vértices
	   // esvaziar listas de origens e vértices
	   // corrente = NULL

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice * ppValor ) {
	   VER_tpCondRet cond; 

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetVerticeInvalido;
	   }
	   
	   cond = VER_ObterValor( pGrafo->pVerticeCorrente->pValor, (void**) ppValor);

	   if (cond != VER_CondRetOK){
		   return GRA_CondRetErroVertice;
	   }
	   	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Alterar valor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice pValor ) {
	   VER_tpCondRet cond; 

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetVerticeInvalido;
	   }

	   cond = VER_AtribuirValor( pGrafo->pVerticeCorrente->pValor, (void*) pValor );
	   
	   if (cond != VER_CondRetOK){
		   return GRA_CondRetErroVertice;
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

	   //ToDo
	   // v = achar na lista de vertices o que tem pValor == pVertice
	   // se existir, corrente = v
	   
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
	   
	   //ToDo
	   // v = achar na lista de sucessores o que tem pValor == pVertice
	   // se existir, corrente = v

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) {
	   tppVerticeGrafo vertice;
	   
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   vertice = CriarVerticeGrafo();
	   vertice->pValor = pVertice;

	   AdicionarOrigem(pGrafo, vertice);
	   AdicionarVertice(pGrafo, vertice);
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Excluir vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVerticeCorrente( GRA_tppGrafo pGrafo ) {
	   tppVerticeGrafo vertice;
	   LIS_tppLista sucessores;

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   vertice = pGrafo->pVerticeCorrente;
	   sucessores = vertice->pListaSuc;

	   LIS_IrInicioLista(sucessores);
	   
	   //ToDo
	   // enquanto conseguir andar em sucessores, obter valor (vértice de grafo), 
	   // obter lista de antecessores, usar LIS_ExcluirValor

	   VER_DestruirVertice(vertice->pValor);
	   LIS_DestruirLista(vertice->pListaAnt);
	   LIS_DestruirLista(vertice->pListaSuc);
	   
	   RemoverVertice(pGrafo, vertice);
	   RemoverOrigem(pGrafo, vertice);

	   free(vertice);
	   
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

	   //ToDo
	   // dest = achar na lista de vertices o que tem pValor == pVertice
	   // adicionar aos sucessores do corrente o dest
	   // adicionar aos antecessores do dest o corrente
	   
	   // balancear origens (PESQUISAR ALGORITMO DEPOIS)
	   
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

	   //ToDo
	   // dest = achar na lista de vertices o que tem pValor == pVertice
	   // remover dos sucessores do corrente o dest
	   // remover dos antecessores do dest o corrente
	   
	   // balancear origens (PESQUISAR ALGORITMO DEPOIS)
	   
	   return GRA_CondRetOK;
   }


/*****  Código das funções encapsuladas no módulo  *****/



/********** Fim do módulo de implementação: Módulo grafo dirigido **********/
