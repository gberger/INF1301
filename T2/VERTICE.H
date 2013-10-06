#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD Módulo de definição: VER  Vértice de grafo com conteúdo genérico
*
*  Arquivo gerado:              VERTICE.h
*  Letras identificadoras:      VER
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa vértices que armazenam conteúdo genérico.
*     Cada elemento do vértice armazena uma referência para tipo genérico
*
***************************************************************************/
 
#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um vértice */

typedef void ** VER_tppVertice ;


/***********************************************************************
*
*  $TC Tipo de dados: VER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK ,
               /* Concluiu corretamente */

         VER_CondRetVerticeVazio ,
               /* Vértice não possui conteúdo */

         VER_CondRetPonteiroNulo ,
               /* Ponteiro fornecido é nulo */

         VER_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de
               * vértice ou um elemento da lista de arestas */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VER  &Criar vértice
*
*  $ED Descrição da função
*     Cria um vértice que armazena conteúdo genérico.
*
*  $EP Parâmetros
*     ppVertice - ponteiro para tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*     VER_CondRetFaltouMemoria
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice( VER_tppVertice * ppVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*     O parâmetro tipo referência para vértice não é modificado,
*     assim como o conteúdo não é destruído.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Esvaziar vértice
*
*  $ED Descrição da função
*     Anula referência armazenada no vértice.
*     O conteúdo em si não é destruido.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*
***********************************************************************/

   VER_tpCondRet VER_EsvaziarVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Atribuir valor
*
*  $ED Descrição da função
*     Atribui referência genérica ao valor do vértice
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*     valor - ponteiro para conteúdo genérico
*
*  $FV Valor retornado
*     VER_CondRetOK
*
***********************************************************************/

   VER_tpCondRet VER_AtribuirValor( VER_tppVertice pVertice, void * valor ) ;

/***********************************************************************
*
*  $FC Função: VER  &Obter valor
*
*  $ED Descrição da função
*     Obtem referência para contúdo genérico armazenado no vértice.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*     pValor - ponteiro de ponteiro para conteúdo genérico
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeVazio
*
***********************************************************************/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice, void ** pValor ) ;


#undef VERTICE_EXT

/********** Fim do módulo de definição: VER  Vértice de grafo com conteúdo genérico **********/

#else
#endif
