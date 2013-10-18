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
#include <string.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da célula do grafo
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct tagVerticeGrafo {
	   LIS_tppLista pListaAnt;
	   LIS_tppLista pListaSuc;
	   char id;
	   void * pValor;
   } tpVerticeGrafo ;

   typedef tpVerticeGrafo * tppVerticeGrafo;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da cabeça de um grafo
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
	   void ( * ExcluirValor ) ( void * pValor ) ;
   } GRA_tpGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da aresta de um grafo
*
*
*  $ED Descrição do tipo
*     A aresta do grafo é referenciada no valor do elemento da lista
*     de sucessores de um vértice.
*
***********************************************************************/

   typedef struct GRA_tagAresta {
	   char idAresta[10];
	   tppVerticeGrafo pVerticeApontado;
   } GRA_tpAresta ;



/***** Protótipos das funções encapuladas no módulo *****/

   // Dada uma lista e um valor, insere-o no final
    static GRA_tpCondRet InserirFinalLista(LIS_tppLista pLista , void* pValor){
	   LIS_tpCondRet cond;

	   LIS_IrFinalLista(pLista);
	   cond = LIS_InserirElementoApos(pLista, pValor);

	   if (cond != LIS_CondRetOK){
		   return GRA_CondRetFaltouMemoria;
	   }
	   return GRA_CondRetOK;
   }

   // Auxiliar para function pointer
   static void DestruirConteudoListaDeVertice (void * pVertice) {
	   
   }

   //
   static void DestruirConteudoListaDeAresta (void * pAresta) {
	   free(pAresta);
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
	   return InserirFinalLista(pGrafo->pListaOrigens, pVertice);
   }

   // Remove o vértice do grafo da lista de origens
   static GRA_tpCondRet RemoverOrigem ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   //ToDo
	   return GRA_CondRetOK;
   };
   
   // Adiciona o vértice do grafo à lista de vértices
   static GRA_tpCondRet AdicionarVertice ( GRA_tppGrafo pGrafo, tppVerticeGrafo pVertice ){
	   return InserirFinalLista(pGrafo->pListaVertices, pVertice);
   }

   static tpVerticeGrafo * PesquisaVertice( LIS_tppLista pLista, char idVertice ) {
	   tpVerticeGrafo * pVerticeGrafo;
	   LIS_IrInicioLista( pLista );

	   do {
		   pVerticeGrafo = (tpVerticeGrafo *) LIS_ObterValor( pLista );
		   if( pVerticeGrafo != NULL && pVerticeGrafo->id == idVertice )
			   return pVerticeGrafo;

	   } while ( LIS_AvancarElementoCorrente( pLista, 1 ) != LIS_CondRetFimLista );

	   return NULL;
   }

   static tpVerticeGrafo * PesquisaVerticeNaListaDeAresta( LIS_tppLista pLista, char idVertice ) {
	   GRA_tpAresta * pAresta;
	   LIS_IrInicioLista( pLista );

	   do {
		   pAresta = (GRA_tpAresta *) LIS_ObterValor( pLista );
		   if( pAresta != NULL && pAresta->pVerticeApontado->id == idVertice )
			   return pAresta->pVerticeApontado;

	   } while ( LIS_AvancarElementoCorrente( pLista, 1 ) != LIS_CondRetFimLista );

	   return NULL;
   }

   // Remove o vértice do grafo da lista de vértices
   static void RemoverVertice ( tppVerticeGrafo pVertice ){
	   tpVerticeGrafo * pVerticeSuc;
	   GRA_tpAresta * pAresta;

	   //Remover arestas sucessoras
	   LIS_IrInicioLista( pVertice->pListaSuc );
	   
	   do {
		   pAresta = (GRA_tpAresta *) LIS_ObterValor( pVertice->pListaSuc );
		   if( pAresta != NULL ) {
			   LIS_ProcurarValor( pAresta->pVerticeApontado->pListaAnt, pVertice );
			   LIS_ExcluirElemento( pAresta->pVerticeApontado->pListaAnt );
		   }

	   } while ( LIS_AvancarElementoCorrente( pVertice->pListaSuc, 1 ) != LIS_CondRetFimLista );

	   //Remover arestas antecessoras
	   LIS_IrInicioLista( pVertice->pListaAnt );
	   
	   do {
		   pVerticeSuc = (tpVerticeGrafo *) LIS_ObterValor( pVertice->pListaAnt );
		   if( pVerticeSuc != NULL ) {
			   PesquisaVerticeNaListaDeAresta( pVerticeSuc->pListaSuc, pVertice->id );
			   LIS_ExcluirElemento( pVerticeSuc->pListaSuc );
		   }

	   } while ( LIS_AvancarElementoCorrente( pVerticeSuc->pListaSuc, 1 ) != LIS_CondRetFimLista );

   }

   static GRA_tpCondRet AdicionarAresta( GRA_tppGrafo pGrafo, tppVerticeGrafo pVerticeOrigem, tppVerticeGrafo pVerticeDestino, char * idAresta) {
	   LIS_tpCondRet CondRetLis;
	   GRA_tpAresta * pAresta;
	   pAresta = (GRA_tpAresta *)malloc(sizeof(GRA_tpAresta));
	   if(pAresta == NULL) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   strcpy(pAresta->idAresta, idAresta);
	   pAresta->pVerticeApontado = pVerticeDestino;

	   LIS_IrFinalLista(pVerticeOrigem->pListaSuc);
	   CondRetLis = LIS_InserirElementoApos(pVerticeOrigem->pListaSuc, (void *) pAresta);
	   if(CondRetLis == LIS_CondRetFaltouMemoria) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   LIS_IrFinalLista(pVerticeDestino->pListaAnt);
	   CondRetLis = LIS_InserirElementoApos(pVerticeDestino->pListaAnt, (void *) pVerticeOrigem);
	   if(CondRetLis == LIS_CondRetFaltouMemoria) {
		   return GRA_CondRetFaltouMemoria;
	   }
   }

