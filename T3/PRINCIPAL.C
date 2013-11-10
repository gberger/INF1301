/***************************************************************************
*  $MCI Módulo de implementação: Módulo principal
*
*  Arquivo gerado:              PRINCIPAL.C
*  Letras identificadoras:      PRN
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <string.h>

/***********************************************************************
*
*  $TC Tipo de dados: PRN Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo principal
*
***********************************************************************/

   typedef enum {

         PRN_CondRetOK ,
               /* Executou corretamente */

         PRN_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         PRN_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } PRN_tpCondRet ;


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

/***** Protótipo das funções encapuladas no módulo *****/

	static void DestruirConteudoListaDeAresta (void * pAresta) ;

	static GRA_tppVerticeGrafo CriarVerticeGrafo (void) ;

	static GRA_tpVerticeGrafo * PesquisaVertice( LIS_tppLista pLista, int idVertice ) ;

	static GRA_tpVerticeGrafo * PesquisaVerticeNaListaDeAresta( LIS_tppLista pLista, int idVertice ) ;

	static void RemoverVertice ( GRA_tppGrafo pGrafo, GRA_tppVerticeGrafo pVertice ) ;

	static GRA_tpCondRet AdicionarAresta( GRA_tppVerticeGrafo pVerticeOrigem, GRA_tppVerticeGrafo pVerticeDestino, int idAresta) ;


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
	   
	   pGrafo->pListaOrigens = LIS_CriarLista( NULL ) ;
	   if (pGrafo->pListaOrigens == NULL){
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->pListaVertices = LIS_CriarLista( NULL ) ;
	   if (pGrafo->pListaVertices == NULL){
		   LIS_DestruirLista(pGrafo->pListaOrigens);
		   free(pGrafo);
		   return GRA_CondRetFaltouMemoria;
	   }

	   pGrafo->ExcluirValor = ExcluirValor;

	   *ppGrafo = pGrafo;

	   return GRA_CondRetOK;
   };

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
	   free(pAresta);
   }

/********** Fim do módulo de implementação: Módulo principal **********/
