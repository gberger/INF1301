/***************************************************************************
*  $MCI Módulo de implementação: Módulo matriz quadrada
*
*  Arquivo gerado:              MATRIZ.C
*  Letras identificadoras:      MAT
*
*  Projeto: T1 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>

#include "LISTA.H"

#define MATRIZ_OWN
#include "MATRIZ.H"
#undef MATRIZ_OWN

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da célula da matriz
*
*  $ED Descrição do tipo
*     Descreve a organização da célula
*
***********************************************************************/

   typedef struct tagCelulaMatriz {

         LIS_tppLista pValor ;
               /* Ponteiro para a lista (valor) */

         struct tagCelulaMatriz * vpVizinhos[8] ;
               /* Vetor de ponteiros para os vizinhos
               *
               *$EED Assertivas estruturais
               *   é NULL se não existir tal vizinho */

   } tpCelulaMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Descritor da cabeça de uma matriz
*
*
*  $ED Descrição do tipo
*     A cabeça da matriz é o ponto de acesso para uma determinada matriz.
*     Por intermédio da referência para a célula corrente pode-se navegar
*     pela matriz.
*
***********************************************************************/

   typedef struct MAT_tagMatriz {

         tpNoArvore * pCelulaCorr ;
               /* Ponteiro para a célula corrente da matriz */

   } MAT_tpMatriz ;



/***** Protótipos das funções encapuladas no módulo *****/

   static tpCelulaMatriz * obterPrimeiraCelula( MAT_tppMatriz pMatriz ) ;

/*****  Código das funções exportadas pelo módulo  *****/

/***************************************************************************
*
*  Função: MAT Criar matriz
*  ****/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * ppMatriz, int n )
   {
      /* Criar cabeça da matriz */
      *ppMatriz = ( MAT_tagMatriz* ) malloc( sizeof(MAT_tagMatriz) );
      if(*ppMatriz == NULL)
      {
         return MAT_CondRetFaltouMemoria;
      }

      tpCelulaMatriz **matrizAuxiliar, *elementoCorrente;
      int linhaCorrente, colunaCorrente;

      /* Criar estrutura da matriz a partir de um vetor bidimensional padrão */
      matrizAuxiliar = ( MAT_tagMatriz** ) malloc( n * sizeof( MAT_tagMatriz* )) ;
      if( matrizAuxiliar == NULL)
      {
         free(*ppMatriz);
         return MAT_CondRetFaltouMemoria;
      } /* if */

      for( linhaCorrente = 0; linhaCorrente < n; linhaCorrente++ )
      {
         matrizAuxiliar[linhaCorrente] = ( MAT_tagMatriz* ) malloc( n * sizeof( MAT_tagMatriz )) ;
         if( matrizAuxiliar[linhaCorrente] == NULL)
         {
            linhaCorrente--;
            while(linhaCorrente != 0)
            {
               free(matrizAuxiliar[linhaCorrente]);
            } /* while */
            free(matrizAuxiliar);
            free(*ppMatriz);
            return MAT_CondRetFaltouMemoria;
         } /* if */
      } /* for */

      /* Encadear células da matriz criada e criar lista em cada célula */
      for( linhaCorrente = 0; linhaCorrente < n; linhaCorrente++ )
      {
         for( colunaCorrente = 0; colunaCorrente < n; colunaCorrente++ )
         {
            elementoCorrente = &matrizAuxiliar[linhaCorrente][colunaCorrente];

            elementoCorrente->vpVizinhos[ MAT_N ] = (linhaCorrente == 0) ? NULL : &matrizAuxiliar[ linhaCorrente - 1 ][ colunaCorrente ];
            elementoCorrente->vpVizinhos[ MAT_S ] = (linhaCorrente == n) ? NULL : &matrizAuxiliar[ linhaCorrente + 1 ][ colunaCorrente ];
            elementoCorrente->vpVizinhos[ MAT_O ] = (colunaCorrente == 0) ? NULL : &matrizAuxiliar[ linhaCorrente ][ colunaCorrente-1 ];
            elementoCorrente->vpVizinhos[ MAT_L ] = (colunaCorrente == n) ? NULL : &matrizAuxiliar[ linhaCorrente ][ colunaCorrente+1 ];

            elementoCorrente->vpVizinhos[ MAT_NO ] = (colunaCorrente == 0 || linhaCorrente == 0) ? NULL : &matrizAuxiliar[ linhaCorrente - 1 ][ colunaCorrente - 1 ];
            elementoCorrente->vpVizinhos[ MAT_SE ] = (colunaCorrente == n || linhaCorrente == n) ? NULL : &matrizAuxiliar[ linhaCorrente + 1 ][ colunaCorrente + 1 ];
            elementoCorrente->vpVizinhos[ MAT_NE ] = (colunaCorrente == n || linhaCorrente == 0) ? NULL : &matrizAuxiliar[ linhaCorrente - 1 ][ colunaCorrente + 1 ];
            elementoCorrente->vpVizinhos[ MAT_SO ] = (colunaCorrente == 0 || linhaCorrente == n) ? NULL : &matrizAuxiliar[ linhaCorrente + 1 ][ colunaCorrente - 1 ];
         } /* for */
      } /* for */

      /* Definir célula corrente inicial */
      *ppMatriz->pCelulaCorr = &matrizAuxiliar[0][0];

      /* Eliminar estrutura auxiliar */
      free(matrizAuxiliar);

      return MAT_CondRetOK;

   } /* Fim função: MAT Criar matriz */

