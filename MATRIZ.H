#if ! defined( MATRIZ_ )
#define MATRIZ_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo matriz quadrada
*
*  Arquivo gerado:              MATRIZ.H
*  Letras identificadoras:      MAT
*
*  Projeto: T1 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e explorar matrizes quadradas.
*     Podem existir inúmeras matrizes em operação simultaneamente.
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
*  $ED Descrição do tipo
*     Condições de retorno das funções da matriz
*
***********************************************************************/

   typedef enum {

         MAT_CondRetOK ,
               /* Executou corretamente */

         MAT_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         MAT_CondRetDirecaoInvalida ,
               /* A direção que se quer mover é inválida */

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
         MAT_NE,
         MAT_L,
         MAT_SE,
         MAT_S,
         MAT_SO,
         MAT_O,
         MAT_NO

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
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetFaltouMemoria
*
***********************************************************************/

   MAT_tpCondRet MAT_CriarMatriz( MAT_tppMatriz * ppMatriz, int n ) ;


/***********************************************************************
*
*  $FC Função: MAT Destruir matriz
*
*  $ED Descrição da função
*     Destrói o corpo e a cabeça da matriz, liberando o espaço ocupado
*     pela matriz e pelas listas.
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
*  $FC Função: MAT Esvaziar
*
*  $ED Descrição da função
*     Esvazia a matriz, isso é, libera todas as listas contidas nas
*     céluals da matriz.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_EsvaziarMatriz( MAT_tppMatriz pMatriz ) ;


/***********************************************************************
*
*  $FC Função: MAT Mover célula corrente.
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

   MAT_tpCondRet MAT_MoverCorrente( MAT_tppMatriz pMatriz, MAT_tpDirecao direcao ) ;


/***********************************************************************
*
*  $FC Função: MAT Atribuir valor
*
*  $ED Descrição da função
*     Atribui a lista à célula corrente da matriz.
*
*  $EP Parâmetros
*     $P pMatriz - ponteiro para a matriz.
*     $P pLista  - ponteiro para a lista a ser atribuída
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_AtribuirValorCorrente( MAT_tppMatriz pMatriz, LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: MAT Obter valor corrente
*
*  $EP Parâmetros
*     $P matriz - ponteiro para a matriz.
*
*  $FV Valor retornado
*     MAT_CondRetOK
*     MAT_CondRetPonteiroNulo
*
***********************************************************************/

   MAT_tpCondRet MAT_ObterValorCorrente( MAT_tppMatriz matriz ) ;

#undef Matriz_EXT

/********** Fim do módulo de definição: Módulo matriz **********/

#else
#endif
