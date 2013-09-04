#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*
*  Projeto: T1 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e explorar matrizes.
*     Podem existir n matrizes em operação simultaneamente.
*     As matrizes possuem uma cabeça encapsulando o seu estado.
*     Cada elemento da matriz pode armazenar uma lista de caracteres.
*
***************************************************************************/
 
#if defined( MATRIZ_OWN )
   #define MATRIZ_EXT
#else
   #define MATRIZ_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma matriz */

typedef struct MAT_tagMatriz * MAT_tppMatriz ;

/***********************************************************************
*
*  $TC Tipo de dados: MAT Condicoes de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da matriz
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK = 0 ,
               /* Executou correto */

         MAT_CondRetFaltouMemoria = 8
               /* Faltou memória ao alocar dados */

   } MAT_tpCondRet ;


/***********************************************************************
*
*  $FC Função: MAT Criar matriz
*
*  $ED Descrição da função
*     Cria uma nova matriz vazia.
*     Caso já exista uma matriz, esta será destruída.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( void ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, anulando a matriz corrente.
*     Faz nada caso a matriz corrente não exista.
*
***********************************************************************/

   void MAT_DestruirMatriz( void ) ;


/***********************************************************************
*
*  $FC Função: MAT Adicionar filho à esquerda
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoEhFolha     - caso não seja folha para a esquerda
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirEsquerda( char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: MAT Adicionar filho à direita
*
*  $EP Parâmetros
*     $P ValorParm - valor a ser inserido no novo nó
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetErroEstrutura
*     MAT_CondRetFaltouMemoria
*     MAT_CondRetNaoEhFolha     - caso não seja folha para a direita
*
***********************************************************************/

   MAT_tpCondRet MAT_InserirDireita( char ValorParm ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó pai
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNoEhRaiz
*
***********************************************************************/

   MAT_tpCondRet MAT_IrPai( void ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à esquerda
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à esquerda
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoEsquerda( void ) ;


/***********************************************************************
*
*  $FC Função: MAT Ir para nó à direita
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*     MAT_CondRetNaoPossuiFilho   - nó corrente não possui filho à direita
*
***********************************************************************/

   MAT_tpCondRet MAT_IrNoDireita( void ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P ValorParm - é o parâmetro que receberá o valor contido no nó.
*                    Este parâmetro é passado por referência.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetMatrizNaoExiste
*     MAT_CondRetMatrizVazia
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorr( char * ValorParm ) ;

#undef Matriz_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
