#if ! defined( CLASSE_PECA_ )
#define CLASSE_PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo classe de peça de xadrez
*
*  Arquivo gerado:              CLASSE_PECA.H
*  Letras identificadoras:      CPC
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e manipular classes (tipos) de peças 
*    de xadrez.
*
***************************************************************************/
 
#if defined( CLASSE_PECA_OWN )
   #define CLASSE_PECA_EXT
#else
   #define CLASSE_PECA_EXT extern
#endif

#include "LISA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma classe_peca */

typedef struct CPC_tagClassePeca * CPC_tppClassePeca ;

/***********************************************************************
*
*  $TC Tipo de dados: CPC Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da classe_peca
*
***********************************************************************/

   typedef enum {

         CPC_CondRetOK ,
               /* Executou corretamente */

         CPC_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         CPC_CondRetArgumentosInvalidos ,
               /* Foram passados valores inválidos para argumentos.
                  Por exemplo, índice de movimento inválido ou movimento
                  fora de -7 a 7. */

         CPC_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } CPC_tpCondRet ;


/***********************************************************************
*
*  $FC Função: CPC Criar classe de peça
*
*  $ED Descrição da função
*     Cria um classe de peça de xadrez
*     O ponteiro para a classe criada será fornecido no valor do ponteiro
*     de ponteiro para classe de peça.
*
*  $EP Parâmetros
*     $P ppClassePeca - ponteiro para ponteiro de classe de pela
*     $P nome - string contendo o nome da classe de peça (por exemplo, "Torre")
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetFaltouMemoria
*
***********************************************************************/

   CPC_tpCondRet CPC_CriarClassePeca( CPC_tppClassePeca * ppClassePeca , char * nome ) ;


/***********************************************************************
*
*  $FC Função: CPC Destruir classe de peça
*
*  $ED Descrição da função
*     Destrói a classe de peça, liberando o espaço alocado.
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para a classe de peça a ser destruída
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

   CPC_tpCondRet CPC_DestruirClassePeca( CPC_tppClassePeca pClassePeca ) ;


/***********************************************************************
*
*  $FC Função: CPC Adicionar movimento a classe de peça
*
*  $ED Descrição da função
*     Obtém o nome da classe de peça passada, escrevendo no
*     ponteiro para string dado.
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para a classe de peça
*     $P movX - inteiro de -7 a 7 contendo o valor horizontal do movimento
*     $P movY - inteiro de -7 a 7 contendo o valor vertical do movimento
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetArgumentosInvalidos
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

   CPC_tpCondRet CPC_AdicionarMovimento( CPC_tppClassePeca pClassePeca , int movX , int movY ) ;


/***********************************************************************
*
*  $FC Função: CPC Obter número de movimentos de classe de peça
*
*  $ED Descrição da função
*     Obtém o número de movimentos distintos que a peça possui.
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para a classe de peça
*     $P pNumMovimentos - ponteiro que será modificado para conter o 
*           número de movimentos da classe de peça dada
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

   CPC_tpCondRet CPC_ObterNumeroMovimentos( CPC_tppClassePeca pClassePeca , int * numMovimentos ) ;


/***********************************************************************
*
*  $FC Função: CPC Obter movimento de classe de peça
*
*  $ED Descrição da função
*     Obtém os componentes do movimento com dado índice
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para a classe de peça
*     $P idxMovimento - índice do movimento, inteiro de 0 até (numMovimentos - 1)
*     $P pMovX - ponteiro para inteiro que conterá a componente horizontal do movimento
*     $P pMovY - ponteiro para inteiro que conterá a componente vertical do movimento
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetArgumentosInvalidos
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

   CPC_tpCondRet CPC_ObterMovimento( CPC_tppClassePeca pClassePeca , int idxMovimento , int * pMovX , int * pMovY ) ;


/***********************************************************************
*
*  $FC Função: CPC Obter nome de classe de peça
*
*  $ED Descrição da função
*     Obtém o nome da classe de peça dada.
*
*  $EP Parâmetros
*     $P pClassePeca - ponteiro para a classe de peça
*     $P pNome - ponteiro para string que conterá o nome
*
*  $FV Valor retornado
*     CPC_CondRetOK
*     CPC_CondRetPonteiroNulo
*
***********************************************************************/

   CPC_tpCondRet CPC_ObterNome( CPC_tppClassePeca pClassePeca , char ** pNome ) ;


#undef CLASSE_PECA_EXT

/********** Fim do módulo de definição: Módulo classe de peça de xadrez **********/

#else
#endif
