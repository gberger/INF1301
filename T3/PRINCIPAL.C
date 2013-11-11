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

#define MAXNOME 100
#define MAXNOME_S "100"

#include <stdio.h>
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
*  $TC Tipo de dados: PRN Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*	  listas de peças e classes de peças.
*
***********************************************************************/

   typedef struct PRN_tagSimulacao {

		TAB_tppTabuleiro pTab;
			   /* Ponteiro para o tabuleiro corrente */
		LIS_tppLista pListaPecas;
			   /* Ponteiro para a lista de peças */
		LIS_tppLista pListaClasses;
			   /* Ponteiro para a lista de classes de peças */

   } PRN_tpSimulacao ;


/*****  Variável global que armazena a simulação corrente  *****/

   PRN_tpSimulacao simulacao;


/***********************************************************************
*
*  $FC Função: PRN renderizar menu principal
*
*  $ED Descrição da função
*     Abre o menu principal na tela para o usuário, solicitando a escolha de uma opcao
*
*  $FV Valor retornado
*     PRN_CondRetOK
*
***********************************************************************/

   PRN_tpCondRet PRN_MenuPrincipal( int * opcao )
   {
		
		printf("01. Novo\n02. Abrir\n03. Salvar\n\n");
		printf("11. Listar tipos de peça\n12. Criar tipo de peça\n13. Alterar tipo de peça\n14. Excluir tipo de peça\n\n");
		printf("21. Listar peças\n22. Criar peça\n23. Alterar peça\n24. Excluir peça\n31. Checa-Cheque\n\n");
		printf("99. Sair\n\nDigite o codigo da opcao desejada:");

		scanf(" %d", opcao);

		while( *opcao < 1 || (*opcao > 3 && *opcao < 11) || (*opcao > 14 && *opcao < 21) || (*opcao > 24 && *opcao != 31 && *opcao != 99) )
		{
			printf("Opcao invalida. Tente novamente:\n");
			scanf(" %d", opcao);
		}

		return PRN_CondRetOK;
   }
		

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

   PRN_tpCondRet PRN_NovoTabuleiro( void )
   {
	   TAB_DestruirTabuleiro( simulacao.pTab );

	   if(TAB_CriarTabuleiro( &(simulacao.pTab) ) != TAB_CondRetOK) {
		   LIS_DestruirLista( simulacao.pListaClasses );
		   LIS_DestruirLista( simulacao.pListaPecas );
		   return PRN_CondRetFaltouMemoria;
	   }

	   LIS_EsvaziarLista( simulacao.pListaClasses );
	   LIS_EsvaziarLista( simulacao.pListaPecas );

	   return PRN_CondRetOK;
   }

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

   PRN_tpCondRet PRN_AbrirTabuleiro( void )
   {
	   char path[200];

	   printf("Digite o path do arquivo:\n");
	   scanf(" %[^\n]", path);

	   PRN_NovoTabuleiro( );

	   LerArquivo( path );

   }


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

   PRN_tpCondRet PRN_SalvarTabuleiro( void )
   {
	   CPC_tppClassePeca pClasse;
	   PEC_tppPeca pPeca;
	   int i, j, count, nMovs;
	   char * nome, auxString[200], ic;
	   PEC_tpJogador jogador;

	   printf("Digite o path do arquivo:\n");
	   scanf(" %[^\n]", auxString);
	   fp = fopen(auxString, "r");
	   if( !fp ) {
		   printf("Path inválido.\n\n");
		   return;
	   }

	   LIS_IrInicioLista( simulacao.pListaClasses );
	   while (LIS_ObterValor( simulacao.pListaClasses ) ) {
		   pClasse = (CPC_tppClassePeca) LIS_ObterValor( simulacao.pListaClasses );
			
		   CPC_ObterNome(pClasse, &nome);
		   fprintf(fp, "CLASSE %s\n", nome);
		   CPC_ObterNumeroMovimentos(pClasse, &nMovs);
		   for(count = 0; count < nMovs; count++) {
			   CPC_ObterMovimento( pClasse, count, &i, &j);
			   fprintf(fp, "MOV %d %d\n", i, j);
		   }
		if( LIS_AvancarElementoCorrente( simulacao.pListaClasses, 1 ) != LIS_CondRetOK )
				break;
	   }
	   

	   fprintf(fp, "TABULEIRO\n");
	   for( ic = 'A'; ic < 'I'; ic++) {
		   for( j = 1; j < 9; j++) {
			   TAB_DefinirCorrente(simulacao.pTab, ic, j);
			   TAB_ObterValorCorrente(simulacao.pTab, &pPeca);
			   if(pPeca == NULL)
				   continue;

			   PEC_ObterJogador(pPeca, &jogador);

			   PEC_ObterClassePeca(pPeca, &pClasse);
			   CPC_ObterNome(pClasse, &nome);

			   fprintf(fp, "%c %c %d %s\n", (jogador == JOGADOR_BRANCO) ? 'B' : 'P', ic, j, nome);
		   }
	   }
		   
   }

