#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - Jo�o Vicente
*
*  $ED Descri��o do m�dulo
*     Implementa listas gen�ricas duplamente encadeadas.
*     Podem existir n listas em opera��o simultaneamente.
*     As listas possuem uma cabe�a encapsulando o seu estado.
*
*     Cada lista � homog�nea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que cont�m.
*
*     Os ponteiros para os dados s�o copiados para elementos da lista.
*        N�o � copiado o valor apontado por estes ponteiros.
*
*     O controle da destrui��o do valor de um elemento a ser exclu�do
*        � realizado por uma fun��o fornecida pelo usu�rio.
*
*     Cada lista referencia uma fun��o que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A fun��o de libera��o dos valores contidos nos elementos deve
*        assegurar a libera��o de todos os espa�os refer�nciados pelo
*        valor contido em um elemento.
*        Esta fun��o � chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso n�o seja necess�rio desalocar o valor referenciado pelo
*        elemento, o ponteiro para a fun��o de libera��o poder� ser NULL .
*        Caso o elemento da lista seja a �nica �ncora do valor referenciado,
*        esta fun��o deve promover a destrui��o (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista n�o cont�m elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* N�o encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Criar lista
*
*  $ED Descri��o da fun��o
*     Cria uma lista gen�rica duplamente encadeada.
*     Os poss�veis tipos s�o desconhecidos a priori.
*     A tipagem � implicita.
*     N�o existe identificador de tipo associado � lista.
*
*  $EP Par�metros
*     ExcluirValor  - ponteiro para a fun��o que processa a
*                     exclus�o do valor referenciado pelo elemento
*                     a ser exclu�do.
*                     Ver descri��o do m�dulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro ser� utilizado pelas fun��es que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de mem�ria ou dados errados,
*     a fun��o retornar� NULL.
*     N�o ser� dada mais informa��o quanto ao problema ocorrido.
*
*  $EAE Assertivas de entrada
*     ExcluirValor ponteiro para umafun��o que encarregue-se de excluir os
*        valores que ser�o usados na lista
*
*  $EAE Assertivas de sa�da
*     Retorna um ponteiro v�lido para a lista criada, caso tenha executado
*       corretamente.
*     Retorna NULL caso tenha ocorrido algum erro.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Destruir lista
*
*  $ED Descri��o da fun��o
*     Destr�i a lista fornecida.
*     O par�metro ponteiro para a lista n�o � modificado.
*     Se ocorrer algum erro durante a destrui��o, a lista resultar�
*     estruturalmente incorreta.
*     OBS. n�o existe previs�o para poss�veis falhas de execu��o.
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     A lista encontra-se destru�da.
*     A mem�ria de cada elemento � liberada.
*     Em caso de erros, a lista pode ficar estruturalmente incorreta.
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Esvaziar lista
*
*  $ED Descri��o da fun��o
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     A lista encontra-se esvaziada, com zero elementos.
*     A mem�ria de cada elemento � liberada.
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento antes
*
*  $ED Descri��o da fun��o
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista onde deve ser inserido o elemento
*     pValor - ponteiro para o valor do novo elemento
*              Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se LIS_CondRetOK:
*       Se a lista anteriormente estava vazia, agora cont�m um elemento,
*         com valor pValor. O n� corrente torna-se este elemento.
*       Do contr�rio, a lista agora cont�m um elemento a mais, sendo este
*         inserido imediatamente antes do n� corrente. O n� corrente n�o
*         � modificado.
*     Se LIS_CondRetFaltouMemoria:
*       A lista n�o � modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Inserir elemento ap�s
*
*  $ED Descri��o da fun��o
*     Insere novo elemento ap�s o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Par�metros
*     Par�metros
*        pLista - ponteiro para a lista onde deve ser inserido o elemento
*        pValor - ponteiro para o valor do novo elemento
*                 Pode ser NULL
*           
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se LIS_CondRetOK:
*       Se a lista anteriormente estava vazia, agora cont�m um elemento,
*         com valor pValor. O n� corrente torna-se este elemento.
*       Do contr�rio, a lista agora cont�m um elemento a mais, sendo este
*         inserido imediatamente ap�s o n� corrente. O n� corrente n�o
*         � modificado.
*     Se LIS_CondRetFaltouMemoria:
*       A lista n�o � modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Excluir elemento
*
*  $ED Descri��o da fun��o
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente ser� o novo corrente.
*     Se n�o existir e existir o elemento � direita, este se tornar� corrente.
*     Se este tamb�m n�o existir a lista tornou-se vazia.
*
*  $EP Par�metros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se LIS_CondRetOK:
*       A lista anteriormente n�o estava vazia, e agora cont�m um elemento a menos.
*       O elemento corrente � exclu�do, e seu valor � liberado.
*       Se existir o elemento a esquerda do antigo corrente, este ser� o novo corrente.
*       Sen�o, se existir o elemento � direita, este se tornar� corrente.
*       Sen�o, a lista tornou-se vazia.
*     Se LIS_CondRetListaVazia:
*       A lista anteriormente estava vazia e n�o � modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter refer�ncia para o valor contido no elemento
*
*  $ED Descri��o da fun��o
*     Obtem a refer�ncia para o valor contido no elemento corrente da lista
*
*  $EP Par�metros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     n�o NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se o retorno for NULL:
*       A lista est� vazia, OU
*       O elemento inserido no n� corrente � NULL
*     Sen�o:
*       A lista n�o est� vazia, e o retono � o elemento inserido no n� corrente.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento inicial
*
*  $ED Descri��o da fun��o
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se a lista estiver vazia:
*       A lista n�o � modificada.
*     Sen�o:
*       O n� corrente torna-se o primeiro n�.
*
***********************************************************************/

   void LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Ir para o elemento final
*
*  $ED Descri��o da fun��o
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista est� vazia.
*
*  $EP Par�metros
*     pLista - ponteiro para a lista a manipular
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se a lista estiver vazia:
*       A lista n�o � modificada.
*     Sen�o:
*       O n� corrente torna-se o �ltimo n�.
*
***********************************************************************/

   void LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Avan�ar elemento
*
*  $ED Descri��o da fun��o
*     Avan�a o elemento corrente numElem elementos na lista
*     Se numElem for positivo avan�a em dire��o ao final
*     Se numElem for negativo avan�a em dire��o ao in�cio
*     numElem pode ser maior do que o n�mro de elementos existentes na
*               dire��o desejada
*     Se numElem for zero somente verifica se a lista est� vazia
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o n�mero de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista est� vazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se LIS_CondRetOK:
*       A lista n�o estava vazia.
*       Se numElem == 0:
*         A lista n�o � modificada.
*       Se numElem > 0:
*         Foram andados numElem elementos em dire��o ao final sem problemas.
*       Se numElem < 0:
*         Foram andados numElem elementos em dire��o ao in�cio sem problemas.
*     Se LIS_CondRetFimLista:
*       Se numElem > 0:
*         Foram andados um n�mero menor de numElem elementos em dire��o ao final,
*         e chegou-se ao final.
*       Se numElem < 0:
*         Foram andados um n�mero menor de numElem elementos em dire��o ao in�cio,
*         e chegou-se ao in�cio.
*     Se LIS_CondRetListaVazia:
*       A lista estava vazia e n�o � modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Procurar elemento contendo valor
*
*  $ED Descri��o da fun��o
*     Procura o elemento que referencia o valor dado.
*     A fun��o compara ponteiro e n�o conte�do apontado.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente � o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que cont�m o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro n�o foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de sa�da
*     Se LIS_CondRetOK:
*       O novo n� corrente � o primeiro n� a partir do antigo corrente 
*       (inclusive) at� o final da lista cujo valor � igual a pValor.
*     Se LIS_CondRetNaoEncontrou:
*       A lista n�o � modificada.
*     Se LIS_CondRetListaVazia:
*       A lista estava vazia e n�o � modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;


/***********************************************************************
*
*  $FC Fun��o: LIS  &Obter numero de elementos
*
*  $ED Descri��o da fun��o
*     Obtem o numero de elementos da lista.
*
*  $EP Par�metros
*     pLista  - ponteiro para a lista
*
*  $FV Valor retornado
*     -1           - ponteiro para lista � NULL
*     inteiro >= 0 - caso contr�rio
*
*
***********************************************************************/

   int LIS_ObterNumElem( LIS_tppLista pLista ) ;
   
#undef LISTA_EXT

/********** Fim do m�dulo de defini��o: LIS  Lista duplamente encadeada **********/

#else
#endif
