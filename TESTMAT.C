/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTARV.C
*  Letras identificadoras:      TARV
*
*  Nome da base de software:    Exemplo de teste automatizado
*  Arquivo da base de software: D:\AUTOTEST\PROJETOS\SIMPLES.BSW
*
*  Projeto: Disciplinas INF 1628 / 1301
*  Gestor:  DI/PUC-Rio
*  Autores: avs - Arndt von Staa
*
*  $HA Histórico de evolução:
*     Versão  Autor    Data     Observações
*       3.00   avs   28/02/2003 Uniformização da interface das funções e
*                               de todas as condições de retorno.
*       2.00   avs   03/08/2002 Eliminação de código duplicado, reestruturação
*       1.00   avs   15/08/2001 Início do desenvolvimento
*
*  $ED Descrição do módulo
*     Este mÇodulo contém as funções específicas para o teste do
*     módulo árvore. Ilustra como redigir um interpretador de comandos
*     de teste específicos utilizando o arcabouço de teste para C.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo árvore:
*
*     =criar        - chama a função ARV_CriarArvore( )
*     =insdir <Char>
*                   - chama a função ARV_InserirDireita( <Char> )
*                     Obs. notação: <Char>  é o valor do parâmetro
*                     que se encontra no comando de teste.
*
*     "=insesq" <Char>
*                   - chama a função ARV_InserirEsquerda( <Char> )
*     "=irpai"      - chama a função ARV_IrPai( )
*     "=iresq"      - chama a função ARV_IrEsquerda( )
*     "=irdir"      - chama a função ARV_IrDireita( )
*     "=obter" <Char>
*                   - chama a função ARV_ObterValorCorr( ) e compara
*                     o valor retornado com o valor <Char>
*     "=destroi"    - chama a função ARV_DestruirArvore( )
*
***************************************************************************/

#include    <string.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "MATRIZ.H"
#include    "LISTA.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_MAT_CMD       "=criar"
#define     ANDAR_DIR           "=andar"      
#define     INS_LIS_CMD         "=inslis"
#define     OBTER_VAL_CMD       "=obter"
#define     DESTROI_CMD         "=destruir"

#define DIM_VI_MATRIZES 10

MAT_tppMatriz * vtMatrizes[ DIM_VT_MATRIZES ];

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*
*  $FC Função: TARV Efetuar operações de teste específicas para árvore
*
*  $ED Descrição da função
*     Efetua os diversos comandos de teste específicos para o módulo
*     árvore sendo testado.
*
*  $EP Parâmetros
*     $P ComandoTeste - String contendo o comando
*
*  $FV Valor retornado
*     Ver TST_tpCondRet definido em TST_ESPC.H
*
***********************************************************************/

   TST_tpCondRet TST_EfetuarComando( char * ComandoTeste )
   {

      int  numLidos = -1, 
           indexMat = -1,
           dimMatriz = -1,
           CondRetEsperada = -1,
           direcao = -1 ;

      LIS_tppLista listaAuxiliar ;     

      TST_tpCondRet CondRetObtido ;

      /* Testar MAT Criar Matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &dimMatriz, &indexMat, &CondRetEsperada ) ;
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarArvore( vtMatrizes[ indexMat ], dimMatriz ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                     "Condicao de retorno errada ao criar matriz." ) ;

         } /* fim ativa: Testar MAT Criar Matriz */

      /* Testar MAT andar na matriz */

         else if ( strcmp( ComandoTeste , ANDAR_DIR ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &indexMat, &direcao , &CondRetEsperada ) ;
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_MoverCorrente( vtMatrizes[indexMat], direcao ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao percorrer a matriz." );

         } /* fim ativa: Testar MAT andar na matriz */

      /* Testar MAT inserir lista na posição */

         else if ( strcmp( ComandoTeste , INS_LIS_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                              &indexMat, &CondRetEsperada ) ;
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_AtribuirValorCorrente( vtMatrizes[ indexMat ], LIS_CriarLista() ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao inserir lista no elemento corrente." );

         } /* fim ativa: Testar MAT inserir lista na posição */

      /* Testar MAT obeter valor no elemento corrente */  
         else if ( strcmp( ComandoTeste , OBTER_VAL_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                              &indexMat, &CondRetEsperada ) ;
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValorCorrente( vtMatrizes[ indexMat ], &listaAuxiliar ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter lista no elemento corrente." );

         } /* fim ativa: Testar MAT obeter valor no elemento corrente */

      /* Testar MAT destruir matriz */  
         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                              &indexMat, &CondRetEsperada ) ;
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_DestruirMatriz( vtMatrizes[ indexMat ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao destruir matriz" );

         } /* fim ativa: Testar MAT destruir matriz */

      /* Testar MAT esvaziar matriz */  
         else if ( strcmp( ComandoTeste , DESTROI_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "ii" ,
                              &indexMat, &CondRetEsperada ) ;
            if ( numLidos != 2 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_EsvaziarMatriz( vtMatrizes[ indexMat ] ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao esvaziar matriz" );

         } /* fim ativa: MAT esvaziar matriz */

      return TST_CondRetNaoConhec ;

   } /* Fim função: TARV Efetuar operações de teste específicas para árvore */

/********** Fim do módulo de implementação: Módulo de teste específico **********/