/***********************************************************************
*
*  $FC Função: PRN carregar padrao
*
*  $ED Descrição da função
*	  Carrega as classes de peças tradicionais do xadrez
*
***********************************************************************/

   void PRN_CarregaPadrao( void )
   {
	   LerArquivo( "default.xdz" );
   }

/***********************************************************************
*
*  $FC Função: PRN listar classes
*
*  $ED Descrição da função
*     Lista todas as possibilidades de pecas que podem ser inseridas no tabuleiro.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_ListarClasses( void )
   {
	   CPC_tppClassePeca pClasse;
	   char * nome;

	   printf("Lista de classes criadas:\n");

	   LIS_IrInicioLista( simulacao.pListaClasses );
	   while (LIS_ObterValor( simulacao.pListaClasses ) ) {
		   pClasse = (CPC_tppClassePeca) LIS_ObterValor( simulacao.pListaClasses );
			
		   CPC_ObterNome(pClasse, &nome);
		   printf("%s\n",nome);
		   
		if( LIS_AvancarElementoCorrente( simulacao.pListaClasses, 1 ) != LIS_CondRetOK )
				break;
	   }
   }

/***********************************************************************
*
*  $FC Função: PRN cria peca
*
*  $ED Descrição da função
*     Abre o menu para colocar uma peca no tabuleiro.
*
***********************************************************************/

   void PRN_CriarPeca( ) {

   	char coluna;
   	char nomeClasse[MAXNOME];
   	int linha;
   	PEC_tppPeca * ppPeca;
   	PEC_tppPeca * ppPecaAux;
   	PEC_tpJogador jogador;

   	printf("Criacao de Peca\n");
   	printf("Digite a classe da peca\n");

   	scanf(" %" MAXNOME_SP "[^ \n]",nomeClasse);

   	pClassePeca = PRN_ProcurarClasse(nomeClasse);

   	if(pClassePeca==NULL) { 
   		printf("Classe inexistente\n");
   		return;
   	}

   	printf("\nDigite 0 para peca do usuario e 1 para peca do computador\n");

   	scanf("%d", &jogador);
   
   	PEC_CriarPeca(ppPeca, pClassePeca, jogador);

   	if(ppPeca==NULL) {
   		printf("Falta de memoria ao criar peca");
   		return;
   	}

   	printf("Digite as coordenadas do tabuleiro onde a peca se encontra\n");
   	printf("Digite a coluna (A a H)\n");
   	scanf(" %1[A-H]",&coluna);
   	printf("Digite a linha (1 a 8)\n");
   	scanf("%d",&linha);

		if(TAB_DefinirCorrente( simulacao.pTab, coluna, linha )==TAB_CondRetPosicaoInvalida) {
			printf("Esta posicao nao existe!\n");
			return;
		}

		TAB_ObterValorCorrente( simulacao.pTab, ppPecaAux );

		if(ppPecaAux!=NULL) {
			printf("Ja existe uma peca nesta casa. Por favor, escolha outra.\n");
			return;
		}   	

		if(TAB_AtribuirValorCorrente( simulacao.pTab, *ppPeca)==TAB_CondRetFaltouMemoria) {
			printf("Erro de memoria ao atribuir peca ao local do tabuleiro");
			return;
		}

   	LIS_InserirElementoApos(simulacao.pListaPecas, *ppPeca);

   }

/***********************************************************************
*
*  $FC Função: PRN exclusao de peca
*
*  $ED Descrição da função
*     Exclui algum tipo de peca previamente definido pelo usuario.
*
***********************************************************************/

   void PRN_ExcluirPeca( ) {

		char coluna;
		int linha;
		PEC_tppPeca * ppPeca;

		printf("Digite as coordenadas do tabuleiro onde esta a peca que voce deseja deletar\n");
		printf("Digite a coluna (A a H)\n");
		scanf(" %1[A-H]",&coluna);
		printf("Digite a linha (1 a 8)\n");
		scanf("%d",&linha);

		if(TAB_DefinirCorrente( simulacao.pTab, coluna, linha )==TAB_CondRetPosicaoInvalida) {
			printf("Esta posicao nao existe!\n");
			return;
		}

		TAB_ObterValorCorrente( simulacao.pTab, ppPeca );
		   
		if(ppPeca==NULL) {
		   printf("Esta posicao nao contem uma peca!\n");
			return;
		}

		if(LIS_ProcurarValor( simulacao.pListaPecas, *ppPeca)==LIS_CondRetOk) {
			LIS_ExcluirElemento( simulacao.pListaPecas );
		} else {
			printf("Erro ao excluir peca da lista de pecas");
			PRN_Sair();
		}

		PEC_DestruirPeca(*ppPeca);

		printf("Peca destruida com sucesso!\n");

	}