/***********************************************************************
*
*  $FC Função: MAT Esvaziar
*  ****/

   MAT_tpCondRet MAT_EsvaziarMatriz( MAT_tppMatriz pMatriz )
   {
      if(pMatriz == NULL)
      {
         return MAT_CondRetPonteiroNulo;
      } /* if */

      tpCelulaMatriz *elementoCorrente, *primeiroDaLinha;

      elementoCorrente = obterPrimeiraCelula( pMatriz );

      /* Destruir conteúdo das celulas */
      primeiroDaLinha = elementoCorrente;
      while(primeiroDaLinha != NULL)
      {
         elementoCorrente = primeiroDaLinha;
         while(elementoCorrente != NULL)
         {
            if(elementoCorrente->pValor != NULL)
            {
               LIS_DestruirLista(elementoCorrente->pValor);
               elementoCorrente->pValor = NULL;
            } /* if */
         } /* while */

         primeiroDaLinha = primeiroDaLinha->vpVizinhos[MAT_S];
      } /* while */

      return MAT_CondRetOK;
   } /* Fim Função: MAT Esvaziar */

/***************************************************************************
*
*  Função: MAT Destruir matriz
*  ****/
   
   MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz pMatriz )
   {
      if(pMatriz == NULL)
      {
         return MAT_CondRetPonteiroNulo;
      } /* if */

      tpCelulaMatriz *elementoCorrente;

      MAT_EsvaziarMatriz( pMatriz );

      elementoCorrente = obterPrimeiraCelula( pMatriz );

      /* Destruir linhas */
      while(elementoCorrente != NULL)
      {
         elementoCorrente = elementoCorrente->vpVizinhos[MAT_S];
         free(elementoCorrente->vpVizinhos[MAT_N]);
      } /* while */

      /* Destruir cabeça da matriz */
      free( pMatriz );

      return MAT_CondRetOK;

   } /* Fim função: MAT Destruir matriz */

/***********************************************************************
*
*  $FC Função: MAT Mover célula corrente
*  ****/

   MAT_tpCondRet MAT_MoverCorrente( MAT_tppMatriz pMatriz, MAT_tpDirecao direcao )
   {
      if(pMatriz == NULL)
      {
         return MAT_CondRetPonteiroNulo;
      } /* if */

      if(pMatriz->pCelulaCorr->vpVizinhos[direcao] == NULL)
      {
         return MAT_CondRetDirecaoInvalida;
      } /* if */
      else
      {
         pMatriz->pCelulaCorr = pMatriz->pCelulaCorr->vpVizinhos[direcao];
         return MAT_CondRetOK;
      } /* else */

   } /* Fim Função: MAT Mover célula corrente */

/***********************************************************************
*
*  $FC Função: MAT Atribuir valor
*  ****/

   MAT_tpCondRet MAT_AtribuirValorCorrente( MAT_tppMatriz pMatriz, LIS_tppLista pLista )
   {
      if(pMatriz == NULL)
      {
         return MAT_CondRetPonteiroNulo;
      } /* if */

      if(pMatriz->pCelulaCorr->pValor != NULL)
      {
         LIS_DestruirLista( pMatriz->pCelulaCorr->pValor );
      } /* if */

      pMatriz->pCelulaCorr->pValor = pLista;

      return MAT_CondRetOK;

   } /* Fim Função: MAT Atribuir valor */

/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*  ****/

   MAT_tpCondRet MAT_ObterValorCorrente( MAT_tppMatriz pMatriz, LIS_tppLista * ppLista )
   {
      if(pMatriz == NULL)
      {
         return MAT_CondRetPonteiroNulo;
      } /* if */

      *ppLista = pMatriz->pCelulaCorr->pValor;

      return MAT_CondRetOK;

   } /* Fim Função: MAT Obter valor corrente */


/*****  Código das funções encapsuladas no módulo  *****/


/***********************************************************************
*
*  $FC Função: MAT Obter primeira célula
*
*  $EAE Assertivas de entradas esperadas
*     pMatriz != NULL
*
*  $FV Valor retornado
*     Ponteiro para a primeira célula da matriz.
*
***********************************************************************/

   tpCelulaMatriz * obterPrimeiraCelula( MAT_tppMatriz pMatriz )
   {
      tpCelulaMatriz *elementoCorrente;

      elementoCorrente = pMatriz->pCelulaCorr;

      /* Obter primeiro elemento da matriz */
      while(elementoCorrente->vpVizinhos[ MAT_O ] != NULL)
      {
         elementoCorrente = elementoCorrente->vpVizinhos[ MAT_O ];
      } /* while */

      while(elementoCorrente->vpVizinhos[ MAT_N ] != NULL)
      {
         elementoCorrente = elementoCorrente->vpVizinhos[ MAT_N ];
      } /* while */

      return elementoCorrente;

   } /* Fim Função: MAT Obter primeira célula */


/********** Fim do módulo de implementação: Módulo matriz quadrada **********/

