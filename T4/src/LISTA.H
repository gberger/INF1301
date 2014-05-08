#if ! defined( LISTA_ )
#define LISTA_
/***************************************************************************
*
*  $MCD Módulo de definição: LIS  Lista duplamente encadeada
*
*  Arquivo gerado:              LISTA.h
*  Letras identificadoras:      LIS
*
*  Projeto: T2 INF1301 2013.2
*  Autores: gb - Guilherme Berger
*           fl - Felipe Luiz
*           jv - João Vicente
*
*  $ED Descrição do módulo
*     Implementa listas genéricas duplamente encadeadas.
*     Podem existir n listas em operação simultaneamente.
*     As listas possuem uma cabeça encapsulando o seu estado.
*
*     Cada lista é homogênea quanto ao tipo dos dados que armazena.
*     Cada elemento da lista referencia o valor que contém.
*
*     Os ponteiros para os dados são copiados para elementos da lista.
*        Não é copiado o valor apontado por estes ponteiros.
*
*     O controle da destruição do valor de um elemento a ser excluído
*        é realizado por uma função fornecida pelo usuário.
*
*     Cada lista referencia uma função que determina como devem ser
*        desalocados os dados nela contidos.
*
*     A função de liberação dos valores contidos nos elementos deve
*        assegurar a liberação de todos os espaços referênciados pelo
*        valor contido em um elemento.
*        Esta função é chamada antes de se desalocar um elemento
*        de uma lista.
*        Caso não seja necessário desalocar o valor referenciado pelo
*        elemento, o ponteiro para a função de liberação poderá ser NULL .
*        Caso o elemento da lista seja a única âncora do valor referenciado,
*        esta função deve promover a destruição (free) desse valor e
*        de todos os dados nele ancorados.
*
***************************************************************************/
 
#if defined( LISTA_OWN )
   #define LISTA_EXT
#else
   #define LISTA_EXT extern
#endif

/***** Declarações exportadas pelo módulo *****/

/* Tipo referência para uma lista */

typedef struct LIS_tagLista * LIS_tppLista ;


/***********************************************************************
*
*  $TC Tipo de dados: LIS Condições de retorno
*
*
*  $ED Descrição do tipo
*     Condições de retorno das funções da lista
*
***********************************************************************/

   typedef enum {

         LIS_CondRetOK ,
               /* Concluiu corretamente */

         LIS_CondRetListaVazia ,
               /* A lista não contém elementos */

         LIS_CondRetFimLista ,
               /* Foi atingido o fim de lista */

         LIS_CondRetNaoAchou ,
               /* Não encontrou o valor procurado */

         LIS_CondRetFaltouMemoria
               /* Faltou memória ao tentar criar um elemento de lista */

   } LIS_tpCondRet ;


