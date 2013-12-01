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

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define GRAFO_OWN
#include "GRAFO.H"
#undef GRAFO_OWN

#ifdef _DEBUG
#include "CONTA.H"
#include "CESPDIN.H"
#endif

/***********************************************************************
*
*  $TC Tipo de dados: GRA Descritor da célula do grafo
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct GRA_tagVerticeGrafo {
	   LIS_tppLista pListaAnt;
	   LIS_tppLista pListaSuc;
	   char id;
	   void * pValor;
#ifdef _DEBUG
		int idTipo;
		GRA_tppGrafo pCabeca;
		int tamValor;
#endif
   } GRA_tpVerticeGrafo ;

   typedef GRA_tpVerticeGrafo * GRA_tppVerticeGrafo;

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
	   GRA_tppVerticeGrafo pVerticeCorrente;
	   void ( * ExcluirValor ) ( void * pValor ) ;
#ifdef _DEBUG
	   int totalElem;
	   int tamValores;
#endif
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
	   GRA_tppVerticeGrafo pVerticeApontado;
		#ifdef _DEBUG
			GRA_tppGrafo pCabeca;
		#endif
   } GRA_tpAresta ;



/***** Protótipo das funções encapuladas no módulo *****/

	static void DestruirConteudoListaDeAresta (void * pAresta) ;

	static GRA_tppVerticeGrafo CriarVerticeGrafo (void) ;

	static GRA_tpVerticeGrafo * PesquisaVertice( LIS_tppLista pLista, char idVertice ) ;

	static GRA_tpVerticeGrafo * PesquisaVerticeNaListaDeAresta( LIS_tppLista pLista, char idVertice ) ;

	static void RemoverVertice ( GRA_tppGrafo pGrafo, GRA_tppVerticeGrafo pVertice ) ;

	static GRA_tpCondRet AdicionarAresta( GRA_tppVerticeGrafo pVerticeOrigem, GRA_tppVerticeGrafo pVerticeDestino, char * idAresta) ;


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
   	
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_CriarGrafo" ) ;
   	#endif

	   pGrafo->pVerticeCorrente = NULL;
	   
	   pGrafo->pListaOrigens = LIS_CriarLista( NULL ) ;
	   if (pGrafo->pListaOrigens == NULL){
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_CriarGrafo-pr0" ) ;
	   #endif

	   pGrafo->pListaVertices = LIS_CriarLista( NULL ) ;
	   if (pGrafo->pListaVertices == NULL){
		   LIS_DestruirLista(pGrafo->pListaOrigens);
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_CriarGrafo-pr1" ) ;
	   #endif

	   pGrafo->ExcluirValor = ExcluirValor;

	   *ppGrafo = pGrafo;

#ifdef _DEBUG
	   CED_MarcarEspacoAtivo(pGrafo);
	   pGrafo->totalElem = 0;
	   pGrafo->tamValores = 0;
#endif

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
	   
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_DestruirGrafo" ) ;
   	#endif

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
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_EsvaziarGrafo" ) ;
   	#endif

	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   while (LIS_ObterValor( pGrafo->pListaVertices ) ) {
	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "GRA_EsvaziarGrafo-while0" ) ;
	   	#endif
	   	RemoverVertice( pGrafo, (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices ) );
	   	if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1) == LIS_CondRetFimLista){
		   	#ifdef _DEBUG
		   	   CNT_CONTAR( "GRA_EsvaziarGrafo-while0-if0" ) ;
		   	#endif
				break;
	   	}
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

		#ifdef _DEBUG
		   CNT_CONTAR( "GRA_ObterValorCorrente" ) ;
		#endif

	   if (pGrafo->pVerticeCorrente == NULL){
   			#ifdef _DEBUG
				   CNT_CONTAR( "GRA_ObterValorCorrente-if0" ) ;
				#endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_ObterValorCorrente-pr0" ) ;
	   #endif
	   
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

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_AlterarValorCorrente" ) ;
   	#endif

	   if (pGrafo->pVerticeCorrente == NULL){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_AlterarValorCorrente-if0" ) ;
	   	 #endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_AlterarValorCorrente-pr0" ) ;
	   #endif

	   pGrafo->pVerticeCorrente->pValor = pValor;

#ifdef _DEBUG
		pGrafo->pVerticeCorrente->idTipo = CED_ObterTipoEspaco(pValor);
		pGrafo->tamValores -= pGrafo->pVerticeCorrente->tamValor;
		if(pValor != NULL){
			#ifdef _DEBUG
			   CNT_CONTAR( "GRA_AlterarValorCorrente-if1" ) ;
			#endif
			pGrafo->pVerticeCorrente->tamValor = CED_ObterTamanhoValor(pValor);
		} else {
			#ifdef _DEBUG
			   CNT_CONTAR( "GRA_AlterarValorCorrente-else0" ) ;
			#endif
			pGrafo->pVerticeCorrente->tamValor = 0;
		}
		pGrafo->tamValores += pGrafo->pVerticeCorrente->tamValor;
#endif

	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_IrParaVertice( GRA_tppGrafo pGrafo, char idVertice ) {
	   GRA_tppVerticeGrafo resultado;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_IrParaVertice" ) ;
   	#endif

	   if (pGrafo->pVerticeCorrente == NULL){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_IrParaVertice-if0" ) ;
	   	 #endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_IrParaVertice-pr0" ) ;
	   #endif

	   resultado = PesquisaVertice( pGrafo->pListaVertices, idVertice );
	   if(resultado == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_IrParaVertice-if1" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_IrParaVertice-pr1" ) ;
	   #endif

	   pGrafo->pVerticeCorrente = resultado;
	   
	   return GRA_CondRetOK;
   }


/***********************************************************************
*
*  $FC Função: GRA Andar para vertice
*
***********************************************************************/

   GRA_tpCondRet GRA_AndarParaVertice( GRA_tppGrafo pGrafo, char idVertice ) {
	   GRA_tppVerticeGrafo resultado;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_AndarParaVertice" ) ;
   	#endif

	   if (pGrafo->pVerticeCorrente == NULL){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_AndarParaVertice-if0" ) ;
	   	 #endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_AndarParaVertice-pr0" ) ;
	   #endif

	   resultado = PesquisaVerticeNaListaDeAresta( pGrafo->pVerticeCorrente->pListaSuc, idVertice );
	   if(resultado == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_AndarParaVertice-if1" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_AndarParaVertice-pr1" ) ;
	   #endif

	   pGrafo->pVerticeCorrente = resultado;

	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pVertice, char idVertice ) {
	   GRA_tppVerticeGrafo vertice;
	   LIS_tpCondRet CondRetLis;
	   
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

	   vertice = CriarVerticeGrafo();
	   if(vertice == NULL) {
		   return GRA_CondRetFaltouMemoria;
	   }

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_InserirVertice" ) ;
   	#endif

	   vertice->pValor = pVertice;
	   vertice->id = idVertice;

#ifdef _DEBUG
		(pGrafo->totalElem)++;
		vertice->pCabeca = pGrafo;
		vertice->tamValor = 0;
		vertice->idTipo = CED_ObterTipoEspaco(pVertice);
		pGrafo->tamValores -= vertice->tamValor;
		if(pVertice != NULL){
			#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirVertice-if0" ) ;
			#endif
			vertice->tamValor = CED_ObterTamanhoValor(pVertice);
		} else {
			#ifdef _DEBUG
			   CNT_CONTAR( "GRA_InserirVertice-else0" ) ;
			#endif
			vertice->tamValor = 0;
		}
		pGrafo->tamValores += vertice->tamValor;
#endif

	   LIS_IrFinalLista(pGrafo->pListaVertices);
	   CondRetLis = LIS_InserirElementoApos(pGrafo->pListaVertices, (void *) vertice);

	   if(pGrafo->pVerticeCorrente == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirVertice-if1" ) ;
	   	 #endif
		   pGrafo->pVerticeCorrente = vertice;
	   }

	   if (CondRetLis != LIS_CondRetOK){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirVertice-if2" ) ;
	   	 #endif
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirVertice-pr0" ) ;
	   #endif
	   
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

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_ExcluirVerticeCorrente" ) ;
   	#endif

   	 #ifdef _DEBUG
	   RemoverVertice(pGrafo, pGrafo->pVerticeCorrente, 1);
	   #else
	   RemoverVertice(pGrafo, pGrafo->pVerticeCorrente);
	   #endif
	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   LIS_ProcurarValor(pGrafo->pListaVertices, (void *) pGrafo->pVerticeCorrente);
	   LIS_ExcluirElemento(pGrafo->pListaVertices);

	   LIS_IrInicioLista(pGrafo->pListaOrigens);
	   condRetLis = LIS_ProcurarValor(pGrafo->pListaOrigens, (void *) pGrafo->pVerticeCorrente);
	   if(condRetLis == LIS_CondRetOK) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_ExcluirVerticeCorrente-if0" ) ;
	   	 #endif
		   LIS_ExcluirElemento(pGrafo->pListaOrigens);
	   }

	   // Reinicia corrente para o primeiro elemento da lista de vértices
	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   pGrafo->pVerticeCorrente = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
	   
	   return GRA_CondRetOK;
   }

   
/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, char idVerticeOrigem, char idVerticeDestino, char * idAresta ) {
	   GRA_tppVerticeGrafo pVerticeOrigem, pVerticeDestino;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_InserirAresta" ) ;
   	#endif

	   if (pGrafo->pVerticeCorrente == NULL){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirAresta-if0" ) ;
	   	 #endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirAresta-pr0" ) ;
	   #endif

	   pVerticeOrigem = PesquisaVertice(pGrafo->pListaVertices, idVerticeOrigem);

	   if(pVerticeOrigem == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirAresta-if1" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirAresta-pr1" ) ;
	   #endif

	   if(PesquisaVerticeNaListaDeAresta(pVerticeOrigem->pListaSuc, idVerticeDestino) != NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirAresta-if2" ) ;
	   	 #endif
		   return GRA_CondRetArestaJaExiste;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirAresta-pr2" ) ;
	   #endif

	   pVerticeDestino = PesquisaVertice(pGrafo->pListaVertices, idVerticeDestino);
	   if(pVerticeDestino == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirAresta-if3" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirAresta-pr3" ) ;
	   #endif

	   return AdicionarAresta(pVerticeOrigem,pVerticeDestino,idAresta);
   }

/***********************************************************************
*
*  $FC Função: GRA Inserir aresta no corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirArestaOrigemCorrente( GRA_tppGrafo pGrafo, char idVerticeDestino, char * idAresta ) {
	   GRA_tppVerticeGrafo pVerticeDestino;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
   	
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_InserirArestaOrigemCorrente" ) ;
   	#endif

	   if (pGrafo->pVerticeCorrente == NULL){
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-if0" ) ;
	   	 #endif
		   return GRA_CondRetGrafoVazio;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-pr0" ) ;
	   #endif

	   if(PesquisaVerticeNaListaDeAresta(pGrafo->pVerticeCorrente->pListaSuc, idVerticeDestino) != NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-if1" ) ;
	   	 #endif
		   return GRA_CondRetArestaJaExiste;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-pr1" ) ;
	   #endif

	   pVerticeDestino = PesquisaVertice(pGrafo->pListaVertices, idVerticeDestino);
	   if(pVerticeDestino == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-if2" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_InserirArestaOrigemCorrente-pr2" ) ;
	   #endif

	   return AdicionarAresta(pGrafo->pVerticeCorrente,pVerticeDestino,idAresta);
   }
   

/***********************************************************************
*
*  $FC Função: GRA Excluir aresta
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, char * idAresta ) {
	   GRA_tppVerticeGrafo pVertice, pVerticeDestino;
	   GRA_tpAresta * pAresta;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }

   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_ExcluirAresta" ) ;
   	#endif

	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   while (LIS_ObterValor( pGrafo->pListaVertices ) ) {
	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "GRA_ExcluirAresta-while0" ) ;
	   	#endif
			pVertice = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices );

			LIS_IrInicioLista( pVertice->pListaSuc );
			while (LIS_ObterValor( pVertice->pListaSuc ) ) {
				#ifdef _DEBUG
				   CNT_CONTAR( "GRA_ExcluirAresta-while1" ) ;
				#endif
				pAresta = (GRA_tpAresta *) LIS_ObterValor( pVertice->pListaSuc );

				if(strcmp(idAresta, pAresta->idAresta) == 0) {
					#ifdef _DEBUG
					   CNT_CONTAR( "GRA_ExcluirAresta-if0" ) ;
					#endif
					pVerticeDestino = pAresta->pVerticeApontado;

					LIS_ExcluirElemento( pVertice->pListaSuc );

					LIS_IrInicioLista( pVerticeDestino->pListaAnt);
					LIS_ProcurarValor( pVerticeDestino->pListaAnt, pVertice);
					LIS_ExcluirElemento( pVerticeDestino->pListaAnt );
					return GRA_CondRetOK;
				} else if(LIS_AvancarElementoCorrente(pVertice->pListaSuc, 1) == LIS_CondRetFimLista){
					#ifdef _DEBUG
					   CNT_CONTAR( "GRA_ExcluirAresta-if1" ) ;
					#endif
					break;
				}

				#ifdef _DEBUG
				   CNT_CONTAR( "GRA_ExcluirAresta-br0" ) ;
				#endif
			}

   		if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices, 1) == LIS_CondRetFimLista){
   			#ifdef _DEBUG
   			   CNT_CONTAR( "GRA_ExcluirAresta-if2" ) ;
   			#endif
				break;
   		}
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_ExcluirAresta-nwhile0" ) ;
	   #endif
	   
	   return GRA_CondRetArestaInvalida;
   }


/***********************************************************************
*
*  $FC Função: GRA Adicionar origem
*
***********************************************************************/

   GRA_tpCondRet GRA_AdicionarOrigem( GRA_tppGrafo pGrafo, char idVertice ) {
	   GRA_tppVerticeGrafo pVertice;
	   LIS_tpCondRet condRetLis;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
   	
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_AdicionarOrigem" ) ;
   	#endif

	   pVertice = PesquisaVertice(pGrafo->pListaVertices, idVertice);
	   if(pVertice == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_AdicionarOrigem-if0" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_AdicionarOrigem-pr0" ) ;
	   #endif

	   LIS_IrFinalLista(pGrafo->pListaOrigens);
	   condRetLis = LIS_InserirElementoApos(pGrafo->pListaOrigens, (void *) pVertice);
	   if(condRetLis == LIS_CondRetFaltouMemoria) {
	   		#ifdef _DEBUG
	   		   CNT_CONTAR( "GRA_AdicionarOrigem-if1" ) ;
	   		#endif
	   		return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_AdicionarOrigem-pr1" ) ;
	   #endif

	   return GRA_CondRetOK;

   }


/***********************************************************************
*
*  $FC Função: GRA Remover origem
*
***********************************************************************/

   GRA_tpCondRet GRA_RemoverOrigem( GRA_tppGrafo pGrafo, char idVertice ) {
	   GRA_tppVerticeGrafo pVertice;
	   if (pGrafo == NULL){
		   return GRA_CondRetPonteiroNulo;
	   }
   	
   	#ifdef _DEBUG
   	   CNT_CONTAR( "GRA_RemoverOrigem" ) ;
   	#endif

	   pVertice = PesquisaVertice(pGrafo->pListaOrigens, idVertice);
	   if(pVertice == NULL) {
	   	 #ifdef _DEBUG
	   	    CNT_CONTAR( "GRA_RemoverOrigem-if0" ) ;
	   	 #endif
		   return GRA_CondRetVerticeInvalido;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "GRA_RemoverOrigem-pr0" ) ;
	   #endif

	   LIS_ExcluirElemento( pGrafo->pListaOrigens );

	   return GRA_CondRetOK;
   }


#ifdef _DEBUG
/***********************************************************************
*
*  $FC Função: GRA Verificar estrutura
*
***********************************************************************/


#define INCERROS (*numErros)++; printf("\nLINHA %d\n",__LINE__)

   GRA_tpCondRet GRA_VerificarEstrutura( GRA_tppGrafo pGrafo, int * numErros ) {
	   int achou, qtd = 0, somaTam = 0;
	   GRA_tppVerticeGrafo pVertice, pVertice2;
	   GRA_tpAresta * pAresta;

	   *numErros = 0;
	   
	   LIS_IrInicioLista( pGrafo->pListaVertices );
	   if(LIS_ObterValor(pGrafo->pListaVertices) != NULL)
	   {
			if(pGrafo->pVerticeCorrente == NULL){
				INCERROS;
			}

			if(LIS_AvancarElementoCorrente(pGrafo->pListaOrigens, 1) != LIS_CondRetFimLista)
			{
				pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
				if(pVertice != pGrafo->pVerticeCorrente){
					INCERROS;
				}
			}
	   }

	   LIS_IrInicioLista(pGrafo->pListaOrigens);
	   while( LIS_ObterValor( pGrafo->pListaOrigens ) ) {
		   pVertice = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaOrigens );
		   LIS_IrInicioLista(pGrafo->pListaVertices);
		   if( LIS_ProcurarValor(pGrafo->pListaVertices, pVertice) != LIS_CondRetOK ){
			   INCERROS;
		   }

		   if( LIS_AvancarElementoCorrente( pGrafo->pListaOrigens, 1 ) != LIS_CondRetOK ){
			   break;
		   }
	   }

	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   if(LIS_ProcurarValor(pGrafo->pListaVertices, pGrafo->pVerticeCorrente) != LIS_CondRetOK){
		   INCERROS;
	   }

	   // Para cada vertice
	   LIS_IrInicioLista(pGrafo->pListaVertices);
	   while( LIS_ObterValor( pGrafo->pListaVertices ) ) {
		   pVertice = (GRA_tppVerticeGrafo) LIS_ObterValor( pGrafo->pListaVertices );

		   // Para cada predecessor
		   LIS_IrInicioLista(pVertice->pListaAnt);
		   while( LIS_ObterValor( pVertice->pListaAnt ) ) {
				pVertice2 = (GRA_tppVerticeGrafo) LIS_ObterValor( pVertice->pListaAnt );
				achou = 0;
				// Para cada sucessor do predecessor
				LIS_IrInicioLista(pVertice2->pListaSuc);
				while( LIS_ObterValor( pVertice2->pListaSuc ) ) {
					pAresta = (GRA_tpAresta *) LIS_ObterValor( pVertice2->pListaSuc );

						if( pAresta->pVerticeApontado == pVertice )
							achou = 1;

					if( LIS_AvancarElementoCorrente( pVertice2->pListaSuc, 1 ) != LIS_CondRetOK )
						break;
				} // Fim: Para cada sucessor do predecessor
				if(!achou){
					INCERROS;
				}
				if( LIS_AvancarElementoCorrente( pVertice->pListaAnt, 1 ) != LIS_CondRetOK )
					break;
		   } // Fim: Para cada predecessor


		   // Para cada sucessor
		   LIS_IrInicioLista(pVertice->pListaSuc);
		   while( LIS_ObterValor( pVertice->pListaSuc ) ) {
				pAresta = (GRA_tpAresta *) LIS_ObterValor( pVertice->pListaSuc );
				
					if(pAresta->pCabeca != pGrafo){
						INCERROS;
					}

					if(pAresta->pVerticeApontado->pCabeca != pGrafo){
						INCERROS;
					}

					LIS_IrInicioLista(pAresta->pVerticeApontado->pListaAnt);
					if(LIS_ProcurarValor(pAresta->pVerticeApontado->pListaAnt, pVertice) != LIS_CondRetOK){
						INCERROS;
					}

				if( LIS_AvancarElementoCorrente( pVertice->pListaSuc, 1 ) != LIS_CondRetOK )
					break;
		   } // Fim: Para cada sucessor

		   if(pVertice->pCabeca != pGrafo){
			   INCERROS;
		   }

		   if((pVertice->pValor == NULL && pVertice->tamValor != 0) || (pVertice->pValor != NULL && pVertice->tamValor != CED_ObterTamanhoValor(pVertice->pValor) )){
			   INCERROS;
		   }

		   if(pVertice->pValor != NULL && pVertice->idTipo != CED_ObterTipoEspaco(pVertice->pValor)){
			   INCERROS;
		   }

		   qtd++;

		   somaTam += pVertice->tamValor;

		   if( LIS_AvancarElementoCorrente( pGrafo->pListaVertices, 1 ) != LIS_CondRetOK )
			   break;
	   } // Fim: Para cada vertice

	   if(pGrafo->totalElem != qtd){
		   INCERROS;
	   }

	   if(pGrafo->tamValores != somaTam){
		   INCERROS;
	   }

		//printf("\n tamvalores %d - somatam %d\n", pGrafo->tamValores, somaTam);

	   return GRA_CondRetOK;
   }

#undef INCERROS


/***********************************************************************
*
*  $FC Função: GRA Deturpar estrutura
*
***********************************************************************/

   GRA_tpCondRet GRA_Deturpar( GRA_tppGrafo pGrafo, int flag ) {
		GRA_tppVerticeGrafo pVertice;
		GRA_tpAresta * pAresta;
		void * pValor;
		int concluido = 0;
		switch(flag) {
			case 1:
				free(pGrafo->pVerticeCorrente);
				break;
			case 2:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					LIS_IrInicioLista(pVertice->pListaSuc);
					pAresta = LIS_ObterValor(pVertice->pListaSuc);
					if(pAresta != NULL) {
						pAresta->pVerticeApontado = NULL;
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 3:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					LIS_IrInicioLista(pVertice->pListaAnt);
					if(LIS_ExcluirElemento( pVertice->pListaAnt ) == LIS_CondRetOK) {
						LIS_InserirElementoAntes( pVertice->pListaAnt, NULL );
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 4:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					LIS_IrInicioLista(pVertice->pListaSuc);
					pAresta = LIS_ObterValor(pVertice->pListaSuc);
					if(pAresta != NULL) {
						pAresta->pVerticeApontado = (GRA_tppVerticeGrafo)0x00012345;
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 5:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					LIS_IrInicioLista(pVertice->pListaAnt);
					if(LIS_ExcluirElemento( pVertice->pListaAnt ) == LIS_CondRetOK) {
						LIS_InserirElementoAntes( pVertice->pListaAnt, (void*)0x00012345 );
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 6:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					if(pVertice != NULL) {
						pVertice->pValor = NULL;
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 7:
				LIS_IrInicioLista(pGrafo->pListaVertices);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaVertices);
					if(pVertice != NULL) {
						pVertice->idTipo = 40;
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaVertices,1) != LIS_CondRetOK) break;
				}
				break;
			case 8:
				// to do
				break;
			case 9:
				pGrafo->pVerticeCorrente = NULL;
				break;
			case 10:
				LIS_IrInicioLista(pGrafo->pListaOrigens);
				while( !concluido ) {
					pVertice = (GRA_tppVerticeGrafo)LIS_ObterValor(pGrafo->pListaOrigens);
					if(pVertice != NULL) {
						LIS_ExcluirElemento(pGrafo->pListaOrigens);
						LIS_InserirElementoAntes(pGrafo->pListaOrigens, NULL);
						concluido = 1;
					}

					if(LIS_AvancarElementoCorrente(pGrafo->pListaOrigens,1) != LIS_CondRetOK) break;
				}
				break;
		}

	   return GRA_CondRetOK;
   }
#endif

/***** Código das funções encapuladas no módulo *****/


/***********************************************************************
*
*  $FC Função: GRA - Destruir conteudo lista de aresta
*
*  $ED Descrição da função
*  Função auxiliar para ser passada durante a criaça da lista de
*  sucessores
*
***********************************************************************/

   static void DestruirConteudoListaDeAresta (void * pAresta) {
   		#ifdef _DEBUG
   		   CNT_CONTAR( "DestruirConteudoListaDeAresta" ) ;
   		#endif
	   free(pAresta);
   }


/***********************************************************************
*
*  $FC Função: GRA - Criar Vertice Grafo
*
*  $ED Descrição da função
*  Cria estrutura interna do vértice, com as devidas verificações
*  de memória
*
***********************************************************************/

   static GRA_tppVerticeGrafo CriarVerticeGrafo (void){
	   GRA_tppVerticeGrafo pVertice = NULL;
	   
	   pVertice = (GRA_tppVerticeGrafo) malloc(sizeof(GRA_tpVerticeGrafo));
	   if (pVertice == NULL){
		   return NULL;
	   }

	   pVertice->pValor = NULL;
	   
	   pVertice->pListaAnt = LIS_CriarLista( NULL ) ;
	   if (pVertice->pListaAnt == NULL){
		   free(pVertice);
		   return NULL;
	   }

	   pVertice->pListaSuc = LIS_CriarLista( DestruirConteudoListaDeAresta ) ;
	   if (pVertice->pListaSuc == NULL){
		   LIS_DestruirLista(pVertice->pListaAnt);
		   free(pVertice);
		   return NULL;
	   }

	   #ifdef _DEBUG
     	CNT_CONTAR( "CriarVerticeGrafo" ) ;
	   	CED_MarcarEspacoAtivo(pVertice);
		 #endif

	   return pVertice;
   }


/***********************************************************************
*
*  $FC Função: GRA - Pesquisa Vertice
*
*  $ED Descrição da função
*  Pesquisa um vértice pelo seu id em uma lista cujos valores
*  referenciam estruturas de vértice do tipo GRA_tpVerticeGrafo
*
***********************************************************************/

   static GRA_tpVerticeGrafo * PesquisaVertice( LIS_tppLista pLista, char idVertice ) {
	   GRA_tpVerticeGrafo * pVerticeGrafo;
	   LIS_IrInicioLista( pLista );

	   #ifdef _DEBUG
	      CNT_CONTAR( "PesquisaVertice" ) ;
	   #endif

	   while (LIS_ObterValor( pLista ) ) {

	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "PesquisaVertice-while0" ) ;
	   	#endif

		   pVerticeGrafo = (GRA_tpVerticeGrafo *) LIS_ObterValor( pLista );
		   if( pVerticeGrafo != NULL && pVerticeGrafo->id == idVertice ){
		   		#ifdef _DEBUG
		   		   CNT_CONTAR( "PesquisaVertice-if0" ) ;
		   		#endif
			   return pVerticeGrafo;
		   }

		   #ifdef _DEBUG
		      CNT_CONTAR( "PesquisaVertice-pr0" ) ;
		   #endif

		    if( LIS_AvancarElementoCorrente( pLista, 1 ) == LIS_CondRetFimLista ){
		    	#ifdef _DEBUG
		    	   CNT_CONTAR( "PesquisaVertice-if1" ) ;
		    	#endif
					break;
				}

				#ifdef _DEBUG
				   CNT_CONTAR( "PesquisaVertice-br0" ) ;
				#endif
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "PesquisaVertice-nwhile1" ) ;
	   #endif

	   return NULL;
   }


/***********************************************************************
*
*  $FC Função: GRA - Pesquisa Vertice na lista de aresta
*
*  $ED Descrição da função
*  Pesquisa um vértice pelo seu id em uma lista cujos valores
*  referenciam estruturas de aresta do tipo GRA_tpAresta, que por
*  vez referenciam estruturas do tipo GRA_tpVerticeGrafo
*
***********************************************************************/

   static GRA_tpVerticeGrafo * PesquisaVerticeNaListaDeAresta( LIS_tppLista pLista, char idVertice ) {
	   GRA_tpAresta * pAresta;
	   LIS_IrInicioLista( pLista );

	   #ifdef _DEBUG
	      CNT_CONTAR( "PesquisaVerticeNaListaDeAresta" ) ;
	   #endif

	   while (LIS_ObterValor( pLista ) ) {

	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-while0" ) ;
	   	#endif

		   pAresta = (GRA_tpAresta *) LIS_ObterValor( pLista );

		   if( pAresta != NULL && pAresta->pVerticeApontado->id == idVertice ){
		   		#ifdef _DEBUG
		   		   CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-if0" ) ;
		   		#endif
			   return pAresta->pVerticeApontado;
		   }

		   #ifdef _DEBUG
		      CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-pr0" ) ;
		   #endif


		   if( LIS_AvancarElementoCorrente( pLista, 1 ) == LIS_CondRetFimLista ){
		   	#ifdef _DEBUG
		   	   CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-if1" ) ;
		   	#endif
				break;
			 }

			 #ifdef _DEBUG
			    CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-br0" ) ;
			 #endif
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "PesquisaVerticeNaListaDeAresta-nwhile0" ) ;
	   #endif

	   return NULL;
   }


/***********************************************************************
*
*  $FC Função: GRA - Remover vértice
*
*  $ED Descrição da função
*  Remove pVertice de pGrafo, destruindo todas as arestas em seus
*  antecessores e sucessores, além do conteúdo armazenado neste
*
***********************************************************************/

   static void RemoverVertice ( GRA_tppGrafo pGrafo, GRA_tppVerticeGrafo pVertice
#ifdef _DEBUG
   	, int darFree
#endif
    ){
	   GRA_tpVerticeGrafo * pVerticeSuc;
	   GRA_tpAresta * pAresta;

	   #ifdef _DEBUG
	      CNT_CONTAR( "RemoverVertice" ) ;
	   #endif
	   
	   //Remover arestas sucessoras
	   LIS_IrInicioLista( pVertice->pListaSuc );
	   
	   while( LIS_ObterValor( pVertice->pListaSuc ) ) {

	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "RemoverVertice-while0" ) ;
	   	#endif

		   pAresta = (GRA_tpAresta *) LIS_ObterValor( pVertice->pListaSuc );
		   if( pAresta != NULL && pAresta->pVerticeApontado != NULL && pAresta->pVerticeApontado->pListaAnt != NULL) {

		   	 #ifdef _DEBUG
		   	    CNT_CONTAR( "RemoverVertice-if0" ) ;
		   	 #endif

			   LIS_IrInicioLista( pAresta->pVerticeApontado->pListaAnt );
			   LIS_ProcurarValor( pAresta->pVerticeApontado->pListaAnt, pVertice );
			   LIS_ExcluirElemento( pAresta->pVerticeApontado->pListaAnt );
		   }

		   if( LIS_AvancarElementoCorrente( pVertice->pListaSuc, 1 ) == LIS_CondRetFimLista ){
		   	 #ifdef _DEBUG
		   	    CNT_CONTAR( "RemoverVertice-if1" ) ;
		   	 #endif
			   break;
		   }

		   #ifdef _DEBUG
		      CNT_CONTAR( "RemoverVertice-br0" ) ;
		   #endif

	   }

	   LIS_DestruirLista( pVertice->pListaSuc );
	   pVertice->pListaSuc = NULL;

	   //Remover arestas antecessoras
	   LIS_IrInicioLista( pVertice->pListaAnt );
	   
		while(LIS_ObterValor( pVertice->pListaAnt ) ) {

			#ifdef _DEBUG
			   CNT_CONTAR( "RemoverVertice-while1" ) ;
			#endif

		   pVerticeSuc = (GRA_tpVerticeGrafo *) LIS_ObterValor( pVertice->pListaAnt );
		   if( pVerticeSuc != NULL && pVerticeSuc->pListaSuc != NULL) {

		   	 #ifdef _DEBUG
		   	    CNT_CONTAR( "RemoverVertice-if2" ) ;
		   	 #endif

			   PesquisaVerticeNaListaDeAresta( pVerticeSuc->pListaSuc, pVertice->id );
			   LIS_ExcluirElemento( pVerticeSuc->pListaSuc );
		   }

		   if( LIS_AvancarElementoCorrente( pVertice->pListaAnt, 1 ) == LIS_CondRetFimLista ){
		   	 #ifdef _DEBUG
		   	    CNT_CONTAR( "RemoverVertice-if3" ) ;
		   	 #endif
			   break;
		   }

		   #ifdef _DEBUG
		      CNT_CONTAR( "RemoverVertice-br1" ) ;
		   #endif
	   }

	   LIS_DestruirLista( pVertice->pListaAnt );
	   pVertice->pListaAnt = NULL;

	   pGrafo->ExcluirValor( pVertice->pValor );

#ifdef _debug
	   if(darFree){
	   	CNT_CONTAR( "RemoverVertice-if4" ) ;
	   	free( pVertice );
	   } else {
	   	#ifdef _DEBUG
	   	   CNT_CONTAR( "RemoverVertice-else0" ) ;
	   	#endif
	   }
#else
	   free( pVertice );
#endif

#ifdef _DEBUG
	   (pGrafo->totalElem)--;
#endif

   }


/***********************************************************************
*
*  $FC Função: GRA - Adicionar Aresta
*
*  $ED Descrição da função
*  Adiciona uma aresta de pVerticeOrigem para pVerticeDestino,
*  identificada por idAresta
*
***********************************************************************/

   static GRA_tpCondRet AdicionarAresta( GRA_tppVerticeGrafo pVerticeOrigem, GRA_tppVerticeGrafo pVerticeDestino, char * idAresta) {

	   LIS_tpCondRet CondRetLis;
	   GRA_tpAresta * pAresta;
	   pAresta = (GRA_tpAresta *)malloc(sizeof(GRA_tpAresta));
	   if(pAresta == NULL) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "AdicionarAresta" ) ;
	   #endif

	   strcpy(pAresta->idAresta, idAresta);
	   pAresta->pVerticeApontado = pVerticeDestino;
#ifdef _DEBUG
	   pAresta->pCabeca = pVerticeOrigem->pCabeca;
#endif

	   LIS_IrFinalLista(pVerticeOrigem->pListaSuc);
	   CondRetLis = LIS_InserirElementoApos(pVerticeOrigem->pListaSuc, (void *) pAresta);
	   if(CondRetLis == LIS_CondRetFaltouMemoria) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "AdicionarAresta-pr1" ) ;
	   #endif

	   LIS_IrFinalLista(pVerticeDestino->pListaAnt);
	   CondRetLis = LIS_InserirElementoApos(pVerticeDestino->pListaAnt, (void *) pVerticeOrigem);
	   if(CondRetLis == LIS_CondRetFaltouMemoria) {
		   return GRA_CondRetFaltouMemoria;
	   }

	   #ifdef _DEBUG
	      CNT_CONTAR( "AdicionarAresta-pr1" ) ;
	   #endif

#ifdef _DEBUG
	   CED_MarcarEspacoAtivo(pAresta);
#endif

	   return GRA_CondRetOK;
   }


/********** Fim do módulo de implementação: Módulo grafo dirigido **********/