/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
***********************************************************************/

   GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo * ppGrafo, void ( * ExcluirValor ) ( void * pDado ) ) {
	   GRA_tppGrafo pGrafo = NULL;
	   
	   pGrafo = (GRA_tppGrafo) malloc(sizeof(GRA_tpGrafo));
	   if (pGrafo == NULL){
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->pVerticeCorrente = NULL;
	   
	   pGrafo->pListaOrigens = LIS_CriarLista( DestruirConteudoListaDeVertice ) ;
	   if (pGrafo->pListaOrigens == NULL){
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->pListaVertices = LIS_CriarLista( DestruirConteudoListaDeVertice ) ;
	   if (pGrafo->pListaVertices == NULL){
		   LIS_DestruirLista(pGrafo->pListaOrigens);
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->ExcluirValor = ExcluirValor;

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
	   LIS_DestruirLista(pGrafo->pListaOrigens);
	   LIS_DestruirLista(pGrafo->pListaVertices);
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
	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   while (LIS_ObterValor( pGrafo->pListaVertices ) ) {
	   	RemoverVertice( (VER_tppVertice) LIS_ObterValor( pGrafo->pListaVertices ) );
	   	LIS_AvancarElementoCorrente(pGrafo->pListaVertices);
	   }
	   LIS_EsvaziarLista( pGrafo->pListaVertices );
	   LIS_EsvaziarLista( pGrafo->pListaOrigens );
	   pGrafo->pVerticeCorrente = NULL;

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
***********************************************************************/

	GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, void ** ppValor ) {

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	   
	   *ppValor = pGrafo->pVerticeCorrente->pValor;
	   	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Alterar valor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo, void * pValor ) {

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }

	   pGrafo->pVerticeCorrente->pValor = pValor;

	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_IrParaVertice( GRA_tppGrafo pGrafo, char idVertice ) {
	   tppVerticeGrafo resultado;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
		
	   resultado = PesquisaVertice( pGrafo->pListaVertices, idVertice );
	   if(resultado == NULL) {
		   return GRA_CondRetVerticeInvalido;
	   }

	   pGrafo->pVerticeCorrente = resultado;
	   
	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Andar para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_AndarParaVertice( GRA_tppGrafo pGrafo, char idVertice ) {
	   tppVerticeGrafo resultado;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   if (pGrafo->pVerticeCorrente == NULL){
		   return GRA_CondRetGrafoVazio;
	   }
	   
	   resultado = PesquisaVertice( pGrafo->pVerticeCorrente->pListaSuc, idVertice );
	   if(resultado == NULL) {
		   return GRA_CondRetVerticeInvalido;
	   }

	   pGrafo->pVerticeCorrente = resultado;

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pVertice, char idVertice ) {
	   tppVerticeGrafo vertice;
	   
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   vertice = CriarVerticeGrafo();
	   if(vertice == NULL) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   vertice->pValor = pVertice;
	   vertice->id = idVertice;

	   AdicionarVertice(pGrafo, vertice);
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Excluir vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVerticeCorrente( GRA_tppGrafo pGrafo ) {
	   LIS_tpCondRet condRetLis;

	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   RemoverVertice(pGrafo->pVerticeCorrente);
	   LIS_ProcurarValor(pGrafo->pListaVertices, (void *) pGrafo->pVerticeCorrente);
	   LIS_ExcluirElemento(pGrafo->pListaVertices);

	   condRetLis = LIS_ProcurarValor(pGrafo->pListaOrigens, (void *) pGrafo->pVerticeCorrente);
	   if(condRetLis == LIS_CondRetOK) {
		   LIS_ExcluirElemento(pGrafo->pListaOrigens);
	   }
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, char idVerticeOrigem, char idVerticeDestino, char * idAresta ) {
	   tppVerticeGrafo pVerticeOrigem, pVerticeDestino;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   pVerticeOrigem = PesquisaVertice(pGrafo->pListaVertices, idVerticeOrigem);
	   if(pVerticeOrigem == NULL) {
		   return GRA_CondRetVerticeInvalido;
	   }

	   pVerticeDestino = PesquisaVertice(pGrafo->pListaVertices, idVerticeDestino);
	   if(pVerticeDestino == NULL) {
		   return GRA_CondRetVerticeInvalido;
	   }

	   return AdicionarAresta(pGrafo,pVerticeOrigem,pVerticeDestino,idAresta);
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
