#if ! defined( VERTICE_ )
#define VERTICE_
/***************************************************************************
*
*  $MCD Módulo de definição: VER  Vértice de grafo contendo string
*
*  Arquivo gerado:              VERTICE.h
*  Letras identificadoras:      VER
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa vértices que armazenam conteúdo genérico.
*     Cada elemento do vértice armazena uma referência genérica para 
*     umca cadeia de caracteres.
*
***************************************************************************/
 
#if defined( VERTICE_OWN )
   #define VERTICE_EXT
#else
   #define VERTICE_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para um vértice */

typedef struct VER_tagVertice * VER_tppVertice;


/***********************************************************************
*
*  $TC Tipo de dados: VER Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         VER_CondRetOK ,
               /* Concluiu corretamente */

         VER_CondRetVerticeVazio ,
               /* Vértice não possui conteúdo */

         VER_CondRetPonteiroNulo ,
               /* Ponteiro fornecido é nulo */

         VER_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de
               * vértice ou um elemento da lista de arestas */

   } VER_tpCondRet ;


/***********************************************************************
*
*  $FC Função: VER  &Criar vértice
*
*  $ED Descrição da função
*     Cria um vértice que armazena conteúdo genérico.
*
*  $EP Parâmetros
*     ppVertice - ponteiro para tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*     VER_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     ppVertice != NULL
*
*  $EAE Assertivas de saída
*     SE VER_CondRetOK
*        ppVertice conterá um ponteiro para um vértice
*     SE VER_CondRetPonteiroNulo
*        ppVertice era NULL
*     SE VER_CondRetFaltouMemoria
*        ppVertice não será modificado
*
***********************************************************************/

   VER_tpCondRet VER_CriarVertice( VER_tppVertice * ppVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Destruir vértice
*
*  $ED Descrição da função
*     Destrói o vértice fornecido.
*     O parâmetro tipo referência para vértice não é modificado.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice é ponteiro válido para vértice
*
*  $EAE Assertivas de saída
*     SE VER_CondRetOK
*        pVertice conterá um ponteiro para um vértice inválido (liberado)
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*
***********************************************************************/

   VER_tpCondRet VER_DestruirVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Esvaziar vértice
*
*  $ED Descrição da função
*     Destrói cadeia de caracteres armazenada no vértice, caso exista.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice é ponteiro válido para vértice
*
*  $EAE Assertivas de saída
*     SE VER_CondRetOK
*        pVertice terá seu valor armazenado destruído, caso exista
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*
***********************************************************************/

   VER_tpCondRet VER_EsvaziarVertice( VER_tppVertice pVertice ) ;


/***********************************************************************
*
*  $FC Função: VER  &Atribuir valor
*
*  $ED Descrição da função
*     Atribui referência genérica ao valor do vértice
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*     valor - ponteiro para cadeia de caracteres
*
*  $FV Valor retornado
*     VER_CondRetOK
*	   VER_CondRetFaltouMemoria
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice é ponteiro válido para vértice
*     valor é string
*
*  $EAE Assertivas de saída
*     SE VER_CondRetOK
*        pVertice terá seu novo valor dado por 'valor'
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*     SE VER_CondRetFaltouMemoria
*        pVertice não será modificado
*
***********************************************************************/

   VER_tpCondRet VER_AtribuirValor( VER_tppVertice pVertice, char * valor ) ;

/***********************************************************************
*
*  $FC Função: VER  &Obter valor
*
*  $ED Descrição da função
*     Obtem referência para contúdo genérico armazenado no vértice.
*
*  $EP Parâmetros
*     pVertice - tipo referência para vértice
*     pValor - ponteiro de ponteiro para cadeia de caracteres
*
*  $FV Valor retornado
*     VER_CondRetOK
*     VER_CondRetVerticeVazio
*     VER_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pVertice != NULL
*     pVertice é ponteiro válido para vértice
*     pValor != NULL
*
*  $EAE Assertivas de saída
*     SE VER_CondRetOK
*        pValor conterá o endereço da string (valor do vértice)
*     SE VER_CondRetPonteiroNulo
*        pVertice era NULL
*     SE VER_CondRetVerticeVazio
*        pVertice não tinha um valor armazenado
*
***********************************************************************/

   VER_tpCondRet VER_ObterValor( VER_tppVertice pVertice, char ** pValor ) ;


#undef VERTICE_EXT

/********** Fim do módulo de definição: VER  Vértice de grafo contendo string **********/

#else
#endif
