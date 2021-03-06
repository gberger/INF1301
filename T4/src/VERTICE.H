#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD M�dulo de defini��o: VER  V�rtice de grafo contendo string
*
*  Arquivo gerado:              VERTICE.h
*  Letras identificadoras:      VER
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - Jo�o Vicente
*
*  $ED Descri��o do m�dulo
*     Implementa v�rtices que armazenam conte�do gen�rico.
*     Cada elemento do v�rtice armazena uma refer�ncia gen�rica para 
*     umca cadeia de caracteres.
*
***************************************************************************/
 
#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

/***** Declara��es exportadas pelo m�dulo *****/

/* Tipo refer�ncia para um v�rtice */

typedef struct VER_tagVertice * VER_tppVertice;


/***********************************************************************
*
*  $TC Tipo de dados: VER Condi��es de retorno
*
*
*  $ED Descri��o do tipo
*     Condi��es de retorno das fun��es da lista
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK ,
               /* Concluiu corretamente */

         VER_CondRetVerticeVazio ,
               /* V�rtice n�o possui conte�do */

         VER_CondRetPonteiroNulo ,
               /* Ponteiro fornecido � nulo */

         VER_CondRetFaltouMemoria
               /* Faltou mem�ria ao tentar criar um elemento de
               * v�rtice ou um elemento da lista de arestas */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Fun��o: VER  &Criar v�rtice
*
*  $ED Descri��o da fun��o
*     Cria um v�rtice que armazena conte�do gen�rico.
*
*  $EP Par�metros
*     ppVertice - ponteiro para tipo refer�ncia para v�rtice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*     VER_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     ppVertice != NULL
*
*  $EAE Assertivas de sa�da
*     SE VER_CondRetOK
*        ppVertice conter� um ponteiro para um v�rtice
*     SE VER_CondRetPonteiroNulo
*        ppVertice era NULL
*     SE VER_CondRetFaltouMemoria
*        ppVertice n�o ser� modificado
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice( VER_tppVertice * ppVertice ) ;


/***********************************************************************
*
*  $FC Fun��o: VER  &Destruir v�rtice
*
*  $ED Descri��o da fun��o
*     Destr�i o v�rtice fornecido.
*     O par�metro tipo refer�ncia para v�rtice n�o � modificado.
*
*  $EP Par�metros
*     pVertice - tipo refer�ncia para v�rtice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice � ponteiro v�lido para v�rtice
*
*  $EAE Assertivas de sa�da
*     SE VER_CondRetOK
*        pVertice conter� um ponteiro para um v�rtice inv�lido (liberado)
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Fun��o: VER  &Esvaziar v�rtice
*
*  $ED Descri��o da fun��o
*     Destr�i cadeia de caracteres armazenada no v�rtice, caso exista.
*
*  $EP Par�metros
*     pVertice - tipo refer�ncia para v�rtice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice � ponteiro v�lido para v�rtice
*
*  $EAE Assertivas de sa�da
*     SE VER_CondRetOK
*        pVertice ter� seu valor armazenado destru�do, caso exista
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*
***********************************************************************/

   VER_tpCondRet VER_EsvaziarVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Fun��o: VER  &Atribuir valor
*
*  $ED Descri��o da fun��o
*     Atribui refer�ncia gen�rica ao valor do v�rtice
*
*  $EP Par�metros
*     pVertice - tipo refer�ncia para v�rtice
*     valor - ponteiro para cadeia de caracteres
*
*  $FV Valor retornado
*     VER_CondRetOK
*	   VER_CondRetFaltouMemoria
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice � ponteiro v�lido para v�rtice
*     valor � string
*
*  $EAE Assertivas de sa�da
*     SE VER_CondRetOK
*        pVertice ter� seu novo valor dado por 'valor'
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*     SE VER_CondRetFaltouMemoria
*        pVertice n�o ser� modificado
*
***********************************************************************/

   VER_tpCondRet VER_AtribuirValor( VER_tppVertice pVertice, char * valor ) ;

/***********************************************************************
*
*  $FC Fun��o: VER  &Obter valor
*
*  $ED Descri��o da fun��o
*     Obtem refer�ncia para cont�do gen�rico armazenado no v�rtice.
*
*  $EP Par�metros
*     pVertice - tipo refer�ncia para v�rtice
*     pValor - ponteiro de ponteiro para cadeia de caracteres
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeVazio
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice � ponteiro v�lido para v�rtice
*     pValor != NULL
*
*  $EAE Assertivas de sa�da
*     SE VER_CondRetOK
*        pValor conter� o endere�o da string (valor do v�rtice)
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*     SE VER_CondRetVerticeVazio
*        pVertice n�o tinha um valor armazenado
*
***********************************************************************/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice, char ** pValor ) ;


#undef VERTICE_EXT

/********** Fim do m�dulo de defini��o: VER  V�rtice de grafo contendo string **********/

#else
#endif
