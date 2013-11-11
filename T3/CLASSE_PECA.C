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
*  $TC Tipo de dados: CPC Descritor de uma classe peça
*
*  $ED Descrição do tipo
*     Uma classe de peça possui um nome (string) e uma lista de movimentos.
*     Um movimento é uma ponteiro ao tipo de dados CPC_tpMovimento.
*
***********************************************************************/

typedef struct CPC_tagClassePeca {

    char * nome;

    LIS_tppLista movimentos;

} CPC_tpClassePeca ;

/***** Tipos de dados encapsulados no módulo *****/

/***********************************************************************
*
*  $TC Tipo de dados: CPC Descritor de um movimento de uma classe de peça
*
*  $ED Descrição do tipo
*     Estrutura simples que armazena dois inteiros, correspondentes aos
*       componentes X e Y do movimento de uma classe de peça.
*
***********************************************************************/

typedef struct CPC_tagMovimento {

    int movX;

    int movY;

} CPC_tpMovimento;

/***** Protótipo das funções encapuladas no módulo *****/

static void DestruirMovimento (void * pMovimento) ;

/*****  Código das funções exportadas pelo módulo  *****/


/***********************************************************************
*  $FC Função: CPC Criar classe de peça
***********************************************************************/

CPC_tpCondRet CPC_CriarClassePeca( CPC_tppClassePeca * ppClassePeca , char * nome ) {
    CPC_tpClassePeca * cp;

    cp = (CPC_tppClassePeca)malloc(sizeof(CPC_tpClassePeca));

    if(cp == NULL) {
        return CPC_CondRetFaltouMemoria;
    }

    cp->nome = (char*)malloc(sizeof(char) * (strlen(nome) + 1));

    if(cp->nome == NULL) {
        free(cp);
        return CPC_CondRetFaltouMemoria;
    }

    strcpy(cp->nome, nome);

    cp->movimentos = LIS_CriarLista( free );

    if(cp->movimentos == NULL) {
        free(cp->nome);
        free(cp);
        return CPC_CondRetFaltouMemoria;
    }

    *ppClassePeca = cp;

    return CPC_CondRetOK;
}


/***********************************************************************
*  $FC Função: CPC Destruir classe de peça
***********************************************************************/

CPC_tpCondRet CPC_DestruirClassePeca( CPC_tppClassePeca pClassePeca ) {
    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    LIS_DestruirLista(pClassePeca->movimentos);
    free(pClassePeca->nome);
    free(pClassePeca);

    return CPC_CondRetOK;
}


/***********************************************************************
*  $FC Função: CPC Adicionar movimento a classe de peça
***********************************************************************/

CPC_tpCondRet CPC_AdicionarMovimento( CPC_tppClassePeca pClassePeca , int movX , int movY ) {
    CPC_tpMovimento * movimento;
    int resp;

    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    CPC_ChecarMovimento(pClassePeca, movX, movY, &resp);
    if(resp == 1) {
        return CPC_CondRetArgumentosInvalidos;
    }

    movimento = (CPC_tpMovimento*)malloc(sizeof(CPC_tpMovimento));

    if(movimento == NULL) {
        return CPC_CondRetFaltouMemoria;
    }

    movimento->movX = movX;
    movimento->movY = movY;

    LIS_IrFinalLista(pClassePeca->movimentos);
    if( LIS_InserirElementoApos(pClassePeca->movimentos, movimento) == LIS_CondRetFaltouMemoria ) {
        return CPC_CondRetFaltouMemoria;
    }

    return CPC_CondRetOK;
}


/***********************************************************************
*  $FC Função: CPC Obter número de movimentos de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterNumeroMovimentos( CPC_tppClassePeca pClassePeca , int * numMovimentos ) {
    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    *numMovimentos = LIS_ObterNumElem(pClassePeca->movimentos);

    return CPC_CondRetOK;
}


/***********************************************************************
*  $FC Função: CPC Obter movimento de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterMovimento( CPC_tppClassePeca pClassePeca , int idxMovimento , int * pMovX , int * pMovY ) {
    int numElem;
    CPC_tpMovimento * movimento;

    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    CPC_ObterNumeroMovimentos(pClassePeca, &numElem);

    if(idxMovimento < 0 || idxMovimento >= numElem) {
        return CPC_CondRetArgumentosInvalidos;
    }

    LIS_IrInicioLista(pClassePeca->movimentos);
    LIS_AvancarElementoCorrente(pClassePeca->movimentos, idxMovimento);

    movimento = (CPC_tpMovimento*) LIS_ObterValor(pClassePeca->movimentos);

    *pMovX = movimento->movX;
    *pMovY = movimento->movY;

    return CPC_CondRetOK;
}

/***********************************************************************
*  $FC Função: CPC Checar movimento de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ChecarMovimento( CPC_tppClassePeca pClassePeca , int movX , int movY , int * resposta ) {
    int numMovimentos;
    int i;
    int movXObtido, movYObtido;

    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    if(movX > 7 || movY > 7 || movX < -7 || movY < -7) {
        *resposta = 0;
    }

    CPC_ObterNumeroMovimentos(pClassePeca, &numMovimentos);

    for(i = 0; i < numMovimentos; i++) {
        CPC_ObterMovimento(pClassePeca, i, &movXObtido, &movYObtido);
        if(movXObtido == movX && movYObtido == movY) {
            *resposta = 1;
            return CPC_CondRetOK;      
        }
    }

    return CPC_CondRetOK;      
}


/***********************************************************************
*  $FC Função: CPC Obter nome de classe de peça
***********************************************************************/

CPC_tpCondRet CPC_ObterNome( CPC_tppClassePeca pClassePeca , char ** pNome ) {
    if(pClassePeca == NULL) {
        return CPC_CondRetPonteiroNulo;
    }

    *pNome = pClassePeca->nome;

    return CPC_CondRetOK;
}


/***** Código das funções encapuladas no módulo *****/

/***********************************************************************
*
*  $FC Função: Destruir Movimento
*
*  $ED Descrição da função
*     Encapsula a função de destruição de um movimento.
*     Função para ser passada à lista genérica, que será usada para 
*       armazenar movimentos.
*
***********************************************************************/

static void DestruirMovimento (void * pMovimento) {
    free(pMovimento);
}



/********** Fim do módulo de implementação: Módulo classe de peça de xadrez **********/

