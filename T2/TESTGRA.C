/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste de grafo genérico
*
*  Arquivo gerado:              TESTGRA.c
*  Letras identificadoras:      TGRA
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

#include    "Grafo.h"
#include    "Vertice.h"

static const char CRIAR_GRAFO_CMD         [ ] = "=criargrafo"           ;
static const char DESTRUIR_GRAFO_CMD      [ ] = "=destruirgrafo"        ;
static const char ESV_GRAFO_CMD           [ ] = "=esvaziargrafo"        ;
static const char CORR_GRAFO_CMD          [ ] = "=obtercorrente"        ;
static const char ALTCORR_GRAFO_CMD       [ ] = "=alterarcorrente"      ;
static const char IRVER_GRAFO_CMD         [ ] = "=irparavertice"        ;
static const char ANDARVER_GRAFO_CMD      [ ] = "=andarparavertice"     ;
static const char INSVER_GRAFO_CMD        [ ] = "=inserirvertice"       ;
static const char EXCCORR_GRAFO_CMD       [ ] = "=excluircorrente"      ;
static const char INSAR_GRAFO_CMD         [ ] = "=inseriraresta"        ;
static const char INSARO_GRAFO_CMD        [ ] = "=inserirarestaorigem"  ;
static const char EXCAR_GRAFO_CMD         [ ] = "=excluiraresta"        ;
static const char ADDOR_GRAFO_CMD         [ ] = "=adicionarorigem"      ;
static const char RMVOR_GRAFO_CMD         [ ] = "=removerorigem"        ;

#define TRUE  1
#define FALSE 0

#define VAZIO     0
#define NAO_VAZIO 1

#define DIM_VT_GRAFO   10
#define DIM_VALOR     100

GRA_tppGrafo vtGRAFO[ DIM_VT_GRAFO ] ;

/*****  Código das funções exportadas pelo módulo  *****/

	static int ValidarInxGrafo( int inxGrafo , int Modo ) ;

	static void DestruirValor( void * pValor ) ;

