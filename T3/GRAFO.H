#if ! defined( GRAFO_ )
#define GRAFO_
/***************************************************************************
*
*  $MCD Módulo de definição: Grafo dirigido
*
*  Arquivo gerado:              GRAFO.H
*  Letras identificadoras:      GRA
*
*  Projeto: T3 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa funções para criar e explorar grafos dirigidos.

*
***************************************************************************/
 
#if defined( GRAFO_OWN )
   #define GRAFO_EXT
#else
   #define GRAFO_EXT extern
#endif

#include "LISTA.H"

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma grafo */

typedef struct GRA_tagGrafo * GRA_tppGrafo ;

/***********************************************************************
*
*  $TC Tipo de dados: GRA Condicoes de retorno
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da grafo
*
***********************************************************************/

   typedef enum {

      GRA_CondRetOK ,
         /* Executou corretamente */

		GRA_CondRetGrafoVazio ,
		   /* Operação inválida pois o grafo está vazio */

		GRA_CondRetVerticeInvalido ,
			/* Vertice referenciado não existe ou não é acessível */
			   
		GRA_CondRetErroVertice ,
			/* Operação no vértice resultou em erro */

      GRA_CondRetPonteiroNulo ,
         /* Foi passado um ponteiro para NULL */

      GRA_CondRetFaltouMemoria ,
         /* Faltou memória ao alocar dados */

		GRA_CondRetArestaJaExiste ,
			/* Já existe uma aresta com a mesma origem e destino */

      GRA_CondRetArestaInvalida
         /* Não existe uma aresta com tal identificador */

   } GRA_tpCondRet ;
   

