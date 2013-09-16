/***************************************************************************
*  $MCI Módulo de implementação: Módulo de teste específico
*
*  Arquivo gerado:              TESTMAT.C
*  Letras identificadoras:      TMAT
*
*  Projeto: T1 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Este módulo contém as funções específicas para o teste do
*     módulo matriz.
*
*  $EIU Interface com o usuário pessoa
*     Comandos de teste específicos para testar o módulo matriz
*     Todos os comandos também recebem como último parâmetro a codição
*     de retorno esperada.
*
*     =criar  <int inx, int n>
*                   - chama a função MAT_CriarMatriz
*                     cria uma matriz no índice inx, de tamanho n x n
*     =andar <int inx, int dir>
*                   - chama a função MAT_AndarCorrente
*                     anda com a matriz inx na direção dir
*     =atrlis <int inx, str valor>
*                   - chama a função MAT_AtribuirValorCorrente
*                     cria uma nova lista representando a string
*                     atribui a lista a celula corrente da matriz inx
*     =obterlis <int inx, str valor>
*                   - chama a função MAT_ObterValorCorrente
*                     compara a representação em string da lista obtida
*                     com a lista passada
*     =destruir <int inx>
*                   - chama a função MAT_DestruirMatriz
*                     destrui a matirz inx
*     =esvaziar <int inx>
*                   - chama a função MAT_EsvaziarMatriz
*                   - esvazia a matriz inx
*
*
***************************************************************************/

#include    <string.h>
#include    <malloc.h>
#include    <stdio.h>

#include    "TST_ESPC.H"

#include    "GENERICO.H"
#include    "LERPARM.H"

#include    "MATRIZ.H"
#include    "LISTA.H"

/* Tabela dos nomes dos comandos de teste específicos */

#define     CRIAR_MAT_CMD       "=criar"
#define     ANDAR_DIR_CMD       "=andar"
#define     ATRIBUIR_LIS_CMD    "=atrlis"
#define     OBTER_LIS_CMD       "=obterlis"
#define     DESTROI_CMD         "=destruir"
#define     ESVAZIA_CMD         "=esvaziar"

#define DIM_VT_MATRIZES 10
#define DIM_STR 128

MAT_tppMatriz vtMatrizes[ DIM_VT_MATRIZES ] = {0};

/***** Protótipos das funções encapuladas no módulo *****/
      LIS_tppLista criarListaAPartirDeString( char * str );
	  char * obterStringAPartirDeLista( LIS_tppLista lista );
/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*
*  $FC Função: TMAT Efetuar operações de teste específicas para matriz quadrada
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

	  char stringDada [ DIM_STR ] = {0};
	  char *stringObtida;

      LIS_tppLista listaAuxiliar ;     

      TST_tpCondRet CondRetObtido ;

      /* Testar MAT Criar Matriz */

         if ( strcmp( ComandoTeste , CRIAR_MAT_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &indexMat, &dimMatriz, &CondRetEsperada ) ;
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_CriarMatriz( &(vtMatrizes[ indexMat ]), dimMatriz ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                     "Condicao de retorno errada ao criar matriz." ) ;

         } /* fim ativa: Testar MAT Criar Matriz */

      /* Testar MAT andar na matriz */

         else if ( strcmp( ComandoTeste , ANDAR_DIR_CMD ) == 0 )
         {

            numLidos = LER_LerParametros( "iii" ,
                               &indexMat, &direcao , &CondRetEsperada ) ;
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_AndarCorrente( vtMatrizes[indexMat], (MAT_tpDirecao) direcao ) ;

            return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao percorrer a matriz." );

         } /* fim ativa: Testar MAT andar na matriz */

      /* Testar MAT atribuir lista a célula corrente */

         else if ( strcmp( ComandoTeste , ATRIBUIR_LIS_CMD ) == 0 )
         {
            numLidos = LER_LerParametros( "isi" ,
                              &indexMat, stringDada, &CondRetEsperada ) ;
            if ( numLidos != 3 )
            {
               return TST_CondRetParm ;
            } /* if */
			
			listaAuxiliar = criarListaAPartirDeString(stringDada);

            CondRetObtido = MAT_AtribuirValorCorrente( vtMatrizes[ indexMat ], listaAuxiliar ) ;
			
			return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                "Retorno errado ao inserir lista no elemento corrente." );
	     } /* fim ativa: Testar MAT atribuir lista a célula corrente */

      /* Testar MAT obter valor da célula corrente */  
         else if ( strcmp( ComandoTeste , OBTER_LIS_CMD ) == 0 )
         {
			int pEsp;
			numLidos = LER_LerParametros( "isii" ,
                              &indexMat, stringDada, &pEsp, &CondRetEsperada ) ;
            if ( numLidos != 4 )
            {
               return TST_CondRetParm ;
            } /* if */

            CondRetObtido = MAT_ObterValorCorrente( vtMatrizes[ indexMat ], &listaAuxiliar ) ;
			
			if( CondRetObtido != CondRetEsperada || CondRetObtido == MAT_CondRetPonteiroNulo ){
				return TST_CompararInt( CondRetEsperada , CondRetObtido ,
                                    "Retorno errado ao obter lista no elemento corrente." );
			}

			if ( pEsp == 0 )
            {
               return TST_CompararPonteiroNulo( 0 , listaAuxiliar ,
                         "Valor não deveria existir." ) ;
            } /* if */

			stringObtida = obterStringAPartirDeLista( listaAuxiliar );

			return TST_CompararString(stringDada, stringObtida, 
									"Representação em string da lista obtida diferente do esperado."); 
         } /* fim ativa: Testar MAT obeter valor da célula corrente */

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
         else if ( strcmp( ComandoTeste , ESVAZIA_CMD ) == 0 )
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

/*****  Código das funções encapsuladas no módulo *****/
   LIS_tppLista criarListaAPartirDeString( char * str ){
	   int i, len = strlen(str);
	   LIS_tppLista lista = LIS_CriarLista();

	   for( i = 0 ; i <= len ; i++) {
		   LIS_InserirElementoApos( lista, str[i] );
		   LIS_IrFinalLista( lista );
	   }
	   
	   return lista;
   }

   char * obterStringAPartirDeLista( LIS_tppLista lista ){
	   int numElementos = LIS_ObterNumElem( lista );
	   char * str;
	   int i = 0;
	   
	   if( numElementos <= 0 ){
		   return "\0";
       }

	   LIS_IrInicioLista( lista );
	   str = (char*)malloc(sizeof(char)*numElementos);
	   
	   do {
		   str[i++] = LIS_ObterValor( lista );
	   } while ( LIS_AvancarElementoCorrente(lista, 1) != LIS_CondRetFimLista );

	   return str;
   }

/********** Fim do módulo de implementação: Módulo de teste específico **********/

