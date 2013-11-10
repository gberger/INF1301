/***************************************************************************
*  $MCI Módulo de implementação: Módulo principal
*
*  Arquivo gerado:              PRINCIPAL.C
*  Letras identificadoras:      PRN
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <string.h>

#include "TABULEIRO.H"
#include "LISTA.H"
#include "CLASSE_PECA.H"
#include "PECA.H"

/***********************************************************************
*
*  $TC Tipo de dados: PRN Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções do módulo principal
*
***********************************************************************/

   typedef enum {

         PRN_CondRetOK ,
               /* Executou corretamente */

         PRN_CondRetPonteiroNulo ,
               /* Foi passado um ponteiro para NULL */
         
         PRN_CondRetErroParm ,
               /* Foram passados um ou mais parametros invalidos */

         PRN_CondRetFaltouMemoria 
               /* Faltou memória ao alocar dados */

   } PRN_tpCondRet ;


/***********************************************************************
*
*  $FC Função: PRN renderizar menu principal
*
*  $ED Descrição da função
*     Abre o menu principal na tela para o usuário mapear o tabuleiro e testar.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_MenuPrincipal( );

/***********************************************************************
*
*  $FC Função: PRN criar novo tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro e permite o usuario alocar as pecas onde ele achar necessario.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_NovoTabuleiro( );

/***********************************************************************
*
*  $FC Função: PRN abrir tabuleiro
*
*  $ED Descrição da função
*     Abre um tabuleiro com as configuracoes previamente salvas.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_AbrirTabuleiro( );

/***********************************************************************
*
*  $FC Função: PRN salvar tabuleiro
*
*  $ED Descrição da função
*     Salva as configuracoes de um tabuleiro para ser utilizado mais tarde.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_SalvarTabuleiro( );

/***********************************************************************
*
*  $FC Função: PRN listar pecas
*
*  $ED Descrição da função
*     Lista todas as possibilidades de pecas que podem ser inseridas no tabuleiro.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_ListarPecas( );

/***********************************************************************
*
*  $FC Função: PRN cria peca
*
*  $ED Descrição da função
*     Abre o menu para criacao de uma peca pelo usuario.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_CriarPeca( );

/***********************************************************************
*
*  $FC Função: PRN alterar peca
*
*  $ED Descrição da função
*     Abre o menu de alteracao, onde o usuario pode reconfigurar uma peca.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_AlterarPeca( );

/***********************************************************************
*
*  $FC Função: PRN exclusao de peca
*
*  $ED Descrição da função
*     Exclui algum tipo de peca previamente definido pelo usuario.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_ExcluirPeca( );

/***********************************************************************
*
*  $FC Função: PRN funcao de saida
*
*  $ED Descrição da função
*     Fecha o programa.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_Sair( );

/****** Codigo de implementacao das funcoes *********/

/****** Funcao principal ********/

/********** Fim do módulo de implementação: Módulo principal **********/