/***********************************************************************
*
*  $FC Função: TLIS &Testar vértices
*
*  $ED Descrição da função
*     Podem ser criadas até 10 grafos, identificados pelos índices 0 a 9
*
*     Comandos disponíveis:
*
* =criargrafo            inxGrafo CondRetEsp 
* =destruirgrafo         inxGrafo CondRetEsp
* =esvaziargrafo         inxGrafo CondRetEsp
* =obtercorrente         inxGrafo ValorComparado CondRetEsp
* =alterarcorrente       inxGrafo ValorDoVertice CondRetEsp
* =irparavertice         inxGrafo idVertice CondRetEsp 
* =andarparavertice      inxGrafo idVertice CondRetEsp
* =inserirvertice        inxGrafo ValorDoVertice idVertice CondRetEsp
* =excluircorrente       inxGrafo CondRetEsp
* =inseriraresta         inxGrafo idVertice1 idVertice2 idAresta CondRetEsp
* =inserirarestaorigem   inxGrafo idVertice idAresta CondRetEsp
* =excluiraresta         inxGrafo idAresta CondRetEsp
* =adicionarorigem       inxGrafo idVertice CondRetEsp
* =removerorigem         inxGrafo idVertice CondRetEsp
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int inxGrafo  = -1 ,
          numLidos   = -1 ,
          CondRetEsp = -1  ;

      char idVertice;
      char idVertice2;

      char StringDado[ DIM_VALOR ];    

      VER_tppVertice novoVertice;

      TST_tpCondRet CondRet ;

      void * pDado ;

      char ** pValor;

      /* Testar criar Grafo */
        if ( strcmp( ComandoTeste , CRIAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , NAO_VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_CriarGrafo( &vtGRAFO[ inxGrafo ], DestruirValor );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar grafo."  ) ;

        } /* fim ativa: Testar criar Grafo */

      /* Testar destruir Grafo */      
        else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_DestruirGrafo( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir grafo."  ) ;

        } /* fim ativa: Testar destruir Grafo */

      /* Testar esvaziar Grafo */      
        else if ( strcmp( ComandoTeste , ESV_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || (ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_EsvaziarGrafo( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao esvaziar grafo."  ) ;

        } /* fim ativa: Testar esvaziar Grafo */

      /* Testar obter vertice corrente em Grafo */
        else if ( strcmp( ComandoTeste , CORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "isi" , &inxGrafo, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
            

            CondRet = GRA_ObterValorCorrente( vtGRAFO[ inxGrafo ], &novoVertice );

            pValor = (char**)malloc(sizeof(char));

            VER_ObterValor( novoVertice, pValor);

            return TST_CompararString( StringDado , *pValor ,
                     "Condicao de retorno errada ao obter corrente."  ) ;   

        } /* fim ativa: Testar obter vertice corrente em Grafo */

      /* Testar alterar vertice corrente em Grafo */
        else if ( strcmp( ComandoTeste , ALTCORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "isi" , &inxGrafo, StringDado, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            VER_CriarVertice( &novoVertice );

            VER_AtribuirValor( novoVertice, StringDado ) ;
            
            CondRet = GRA_AlterarValorCorrente( vtGRAFO[ inxGrafo ], novoVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao alterar corrente."  ) ;

        } /* fim ativa: Testar alterar vertice corrente em Grafo */

      /* Testar ir para vertice em Grafo */ 
        else if ( strcmp( ComandoTeste , IRVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ici" , &inxGrafo, &idVertice, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_IrParaVertice( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao ir para vertice."  ) ;

        } /* fim ativa: Testar ir para vertice em Grafo */

      /* Testar andar para vertice em Grafo */
        else if ( strcmp( ComandoTeste , ANDARVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ici" , &inxGrafo, &idVertice, &CondRetEsp ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_AndarParaVertice( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao andar para vertice."  ) ;

        } /* fim ativa: Testar andar para vertice em Grafo */

      /* Testar inserir vertice em Grafo */
        else if ( strcmp( ComandoTeste , INSVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "isci" , &inxGrafo, StringDado, &idVertice, &CondRetEsp ) ;

            if ( ( numLidos != 4 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            VER_CriarVertice( &novoVertice );

            VER_AtribuirValor( novoVertice, StringDado ) ;
            
            CondRet = GRA_InserirVertice( vtGRAFO[ inxGrafo ], novoVertice, idVertice );   

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice."  ) ;

        } /* fim ativa: Testar inserir vertice em Grafo */

      /* Testar excluir vertice corrente em Grafo */
        else if ( strcmp( ComandoTeste , EXCCORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_ExcluirVerticeCorrente( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir vertice corrente."  ) ;

        } /* fim ativa: Testar excluir vertice corrente em Grafo */

      /* Testar inserir aresta em Grafo */ 
        else if ( strcmp( ComandoTeste , INSAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "iccsi" , &inxGrafo, &idVertice, &idVertice2, StringDado, &CondRetEsp) ;

            if ( ( numLidos != 5 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_InserirAresta( vtGRAFO[ inxGrafo ], idVertice, idVertice2, StringDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir aresta."  ) ;

        } /* fim ativa: Testar inserir aresta em Grafo */

      /* Testar inserir aresta em origem no Grafo */
        else if ( strcmp( ComandoTeste , INSARO_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "icsi" , &inxGrafo, &idVertice, StringDado, &CondRetEsp) ;

            if ( ( numLidos != 4 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_InserirArestaOrigemCorrente( vtGRAFO[ inxGrafo ], idVertice, StringDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir aresta na origem corrente."  ) ;

        } /* fim ativa: Testar inserir aresta em origem no Grafo */

      /* Testar excluir aresta em Grafo */
        else if ( strcmp( ComandoTeste , EXCAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "isi" , &inxGrafo, StringDado, &CondRetEsp) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_ExcluirAresta( vtGRAFO[ inxGrafo ], StringDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir aresta."  ) ;

        } /* fim ativa: Testar excluir aresta em Grafo */

      /* Testar adicionar origem em Grafo */
        else if ( strcmp( ComandoTeste , ADDOR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ici" , &inxGrafo, &idVertice, &CondRetEsp) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_AdicionarOrigem( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao adicionar origem."  ) ;

        } /* fim ativa: Testar adicionar origem em Grafo */

      /* Testar remover origem em Grafo */
        else if ( strcmp( ComandoTeste , RMVOR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ici" , &inxGrafo, &idVertice, &CondRetEsp) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_RemoverOrigem( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao remover origem."  ) ;

        } /* fim ativa: Testar remover origem em Grafo */

   } /* Fim função: TLIS &Testar grafo */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TGRA -Validar indice de grafo
*
***********************************************************************/

   static int ValidarInxGrafo( int inxGrafo , int Modo ) {

      if ( ( inxGrafo <  0 )
        || ( inxGrafo >= DIM_VT_GRAFO ))
      {
         return FALSE ;
      } /* if */
         
      if ( Modo == VAZIO )
      {
         if ( vtGRAFO[ inxGrafo ] != 0 )
         {
            return FALSE ;
         } /* if */
      } else
      {
         if ( vtGRAFO[ inxGrafo ] == 0 )
         {
            return FALSE ;
         } /* if */
      } /* if */
         
      return TRUE ;

   } /* Fim função: TGRA -Validar indice de grafo */

/***********************************************************************
*
*  $FC Função: TGRA -Esvaziar valor vertice
*
***********************************************************************/

   static void DestruirValor( void * pValor) {
	   VER_EsvaziarVertice( (VER_tppVertice) pValor);
   }


/********** Fim do módulo de implementação: TGRA Teste de grafo genérico **********/

