/***************************************************************************
*  $MCI Módulo de implementação: TGRA Teste de grafo genérico
*
*  Arquivo gerado:              TestGRA.c
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

static const char CRAIR_GRAFO_CMD         [ ] = "=criargrafo"           ;
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

/***** Protótipos das funções encapuladas no módulo *****/

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
*     =criarvertice               InxGrafo
*     =destruirvertice            InxGrafo
*     =esvaziarvertice            InxGrafo
*     =atribuirvalor              InxGrafo  string  CondRetEsp
*     =obtervalor                 InxGrafo  string  CondRetEsp
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

      TST_tpCondRet CondRet ;

      void * pDado ;

        if ( strcmp( ComandoTeste , CRAIR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , NAO_VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_CriarGrafo( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao criar grafo."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , DESTRUIR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_DestruirGrafo( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao destruir grafo."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , ESV_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || (ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_EsvaziarGrafo( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao esvaziar grafo."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , CORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo, &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_ObterValorCorrente( vtGRAFO[ inxGrafo ], &pDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao obter corrente."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , ALTCORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp ) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_AlterarValorCorrente( vtGRAFO[ inxGrafo ], &pDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao alterar corrente."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , IRVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "iic" , &inxGrafo,  &CondRetEsp, &idVertice ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_IrParaVertice( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao ir para vertice."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , ANDARVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "iic" , &inxGrafo,  &CondRetEsp, &idVertice ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_AndarParaVertice( vtGRAFO[ inxGrafo ], idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao andar para vertice."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , INSVER_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "iic" , &inxGrafo,  &CondRetEsp, &idVertice ) ;

            if ( ( numLidos != 3 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_InserirVertice( vtGRAFO[ inxGrafo ], pDado, idVertice );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir vertice."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , EXCCORR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "ii" , &inxGrafo,  &CondRetEsp) ;

            if ( ( numLidos != 2 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_ExcluirVerticeCorrente( vtGRAFO[ inxGrafo ] );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao excluir vertice corrente."  ) ;

        } /* fim ativa: Testar criação de Grafo */

        else if ( strcmp( ComandoTeste , INSAR_GRAFO_CMD  ) == 0 ) {

            numLidos = LER_LerParametros( "iiccs" , &inxGrafo,  &CondRetEsp, &idVertice, &idVertice2, StringDado) ;

            if ( ( numLidos != 5 ) || ( ValidarInxGrafo( inxGrafo , VAZIO ) ) )
            {
               return TST_CondRetParm ;
            } /* if */
           
            CondRet = GRA_InserirAresta( vtGRAFO[ inxGrafo ], idVertice, idVertice2, StringDado );

            return TST_CompararInt( CondRetEsp , CondRet ,
                     "Condicao de retorno errada ao inserir aresta."  ) ;

        } /* fim ativa: Testar criação de Grafo */

   } /* Fim função: TLIS &Testar vertice */


/*****  Código das funções encapsuladas no módulo  *****/

/***********************************************************************
*
*  $FC Função: TLIS -Validar indice de vértice
*
***********************************************************************/

   int ValidarInxGrafo( int inxGrafo , int Modo ) {

      if ( ( inxGrafo <  0 )
        || ( inxGrafo >= DIM_VT_VERTICE ))
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

   } /* Fim função: TLIS -Validar indice de vértice */


/********** Fim do módulo de implementação: TVER Teste vértice de grafo genérico **********/