/***********************************************************************
*
*  $FC Função: GRA Criar grafo
*
*  $ED Descrição da função
*     Cria um novo grafo.
*     O ponteiro para o novo grafo será fornecido no valor do ponteiro
*     de ponteiro para grafo.
*
*  $EP Parâmetros
*     $P ppGrafo - ponteiro para o ponteiro de grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     ExcluirValor ponteiro para uma função que encarregue-se de excluir os
*        valores que serão usados nos vértices do grafo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        ppGrafo conterá um ponteiro para um grafo
*     SE GRA_CondRetFaltouMemoria
*        ppGrafo não será modificado
*
***********************************************************************/

   GRA_tpCondRet GRA_CriarGrafo( GRA_tppGrafo * ppGrafo, void ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: GRA Destruir grafo
*
*  $ED Descrição da função
*     Destrói o grafo, liberando o espaço ocupado
*     pela grafo, pelos vértices e pelas listas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá sido liberado e será agora um ponteiro inválido
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_DestruirGrafo( GRA_tppGrafo pGrafo ) ;


/***********************************************************************
*
*  $FC Função: GRA Esvaziar
*
*  $ED Descrição da função
*     Esvazia a grafo, isso é, libera todos os vértices e listas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá sido esvaziado: todos os vértices, arestas e origens
*           terão sido excluídos
*        vértice corrente será NULL
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_EsvaziarGrafo( GRA_tppGrafo pGrafo ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Obter valor do vértice corrente
*
*  $ED Descrição da função
*     O valor do vértice corrente é retornado pelo parâmetro ppValor.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P ppValor - ponteiro para o ponteiro de vertice, a ser modificado
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     ppValor != NULL
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        ppValor conterá ponteiro para o valor contido no vértice corrente
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL ou ppValor era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_ObterValorCorrente( GRA_tppGrafo pGrafo, void ** ppValor ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Alterar valor do vértice corrente
*
*  $ED Descrição da função
*     O vértice corrente é alterado para o valor de pValor.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P pValor - ponteiro para um valor de vertice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá em seu nó corrente o valor pValor
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_AlterarValorCorrente( GRA_tppGrafo pGrafo, void * pValor ) ;


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
*  $ED Descrição da função
*     O vértice corrente torna-se o vértice cujo valor é o dado, se
*		existir tal vértice no grafo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P idVertice - identificador do vértice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*	   GRA_CondRetVerticeInvalido
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVertice deve ser um id de um vértice válido existente no grafo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá como vértice corrente o vértice cujo id é idVertice
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetVerticeInvalido
*        idVertice não era um id de um vértice válido existente no grafo
*
***********************************************************************/

   GRA_tpCondRet GRA_IrParaVertice( GRA_tppGrafo pGrafo, int idVertice ) ;


/***********************************************************************
*
*  $FC Função: GRA Ir para vertice
*
*  $ED Descrição da função
*     O vértice corrente torna-se o vértice cujo valor é o dado, desde
*		que tal vértice seja um dos sucessores do corrente.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para a grafo.
*     $P idVertice - identificador do vértice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*	   GRA_CondRetVerticeInvalido
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVertice deve ser um id de um vértice válido existente no grafo,
*       e tal vértice deve ser um dos sucessores do vértice corrente
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá como vértice corrente o vértice cujo id é idVertice
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetVerticeInvalido
*        idVertice não era um id de um vértice válido existente no grafo
*           OU era id válido mas não era sucessor do vértice corrente
*
***********************************************************************/

   GRA_tpCondRet GRA_AndarParaVertice( GRA_tppGrafo pGrafo, int idVertice ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Inserir vértice
*
*  $ED Descrição da função
*     Cria um novo vértice a partir do valor dado.
*	  O novo vértice não possui arestas.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P pVertice - ponteiro para o conteúdo a ser inserido no novo vértice criado.
*	   $P idVertice - identificador do vértice
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetFaltouMemoria
*     GRA_CondRetPonteiroNulo
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá um novo vértice com o valor e identificador dados
*     SE GRA_CondRetFaltouMemoria
*        pGrafo não será modificado
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirVertice( GRA_tppGrafo pGrafo, void * pVertice, int idVertice ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Excluir vértice corrente
*
*  $ED Descrição da função
*     Exclui o vértice corrente.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*	   GRA_CondRetGrafoVazio
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        o antigo vértice corrente de pGrafo será excluído
*        o novo vértice corrente será o primeiro da lista de vértices
*        ou o novo vértice corrente será NULL, caso o grafo esteja vazio
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirVerticeCorrente( GRA_tppGrafo pGrafo ) ;

   
/***********************************************************************
*
*  $FC Função: GRA Inserir aresta
*
*  $ED Descrição da função
*     Insere uma aresta no grafo
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idVerticeOrigem - identificador do vértice origem da aresta
*     $P idVerticeDestino - identificador do vértice destino da aresta
*     $P idAresta - identificador da aresta a ser criada
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*	   GRA_CondRetArestaJaExiste
*     GRA_CondRetVerticeInvalido
*     GRA_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVerticeOrigem deve ser um identificador de vértice válido
*     idVerticeDestino deve ser um identificador de vértice válido
*     idAresta deve ser uma string de no máximo 9 caracteres válidos
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá uma nova aresta apontando do vértice origem 
*           ao vértice destino
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetArestaJaExiste
*        já existia uma aresta ligando o vértice origem ao vértice destino
*     SE GRA_CondRetVerticeInvalido
*        idVerticeOrigem não é um identificador de vértice válido
*        OU idVerticeDestino não é um identificador de vértice válido
*     SE GRA_CondRetFaltouMemoria
*        pGrafo não será modificado
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirAresta( GRA_tppGrafo pGrafo, int idVerticeOrigem, int idVerticeDestino, int idAresta ) ;


/***********************************************************************
*
*  $FC Função: GRA Inserir aresta no corrente
*
*  $ED Descrição da função
*     Insere uma aresta a partir do vértice corrente, dirigida
*     ao vértice informado como destino
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idVerticeDestino - identificador do vértice destino da aresta
*     $P idAresta - identificador da aresta a ser criada, possui no
*           máximo 9 caracteres válidos.
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*     GRA_CondRetArestaJaExiste
*     GRA_CondRetVerticeInvalido
*     GRA_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVerticeDestino deve ser um identificador de vértice válido
*     idAresta deve ser uma string de no máximo 9 caracteres válidos
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá uma nova aresta apontando do vértice corrente 
*           ao vértice destino
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetArestaJaExiste
*        já existia uma aresta ligando o vértice corrente ao vértice destino
*     SE GRA_CondRetVerticeInvalido
*        idVerticeDestino não é um identificador de vértice válido
*     SE GRA_CondRetFaltouMemoria
*        pGrafo não será modificado
*
***********************************************************************/

   GRA_tpCondRet GRA_InserirArestaOrigemCorrente( GRA_tppGrafo pGrafo, int idVerticeDestino, int idAresta ) ;

/***********************************************************************
*
*  $FC Função: GRA Percorrer aresta
*
*  $ED Descrição da função
*	  Muda corrente para o vértice apontado pela aresta identificada
*	  por idAresta, que por sua vez tem como origem o corrente atual
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idAresta - identificador da aresta
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*     GRA_CondRetArestaInvalida
*     GRA_CondRetGrafoVazio
*
***********************************************************************/

   GRA_tpCondRet GRA_PercorrerAresta( GRA_tppGrafo pGrafo, int idAresta ) ;
   
/***********************************************************************
*
*  $FC Função: GRA Excluir aresta
*
*  $ED Descrição da função
*	  Exclui aresta que tem id igual ao fornecido
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idAresta - identificador da aresta
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*     GRA_CondRetArestaInvalida
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idAresta deve ser uma string de no máximo 9 caracteres
*     idAresta deve ser um identificador válido de uma aresta existente
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá uma nova aresta apontando do vértice corrente 
*           ao vértice destino
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetArestaInvalida
*        idAresta não era um identificado válido de uma aresta existente
*
***********************************************************************/

   GRA_tpCondRet GRA_ExcluirAresta( GRA_tppGrafo pGrafo, int idAresta ) ;


/***********************************************************************
*
*  $FC Função: GRA Adicionar origem
*
*  $ED Descrição da função
*     Inclui vértice na lista de origens do grafo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idVertice - identificador do vértice a ser definido como origem
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*     GRA_CondRetVerticeInvalido
*     GRA_CondRetFaltouMemoria
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVértice deve ser um id válido de um vértice existente
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        pGrafo terá uma nova origem
*        vértice cujo id é idVertice será uma origem
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetVerticeInvalido
*        idVertice não era um identificado válido de uma vértice existente
*     SE GRA_CondRetFaltouMemoria
*        pGrafo não será modificado
*
***********************************************************************/

   GRA_tpCondRet GRA_AdicionarOrigem( GRA_tppGrafo pGrafo, int idVertice ) ;

/***********************************************************************
*
*  $FC Função: GRA Remover origem
*
*  $ED Descrição da função
*     Remove vértice da lista de origens do grafo.
*
*  $EP Parâmetros
*     $P pGrafo - ponteiro para o grafo.
*     $P idVertice - identificador do vértice a não ser mais origem
*
*  $FV Valor retornado
*     GRA_CondRetOK
*     GRA_CondRetPonteiroNulo
*     GRA_CondRetVerticeInvalido
*
*  $EAE Assertivas de entrada
*     pGrafo != NULL
*     pGrafo deve ser ponteiro válido para um grafo do módulo
*     idVértice deve ser um id válido de um vértice existente
*
*  $EAE Assertivas de saída
*     SE GRA_CondRetOK
*        vértice cujo id é idVertice não será mais uma origem
*     SE GRA_CondRetPonteiroNulo
*        pGrafo era NULL
*     SE GRA_CondRetVerticeInvalido
*        idVertice não era um identificado válido de uma vértice existente
*
***********************************************************************/

   GRA_tpCondRet GRA_RemoverOrigem( GRA_tppGrafo pGrafo, int idVertice ) ;
   

#undef GRAFO_EXT

/********** Fim do módulo de definição: Módulo grafo **********/

#else
#endif