/***********************************************************************
*
*  $FC Função: LIS  &Criar lista
*
*  $ED Descrição da função
*     Cria uma lista genérica duplamente encadeada.
*     Os possíveis tipos são desconhecidos a priori.
*     A tipagem é implicita.
*     Não existe identificador de tipo associado à lista.
*
*  $EP Parâmetros
*     ExcluirValor  - ponteiro para a função que processa a
*                     exclusão do valor referenciado pelo elemento
*                     a ser excluído.
*                     Ver descrição do módulo.
*
*  $FV Valor retornado
*     Se executou corretamente retorna o ponteiro para a lista.
*     Este ponteiro será utilizado pelas funções que manipulem esta lista.
*
*     Se ocorreu algum erro, por exemplo falta de memória ou dados errados,
*     a função retornará NULL.
*     Não será dada mais informação quanto ao problema ocorrido.
*
*  $EAE Assertivas de entrada
*     ExcluirValor ponteiro para umafunção que encarregue-se de excluir os
*        valores que serão usados na lista
*
*  $EAE Assertivas de saída
*     Retorna um ponteiro válido para a lista criada, caso tenha executado
*       corretamente.
*     Retorna NULL caso tenha ocorrido algum erro.
*
***********************************************************************/

   LIS_tppLista LIS_CriarLista(
             void   ( * ExcluirValor ) ( void * pDado ) ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Destruir lista
*
*  $ED Descrição da função
*     Destrói a lista fornecida.
*     O parâmetro ponteiro para a lista não é modificado.
*     Se ocorrer algum erro durante a destruição, a lista resultará
*     estruturalmente incorreta.
*     OBS. não existe previsão para possíveis falhas de execução.
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     A lista encontra-se destruída.
*     A memória de cada elemento é liberada.
*     Em caso de erros, a lista pode ficar estruturalmente incorreta.
*
***********************************************************************/

   void LIS_DestruirLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Esvaziar lista
*
*  $ED Descrição da função
*     Elimina todos os elementos, sem contudo eliminar a lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a ser esvaziada
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     A lista encontra-se esvaziada, com zero elementos.
*     A memória de cada elemento é liberada.
*
***********************************************************************/

   void LIS_EsvaziarLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento antes
*
*  $ED Descrição da função
*     Insere novo elemento antes do elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
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
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Se a lista anteriormente estava vazia, agora contém um elemento,
*         com valor pValor. O nó corrente torna-se este elemento.
*       Do contrário, a lista agora contém um elemento a mais, sendo este
*         inserido imediatamente antes do nó corrente. O nó corrente não
*         é modificado.
*     Se LIS_CondRetFaltouMemoria:
*       A lista não é modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoAntes( LIS_tppLista pLista ,
                                           void * pValor        ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Inserir elemento após
*
*  $ED Descrição da função
*     Insere novo elemento apás o elemento corrente.
*     Caso a lista esteja vazia, insere o primeiro elemento da lista.
*
*  $EP Parâmetros
*     Parâmetros
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
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       Se a lista anteriormente estava vazia, agora contém um elemento,
*         com valor pValor. O nó corrente torna-se este elemento.
*       Do contrário, a lista agora contém um elemento a mais, sendo este
*         inserido imediatamente após o nó corrente. O nó corrente não
*         é modificado.
*     Se LIS_CondRetFaltouMemoria:
*       A lista não é modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_InserirElementoApos( LIS_tppLista pLista ,
                                          void * pValor        )
       ;


/***********************************************************************
*
*  $FC Função: LIS  &Excluir elemento
*
*  $ED Descrição da função
*     Exclui o elemento corrente da lista dada.
*     Se existir o elemento aa esquerda do corrente será o novo corrente.
*     Se não existir e existir o elemento à direita, este se tornará corrente.
*     Se este também não existir a lista tornou-se vazia.
*
*  $EP Parâmetros
*     pLista    - ponteiro para a lista na qual deve excluir.
*
*  $FV Valor retornado
*     LIS_CondRetOK
*     LIS_CondRetListaVazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       A lista anteriormente não estava vazia, e agora contém um elemento a menos.
*       O elemento corrente é excluído, e seu valor é liberado.
*       Se existir o elemento a esquerda do antigo corrente, este será o novo corrente.
*       Senão, se existir o elemento à direita, este se tornará corrente.
*       Senão, a lista tornou-se vazia.
*     Se LIS_CondRetListaVazia:
*       A lista anteriormente estava vazia e não é modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_ExcluirElemento( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Obter referência para o valor contido no elemento
*
*  $ED Descrição da função
*     Obtem a referência para o valor contido no elemento corrente da lista
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista de onde se quer o valor
*
*  $FV Valor retornado
*     não NULL - se o elemento corrente existe
*     NULL     - se a lista estiver vazia
*                Pode retornar NULL se o valor inserido no elemento for NULL.
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se o retorno for NULL:
*       A lista está vazia, OU
*       O elemento inserido no nó corrente é NULL
*     Senão:
*       A lista não está vazia, e o retono é o elemento inserido no nó corrente.
*
***********************************************************************/

   void * LIS_ObterValor( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento inicial
*
*  $ED Descrição da função
*     Torna corrente o primeiro elemento da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se a lista estiver vazia:
*       A lista não é modificada.
*     Senão:
*       O nó corrente torna-se o primeiro nó.
*
***********************************************************************/

   void LIS_IrInicioLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Ir para o elemento final
*
*  $ED Descrição da função
*     Torna corrente o elemento final da lista.
*     Faz nada se a lista está vazia.
*
*  $EP Parâmetros
*     pLista - ponteiro para a lista a manipular
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se a lista estiver vazia:
*       A lista não é modificada.
*     Senão:
*       O nó corrente torna-se o último nó.
*
***********************************************************************/

   void LIS_IrFinalLista( LIS_tppLista pLista ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Avançar elemento
*
*  $ED Descrição da função
*     Avança o elemento corrente numElem elementos na lista
*     Se numElem for positivo avança em direção ao final
*     Se numElem for negativo avança em direção ao início
*     numElem pode ser maior do que o númro de elementos existentes na
*               direção desejada
*     Se numElem for zero somente verifica se a lista está vazia
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista a ser manipulada
*     numElem - o número de elementos a andar
*
*  $FV Valor retornado
*     LIS_CondRetOK         - se numElem elementos tiverem sido andados
*     LIS_CondRetFimLista   - se encontrou o fim da lista antes de andar numElem
*                         elementos
*     LIS_CondRetListaVazia - se a lista está vazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       A lista não estava vazia.
*       Se numElem == 0:
*         A lista não é modificada.
*       Se numElem > 0:
*         Foram andados numElem elementos em direção ao final sem problemas.
*       Se numElem < 0:
*         Foram andados numElem elementos em direção ao início sem problemas.
*     Se LIS_CondRetFimLista:
*       Se numElem > 0:
*         Foram andados um número menor de numElem elementos em direção ao final,
*         e chegou-se ao final.
*       Se numElem < 0:
*         Foram andados um número menor de numElem elementos em direção ao início,
*         e chegou-se ao início.
*     Se LIS_CondRetListaVazia:
*       A lista estava vazia e não é modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_AvancarElementoCorrente( LIS_tppLista pLista ,
                                              int numElem ) ;


/***********************************************************************
*
*  $FC Função: LIS  &Procurar elemento contendo valor
*
*  $ED Descrição da função
*     Procura o elemento que referencia o valor dado.
*     A função compara ponteiro e não conteúdo apontado.
*
*  $EP Parâmetros
*     pLista  - ponteiro para a lista onde procura
*     pValor  - ponteiro para o valor procurado
*               Pode ser NULL
*
*  $FV Valor retornado
*     LIS_CondRetOK  - se encontrou.
*                      O elemento corrente é o primeiro elemento do
*                      elemento corrente inclusive para o fim da lista
*                      e que contém o ponteiro procurado
*
*     LIS_CondRetNaoEncontrou - se o ponteiro não foi encontrado
*                      O elemento corrente continua o mesmo
*     LIS_CondRetListaVazia   - se a lista estiver vazia
*
*  $EAE Assertivas de entrada
*     pLista != NULL
*
*  $EAE Assertivas de saída
*     Se LIS_CondRetOK:
*       O novo nó corrente é o primeiro nó a partir do antigo corrente 
*       (inclusive) até o final da lista cujo valor é igual a pValor.
*     Se LIS_CondRetNaoEncontrou:
*       A lista não é modificada.
*     Se LIS_CondRetListaVazia:
*       A lista estava vazia e não é modificada.
*
***********************************************************************/

   LIS_tpCondRet LIS_ProcurarValor( LIS_tppLista pLista ,
                                    void * pValor        ) ;

#undef LISTA_EXT

/********** Fim do módulo de definição: LIS  Lista duplamente encadeada **********/

#else
#endif
