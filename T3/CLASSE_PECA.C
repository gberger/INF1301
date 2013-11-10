/***************************************************************************
*  $MCI Módulo de implementação: Módulo classe de peça de xadrez
*
*  Arquivo gerado:              CLASSE_PECA.C
*  Letras identificadoras:      CPC
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <malloc.h>
#include <stdio.h>
#include <string.h>

#define CLASSE_PECA_OWN
#include "CLASSE_PECA.H"
#undef CLASSE_PECA_OWN

/***********************************************************************
*
*  $TC Tipo de dados: TAB Descritor da cabeça de um tabuleiro
*
*
*  $ED Descrição do tipo
*     A cabeça do tabuleiro é o ponto de acesso para um determinado tabuleiro.
*     Por intermédio da referência para uma matriz pode-se navegar
*     pelo tabuleiro.
*
***********************************************************************/

   typedef struct CPC_tagClassePeca {

      char * nome,

      LIS_tppLista movimentos

   } CPC_tpClassePeca ;

/***** Protótipo das funções encapuladas no módulo *****/

   typedef struct CPC_tagMovimento {
      
      int movX,

      int movY
   
   } CPC_tpMovimento;

   static void DestruirMovimento (void * pMovimento) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*  $FC Função: CPC Criar classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_CriarClassePeca( CPC_tppClassePeca * ppClassePeca , char * nome ) {
      CPC_tpClassePeca * cp;

      cp = (CPC_tppClassePeca)malloc(sizeof(CPC_tpClassePeca));

      if(cp == NULL){
         return CPC_CondRetFaltouMemoria;
      }

      cp->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));

      if(cp->nome == NULL){
         free(cp);
         return CPC_CondRetFaltouMemoria;
      }

      strcpy(cp->nome, nome);

      cp->movimentos = LIS_CriarLista( free ); // DestruirMovimento ??

      if(cp->movimentos == NULL){
         free(cp->nome);
         free(cp);
         return CPC_CondRetFaltouMemoria;
      }

      *ppClassePeca = cp;

      return CPC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: CPC Destruir classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_DestruirClassePeca( CPC_tppClassePeca pClassePeca ) {
      if(pClassePeca == NULL){
         return CPC_CondRetPonteiroNulo;
      }

      LIS_DestruirLista(pClassePeca->movimentos);
      free(pClassePeca->nome);
      free(pClassePeca);

      return CPC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: CPC Adicionar movimento a classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_AdicionarMovimento( CPC_tppClassePeca pClassePeca , int movX , int movY ) {
      CPC_tpMovimento * movimento;

      if(pClassePeca == NULL){
         return CPC_CondRetPonteiroNulo;
      }

      movimento = (CPC_tpMovimento*)malloc(sizeof(CPC_tpMovimento));

      if(movimento == NULL){
         return CPC_CondRetFaltouMemoria;
      }

      LIS_IrFinalLista(pClassePeca->movimentos);
      if( LIS_InserirElementoApos(pClassePeca->movimentos, movimento) == LIS_CondRetFaltouMemoria ){
         return CPC_CondRetFaltouMemoria;
      }

      return CPC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: CPC Obter número de movimentos de classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_ObterNumeroMovimentos( CPC_tppClassePeca pClassePeca , int * numMovimentos ) {
      if(pClassePeca == NULL){
         return CPC_CondRetPonteiroNulo;
      }

      *numMovimentos = LIS_ObterNumElem(pClassePeca->movimentos);

      return CPC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: CPC Obter movimento de classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_ObterMovimento( CPC_tppClassePeca pClassePeca , int idxMovimento , int * pMovX , int * pMovY ) {
      if(pClassePeca == NULL){
         return CPC_CondRetPonteiroNulo;
      }

      int numElem;
      CPC_tpMovimento * movimento;

      CPC_ObterNumeroMovimentos(pClassePeca, &numElem);

      if(idxMovimento < 0 || idxMovimento >= numElem){
         return CPC_CondRetArgumentosInvalidos;
      }

      LIS_IrInicioLista(pClassePeca->movimentos);
      LIS_AvancarElementoCorrente(pClassePeca->movimentos, idxMovimento);

      movimento = LIS_ObterValor(pClassePeca->movimentos)

      *pMovX = movimento->movX;
      *pMovY = movimento->movY;

      return CPC_CondRetOk;
   }


/***********************************************************************
*  $FC Função: CPC Obter nome de classe de peça
***********************************************************************/

   CPC_tpCondRet CPC_ObterNome( CPC_tppClassePeca pClassePeca , char ** pNome ) {
      if(pClassePeca == NULL){
         return CPC_CondRetPonteiroNulo;
      }

      *pNome = pClassePeca->nome;

      return CPC_CondRetOk;
   }


/***** Código das funções encapuladas no módulo *****/

   static void DestruirMovimento (void * pMovimento) {
      free(pMovimento);
   }


#undef CLASSE_PECA_EXT

/********** Fim do módulo de definição: Módulo classe de peça de xadrez **********/

#else
#endif
