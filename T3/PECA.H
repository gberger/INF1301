#if ! defined( PECA_ )
#define PECA_
/***************************************************************************
*
*  $MCD Módulo de definição: Módulo peça de xadrez
*
*  Arquivo gerado:              PECA.H
*  Letras identificadoras:      PEC
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e manipular peças de xadrez. 
*
***************************************************************************/
 
#if defined( PECA_OWN )
   #define PECA_EXT
#else
   #define PECA_EXT extern
#endif

#include "CLASSE_PECA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma peça */

typedef struct PEC_tagPeca * PEC_tppPeca ;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da classe_peca
*
***********************************************************************/

   typedef enum {

         PEC_CondRetOK ,
               /* Executou corretamente */

         PEC_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */

         PEC_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } PEC_tpCondRet ;

/***********************************************************************
*
*  $TC Tipo de dados: PEC Jogadores
*
*  $ED Descrição do tipo
*     Jogadores do xadrez
*
***********************************************************************/

   typedef enum {
      JOGADOR_BRANCO ,
      JOGADOR_PRETO ;
   } PEC_tpJogador ;

/***********************************************************************
*
*  $FC Função: PEC Criar peça
*
*  $ED Descrição da função
*     Cria um peça de xadrez usando a classe de peça fornecida.
*     O ponteiro para a peça criada será fornecido no valor do ponteiro
*     de ponteiro para peça.
*
*  $EP Parâmetros
*     $P ppPeca - ponteiro para ponteiro de peça
*     $P pClassePeca - ponteiro para a classe de peça
*     $P jogador - jogador dono da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetFaltouMemoria
*
***********************************************************************/

   PEC_tpCondRet PEC_CriarPeca( PEC_tppPeca * ppPeca , CPC_tppClassePeca pClassePeca , PEC_tpJogador jogador ) ;


/***********************************************************************
*
*  $FC Função: PEC Destruir peça
*
*  $ED Descrição da função
*     Destrói a peça, liberando o espaço alocado.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça a ser destruída
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

   PEC_tpCondRet PEC_DestruirPeca( PEC_tppPeca pPeca ) ;


/***********************************************************************
*
*  $FC Função: PEC Obter classe da peça
*
*  $ED Descrição da função
*     Obtém a classe da peça e preenche o ponteiro dado
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça
*     $P ppClassePeca - ponteiro para ponteiro que conterá a classe da peça
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

   PEC_tpCondRet PEC_ObterClassePeca( PEC_tppPeca pPeca , CPC_tppClassePeca * ppClassePeca ) ;


/***********************************************************************
*
*  $FC Função: PEC Obter jogador de peça
*
*  $ED Descrição da função
*     Obtém o jogador dono da peça dada.
*
*  $EP Parâmetros
*     $P pPeca - ponteiro para a peça
*     $P pJogador - ponteiro que será modificado para conter o jogador da peça dada
*
*  $FV Valor retornado
*     PEC_CondRetOK
*     PEC_CondRetPonteiroNulo
*
***********************************************************************/

   PEC_tpCondRet PEC_ObterClassePeca( PEC_tppPeca pPeca , PEC_tpJogador * pJogador ) ;


#undef PECA_EXT

/********** Fim do módulo de definição: Módulo peça de xadrez **********/

#else
#endif
