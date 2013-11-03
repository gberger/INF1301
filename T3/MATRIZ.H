#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz quadrada
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e explorar matrizes quadradas.
*     Podem existir inúmeras matrizes em operação simultaneamente.
*     As matrizes possuem uma cabeça encapsulando o seu estado.
*     Cada elemento da matriz pode armazenar um valor genérico.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

#include "GRAFO.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tagMatriz * MAT_tppMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da matriz
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK ,
               /* Executou corretamente */

         MAT_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

		   MAT_CondRetTamanhoInvalido ,
			   /* Foi passado um tamanho invalido */

         MAT_CondRetDirecaoInvalida ,
               /* A direção que se quer mover é inválida */

         MAT_CondRetPosicaoInvalida ,
               /* A posição onde se quer ir é inválida */

         MAT_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Direcoes
*
*  $ED Descrição do tipo
*     Direcoes disponíveis para mover a célula corrente da matriz
*     Equivalem às direções da rosa dos ventos
*
***********************************************************************/
   typedef enum {

         MAT_N,
         MAT_L,
         MAT_S,
         MAT_O,

   } MAT_tpDirecao ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz de tamanho N x N.
*     O ponteiro para a nova matriz será fornecido no valor do ponteiro
*     de ponteiro para matriz.
*
*  $EP Parâmetros
*     $P ppMatriz - ponteiro para o ponteiro de matriz.
*     $P n        - tamanho da matriz
*     $P ExcluirValor - ponteiro para a função de destruição do valor.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetTamanhoInvalido
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * ppMatriz, int n, void ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, liberando o espaço ocupado
*     pela matriz.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_DestruirMatriz( MAT_tppMatriz pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Andar com a célula corrente.
*
*  $ED Descrição da função
*     Move a célula corrente da matriz, de acordo com a direcao fornecida.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P direcao - direcao para a qual mover.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*     MAT_CondRetDirecaoInvalida
*
***********************************************************************/

   MAT_tpCondRet MAT_AndarCorrente( MAT_tppMatriz pMatriz, MAT_tpDirecao direcao ) ;


/***********************************************************************
*
*  $FC Função: MAT Definir célula corrente.
*
*  $ED Descrição da função
*     Define a célula corrente da matriz através de suas coordenadas.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P i - coordenada horizontal.
*     $P j - coordenada vertical.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*     MAT_CondRetPosicaoInvalida
*
***********************************************************************/

   MAT_tpCondRet MAT_DefinirCorrente( MAT_tppMatriz pMatriz, int i, int j ) ;


/***********************************************************************
*
*  $FC Função: MAT Atribuir valor
*
*  $ED Descrição da função
*     Atribui valor à célula corrente da matriz.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P pLista  - ponteiro para o valor a ser atribuído
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_AtribuirValorCorrente( MAT_tppMatriz pMatriz, void * pValor ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P ppValor - ponteiro para o ponteiro do valor a ser obtido
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorrente( MAT_tppMatriz pMatriz, void ** ppValor ) ;

#undef Matriz_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
