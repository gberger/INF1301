/***************************************************************************
*  $MCI Módulo de implementação: TVER Teste vértice de grafo genérico
*
*  Arquivo gerado:              TestVER.c
*  Letras identificadoras:      TVER
*
*  Nome da base de software:    Arcabouço para a automação de testes de programas redigidos em C
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\VERTICE.BSW
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>
#include    <malloc.h>

#include    "TST_Espc.h"

#include    "Generico.h"
#include    "LerParm.h"

#include    "Vertice.h"

static const char RESET_VERTICE_CMD       [ ] = "=resetteste"     ;
static const char CRIAR_VERTICE_CMD       [ ] = "=criarvertice"   ;
static const char DESTRUIR_VERTICE_CMD    [ ] = "=destruirvertice";
static const char ESVAZIAR_VERTICE_CMD    [ ] = "=esvaziarvertice";
static const char ATRIBUIR_VALOR_CMD      [ ] = "=atribuirvalor"  ;
static const char OBTER_VALOR_CMD         [ ] = "=obtervalor"     ;


#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_VERTICE   10
#define DIM_VALOR     100

VER_tppVertice   vtVertices[ DIM_VT_VERTICE ] ;

/***** Protótipos das funções encapuladas no módulo *****/

   static void DestruirValor( void * pValor ) ;

   static int ValidarInxVertice( int inxVertice , int Modo ) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TLIS &Testar vértices
*
*  $ED Descrição da função
*     Podem ser criadas até 10 vértices, identificadas pelos índices 0 a 10
*
*     Comandos disponíveis:
*
*     =resetteste
*           - anula o vetor de vértices. Provoca vazamento de memória
*     =criarvertice               inxVertice
*     =destruirvertice            inxVertice
*     =esvaziarvertice            inxVertice
*     =atribuirvalor              inxVertice  string  CondRetEsp
*     =obtervalor                 inxVertice  string  CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxVertice  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      TST_tpCondRet CondRet ;

      char   StringDado[  DIM_VALOR ] ;
      void * pDado ;

      int i ;

      StringDado[ 0 ] = 0 ;

      /* Efetuar reset de teste de vertice */

         if ( strcmp( ComandoTeste , RESET_VERTICE_CMD ) == 0 )
         {

            for( i = 0 ; i < DIM_VT_VERTICE ; i++ )
            {
               vtVertices[ i ] = NULL ;
            } /* for */

            return TST_CondRetOK ;

         } /* fim ativa: Efetuar reset de teste de vertice */

      /* Testar CriarVertice */

         else if ( strcmp( ComandoTeste , CRIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                       &inxVertice ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxVertice( inxVertice , VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

			VER_CriarVertice( &vtVertices[ inxVertice ] ) ;

            return TST_CompararPonteiroNulo( 1 , vtVertices[ inxVertice ] ,
               "Erro em ponteiro de nova vertice."  ) ;

         } /* fim ativa: Testar CriarVertice */

      /* Testar Esvaziar vértice */

         else if ( strcmp( ComandoTeste , ESVAZIAR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxVertice ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxVertice( inxVertice , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            VER_EsvaziarVertice( vtVertices[ inxVertice ] ) ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Esvaziar vertice */

      /* Testar Destruir vertice */

         else if ( strcmp( ComandoTeste , DESTRUIR_VERTICE_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "i" ,
                               &inxVertice ) ;

            if ( ( numLidos != 1 )
              || ( ! ValidarInxVertice( inxVertice , NAO_VAZIO )))
            {
               return TST_CondRetParm ;
            } /* if */

            VER_DestruirVertice( vtVertices[ inxVertice ] ) ;
            vtVertices[ inxVertice ] = NULL ;

            return TST_CondRetOK ;

         } /* fim ativa: Testar Destruir vertice */

      /* Testar atribuir valor */

         else if ( strcmp( ComandoTeste , ATRIBUIR_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxVertice , StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxVertice( inxVertice , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = VER_AtribuirValor( vtVertices[ inxVertice ] , (void *) StringDado ) ;

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao atribuir valor."  ) ;

         } /* fim ativa: Testar atribuir valor */

      /* Testar obter valor */

         else if ( strcmp( ComandoTeste , OBTER_VALOR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "isi" ,
                       &inxVertice , StringDado , &CondRetEsp ) ;

            if ( ( numLidos != 3 )
              || ( ! ValidarInxVertice( inxVertice , NAO_VAZIO )) )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRet = VER_ObterValor( vtVertices[ inxVertice ] , &pDado ) ;

			if ( CondRetEsp != 0 )
            {
               return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao obter valor."  ) ;
            } /* if */

            if ( pDado == NULL )
            {
               return TST_CompararPonteiroNulo( 1 , pDado ,
                         "Dado tipo um deveria existir." ) ;
            } /* if */

            return TST_CompararString( StringDado , (char *) pDado ,
                         "Valor do elemento errado." ) ;

         } /* fim ativa: Testar inserir elemento apos */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TLIS &Testar vertice */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de vértice
*
***********************************************************************/

   int ValidarInxVertice( int inxVertice , int Modo )
   {

      if ( ( inxVertice <  0 )
        || ( inxVertice >= DIM_VT_VERTICE ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtVertices[ inxVertice ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtVertices[ inxVertice ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TLIS -Validar indice de vértice */

/********** Fim do módulo de implementação: TVER Teste vértice de grafo genérico **********/

