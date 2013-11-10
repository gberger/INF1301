#if ! defined( VERIFICADOR_ )
#define VERIFICADOR_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo verificador de cheque-mate
*  Arquivo gerado:              VERIFICADOR.H
*  Letras identificadoras:      VER
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa as funções para testar se um tabuleiro está
*     em caso de cheque-mate. O módulo utiliza um algoritimo que
*     verifica se o jogador está em cheque e, caso positivo, se 
*     existe algum movimento possível que o retire deste estado.
*     Caso não exista, é um cheque-mate.
*
***************************************************************************/
 
#if defined( VERIFICADOR_OWN )
   #define VERIFICADOR_EXT
#else
   #define VERIFICADOR_EXT extern
#endif

#include "TABULEIRO.H"

/***** Declarações exportadas pelo módulo *****/


/***********************************************************************
*
*  $TC Tipo de dados: VER Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do verificador
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK ,
               /* Executou corretamente */

         VER_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         VER_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VER Verificar Cheque-Mate
*
*  $ED Descrição da função
*     Verifica se um tabuleiro está em condição de cheque-mate.
*    
*  $EP Parâmetros
*     $P pTabuleiro - ponteiro para o tabuleiro.
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*
***********************************************************************/

   VER_tpCondRet VER_VerificaCheque( TAB_tppTabuleiro pTabuleiro ) ;

#undef VERIFICADOR_EXT

/********** Fim do módulo de definição: Módulo verificador de cheque-mate **********/

#else
#endif
