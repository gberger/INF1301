/***************************************************************************
*  $MCI Módulo de implementação: Módulo tabuleiro
*
*  Arquivo gerado:              TABULEIRO.C
*  Letras identificadoras:      TAB
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
***************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#define TABULEIRO_OWN
#include "TABULEIRO.H"
#undef TABULEIRO_OWN

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

typedef struct TAB_tagTabuleiro {

    MAT_tppMatriz pMatriz ;
        /* Ponteiro para a matriz utilizada */
    char i;
        /* Coordenada vertical da posição corrente */
    int j;
        /* Coordenada horizontal da posição corrente */

} TAB_tpTabuleiro ;


/***** Protótipo das funções encapuladas no módulo *****/

static void ExcluirCasa( void * pValor );


/*****  Código das funções exportadas pelo módulo  *****/

/***********************************************************************
*  $FC Função: TAB Criar tabuleiro
***********************************************************************/

TAB_tpCondRet TAB_CriarTabuleiro( TAB_tppTabuleiro * ppTabuleiro ) {
    TAB_tppTabuleiro pTab;
    int i, j;

    if(ppTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    pTab = (TAB_tpTabuleiro *)malloc(sizeof(TAB_tpTabuleiro));
    if(pTab == NULL || MAT_CriarMatriz(&(pTab->pMatriz), 8, ExcluirCasa) != MAT_CondRetOK) {
        return TAB_CondRetFaltouMemoria;
    }

    pTab->i = 'A';
    pTab->j = 1;

    *ppTabuleiro = pTab;

    return TAB_CondRetOK;

}


/***********************************************************************
*  $FC Função: TAB Destruir tabuleiro
***********************************************************************/

TAB_tpCondRet TAB_DestruirTabuleiro( TAB_tppTabuleiro pTabuleiro ) {

    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    MAT_DestruirMatriz( pTabuleiro->pMatriz );

    free( pTabuleiro );

    return TAB_CondRetOK;

}


/***********************************************************************
*  $FC Função: TAB Definir posição corrente.
***********************************************************************/

TAB_tpCondRet TAB_DefinirCorrente( TAB_tppTabuleiro pTabuleiro, char i, int j ) {
    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    if(TAB_ChecarPosicaoValida(i, j) == TAB_CondRetPosicaoInvalida || MAT_DefinirCorrente( pTabuleiro->pMatriz, (int) (i-'A'), j - 1) == MAT_CondRetPosicaoInvalida )
        return TAB_CondRetPosicaoInvalida;

    pTabuleiro->i = i;
    pTabuleiro->j = j;

    return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Obter posição corrente.
***********************************************************************/

TAB_tpCondRet TAB_ObterCorrente( TAB_tppTabuleiro pTabuleiro, char *i, int *j ) {
    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    *i = pTabuleiro->i;
    *j = pTabuleiro->j;

    return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Atribuir valor
***********************************************************************/

TAB_tpCondRet TAB_AtribuirValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca pPeca ) {

    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    MAT_AtribuirValorCorrente( pTabuleiro->pMatriz, (void *)pPeca);

    return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Obter valor corrente
***********************************************************************/

TAB_tpCondRet TAB_ObterValorCorrente( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca ) {
    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    MAT_ObterValorCorrente( pTabuleiro->pMatriz, (void **)ppPeca);

    return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB Obter valor de casa
***********************************************************************/

TAB_tpCondRet TAB_ObterValorDeCasa( TAB_tppTabuleiro pTabuleiro, PEC_tppPeca * ppPeca , char i, int j ) {
    char oldI;
    int oldJ;	   
    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    TAB_ObterCorrente(pTabuleiro, &oldI, &oldJ);
    TAB_DefinirCorrente(pTabuleiro, i, j);
    TAB_ObterValorCorrente(pTabuleiro, ppPeca);
    TAB_DefinirCorrente(pTabuleiro, oldI, oldJ);

    return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Mover valor de uma casa a outra
***********************************************************************/

TAB_tpCondRet TAB_MoverValor( TAB_tppTabuleiro pTabuleiro, char iOrig, int jOrig, char iDest, int jDest, PEC_tppPeca * pPecaComida ) {
    PEC_tppPeca pPeca;

    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    if(TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetPosicaoInvalida || TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetPosicaoInvalida) {
        return TAB_CondRetPosicaoInvalida;
    }

    TAB_DefinirCorrente(pTabuleiro, iOrig, jOrig);
    TAB_ObterValorCorrente(pTabuleiro, &pPeca);
    TAB_AtribuirValorCorrente(pTabuleiro, NULL);
    TAB_DefinirCorrente(pTabuleiro, iDest, jDest);
    TAB_ObterValorCorrente(pTabuleiro, pPecaComida);
    TAB_AtribuirValorCorrente(pTabuleiro, pPeca);

    return TAB_CondRetOK;
}

/***********************************************************************
*  $FC Função: TAB Mover valor de uma casa a outra
***********************************************************************/

TAB_tpCondRet TAB_DesMoverValor( TAB_tppTabuleiro pTabuleiro, char iOrig, int jOrig, char iDest, int jDest, PEC_tppPeca pPecaComida ) {
    PEC_tppPeca pPeca;

    if(pTabuleiro == NULL) {
        return TAB_CondRetPonteiroNulo;
    }

    if(TAB_ChecarPosicaoValida(iOrig, jOrig) == TAB_CondRetPosicaoInvalida || TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetPosicaoInvalida) {
        return TAB_CondRetPosicaoInvalida;
    }

    TAB_DefinirCorrente(pTabuleiro, iDest, jDest);
    TAB_ObterValorCorrente(pTabuleiro, &pPeca);
    TAB_AtribuirValorCorrente(pTabuleiro, pPecaComida);
    TAB_DefinirCorrente(pTabuleiro, iOrig, jOrig);
    TAB_AtribuirValorCorrente(pTabuleiro, pPeca);

    return TAB_CondRetOK;
}


/***********************************************************************
*  $FC Função: TAB - Checar posição válida
***********************************************************************/

TAB_tpCondRet TAB_ChecarPosicaoValida( char i, int j ) {
    if(i > 'H' || i < 'A' || j > 8 || j < 1) {
        return TAB_CondRetPosicaoInvalida;
    }

    return TAB_CondRetOK;
}


/***** Código das funções encapuladas no módulo *****/

/***********************************************************************
*
*  $FC Função: TAB - Excluir casa
*
*  $ED Descrição da função
*	  Função auxiliar para destruir casa
*
***********************************************************************/

static void ExcluirCasa( void * pValor ) {
    if(pValor != NULL) {
        PEC_DestruirPeca( (PEC_tppPeca) pValor);
    }
}


/********** Fim do módulo de definição: Módulo tabuleiro **********/