/***********************************************************************
*
*  $FC Função: PRN funcao de inicialização
*
*  $ED Descrição da função
*     Inicializa a variável global, criando as estruturas necessárias.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   PRN_tpCondRet PRN_Inicializa( void )
   {
	   if( TAB_CriarTabuleiro( &(simulacao.pTab) ) != TAB_CondRetOK )
		   return PRN_CondRetFaltouMemoria;

	   simulacao.pListaClasses = LIS_CriarLista( DestruirClassePeca );
	   if( simulacao.pListaClasses == NULL ) {
		   TAB_DestruirTabuleiro( simulacao.pTab );
		   return PRN_CondRetFaltouMemoria;
	   }

	   simulacao.pListaPecas = LIS_CriarLista( DestruirPeca );
	   if( simulacao.pListaPecas == NULL ) {
		   TAB_DestruirTabuleiro( simulacao.pTab );
		   LIS_DestruirLista( simulacao.pListaClasses );
		   return PRN_CondRetFaltouMemoria;
	   }

	   return PRN_CondRetOK;
   }

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

/***********************************************************************
*
*  $FC Função: PRN main
*
*  $ED Descrição da função
*     Coordena a excecução do programa.
*
*  $FV Valor retornado
*     PRN_CondRetOK
*     PRN_CondRetFaltouMemoria
*
***********************************************************************/

   int main( void )
   {
	   int opcao;

	   if( PRN_Inicializa( ) == PRN_CondRetFaltouMemoria)
		   return PRN_CondRetFaltouMemoria;

	   do {
			PRN_MenuPrincipal( &opcao );
			switch(opcao) {
				case 1:
					PRN_NovoTabuleiro( );
				break;
				case 2:
					PRN_AbrirTabuleiro( );
				break;
				case 3:
					PRN_SalvarTabuleiro( );
				break;
		   }
	   } while( opcao != 99 );

	   PRN_Sair( );

	   return PRN_CondRetOK;
   }

/***********************************************************************
*
*  $FC Função: PRN - Le arquivo de configuracao
*
***********************************************************************/

   void LerArquivo( char * path )
   {
	   char auxString[200], jogador, i;
	   int j;
	   FILE *fp;
	   CPC_tppClassePeca pClasse;
	   PEC_tppPeca pPeca;

	   fp = fopen(path, "r");
	   if( !fp ) {
		   printf("Path inválido.\n\n");
		   return;
	   }

	   while( fscanf(fp, " %s", auxString) == 1 ) {
		   if( strcmp( auxString, "CLASSE") == 0 ) {
			   fscanf(fp, " %[^\n]", auxString);
			   if( CPC_CriarClassePeca(&pClasse, auxString) != CPC_CondRetOK) {
				   printf( "Faltou memória." );
				   PRN_Sair( );
			   }
			   LIS_InserirElementoApos(simulacao.pListaClasses, (void *) pClasse);

		   } else if( strcmp( auxString, "MOV") == 0 ) {
			   fscanf(fp, " %d %d", &i, &j);
			   if( CPC_AdicionarMovimento(pClasse, i, j) != CPC_CondRetOK) {
					printf( "Faltou memória." );
					PRN_Sair( );
			   }

		   } else if( strcmp( auxString, "TABULEIRO") == 0 ) {
			   while( scanf( " %c %c %d %[^\n]", &jogador, &i, &j, auxString) == 4) {
				   pClasse = PRN_ProcurarClasse( auxString );
				   if(!pClasse)
					   continue;
				   if( PEC_CriarPeca( &pPeca, pClasse, (jogador == 'B') ? JOGADOR_BRANCO : JOGADOR_PRETO ) != PEC_CondRetOK ) {
					   printf( "Faltou memória." );
					   PRN_Sair( );
				   }
				   TAB_DefinirCorrente(simulacao.pTab, i, j);
				   TAB_AtribuirValorCorrente(simulacao.pTab, pPeca);
			   }
		   }
	   }
   }
	
   void DestruirPeca( void * pValor )
   {
	   PEC_DestruirPeca( (PEC_tppPeca) pValor );
   }

   void DestruirClassePeca( void * pValor )
   {
	   CPC_DestruirClassePeca( (CPC_tppClassePeca) pValor );
   }

/********** Fim do módulo de implementação: Módulo principal **********/
