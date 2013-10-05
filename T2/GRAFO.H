#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: Grafo dirigido
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e explorar grafos dirigidos.

*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"
#include "VERTICE.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da grafo
*
***********************************************************************/

   typedef enum {

         GRA_CondRetOK ,
               /* Executou corretamente */

		 GRA_CondRetGrafoVazio ,
			   /* Operação inválida pois o grafo está vazio */

		 GRA_CondRetVerticeInvalido ,
			   /* Vertice que deseja ir não existe ou não é acessível */
			   
		 GRA_CondRetErroVertice ,
			   /* Operação no vértice resultou em erro */

         GRA_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         GRA_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } GRA_tpCondRet ;
   

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Cria um novo grafo.
*     O ponteiro para o novo grafo será fornecido no valor do ponteiro
*     de ponteiro para grafo.
*
*  $EP Parâmetros
*     $P ppGrafo - ponteiro para o ponteiro de grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo * ppGrafo ) ;


/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo, liberando o espaço ocupado
*     pela grafo, pelos vértices e pelas listas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
***********************************************************************/

   GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo ) ;


/***********************************************************************
*
*  $FC Função: GRA Esvaziar
*
*  $ED Descrição da função
*     Esvazia a grafo, isso é, libera todos os vértices e listas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
***********************************************************************/

   GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo pGrafo ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
*  $ED Descrição da função
*     O valor do vértice corrente é retornado pelo parâmetro ppValor.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P ppValor - ponteiro para o ponteiro de vertice, a ser modificado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
***********************************************************************/

   GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice * ppValor ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Alterar valor do vértice corrente
*
*  $ED Descrição da função
*     O vértice corrente é alterado para o valor de pValor.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P pValor - ponteiro para um valor de vertice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
***********************************************************************/

   GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo, VER_tppVertice pValor ) ;


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
*  $ED Descrição da função
*     O vértice corrente torna-se o vértice cujo valor é o dado, se
*		existir tal vértice no grafo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P pVertice - ponteiro para o vertice que deseja ir
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*	  GRA_CondRetVerticeInvalido
*
***********************************************************************/

   GRA_tpCondRet GRA_IrParaVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
*  $ED Descrição da função
*     O vértice corrente torna-se o vértice cujo valor é o dado, desde
*		que tal vértice seja um dos sucessores do corrente.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P pVertice - ponteiro para o vertice que deseja ir
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*	  GRA_CondRetVerticeInvalido
*
***********************************************************************/

   GRA_tpCondRet GRA_AndarParaVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
*  $ED Descrição da função
*     Cria um novo vértice a partir do valor dado.
*	  O novo vértice não possui arestas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P pVertice - ponteiro para o conteúdo a ser inserido no novo vértice criado.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Excluir vértice corrente
*
*  $ED Descrição da função
*     Exclui o vértice corrente.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetGrafoVazio
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVerticeCorrente( GRA_tppGrafo pGrafo ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta no vértice corrente, dirigida ao vértice cujo valor
*		é igual ao dado, se este existir
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P pVertice - ponteiro para o vértice de destino da aresta
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetDirecaoInvalida
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) ;
   

/***********************************************************************
*
*  $FC Função: GRA Excluir aresta
*
*  $ED Descrição da função
*     Exclui a aresta do vértice corrente que o liga ao vértice cujo valor
*		é igual ao dado, se este existir.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P pVertice - ponteiro para o vértice de destino da aresta
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	  GRA_CondRetDirecaoInvalida
*     GRA_CondRetFaltouMemoria
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, VER_tppVertice pVertice ) ;
   

#undef Grafo_EXT

/********** Fim do módulo de definição: Módulo grafo **********/

#else
#endif
