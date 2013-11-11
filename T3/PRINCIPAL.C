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
#include <stdlib.h>
#include <string.h>

#include "TABULEIRO.H"
#include "LISTA.H"
#include "CLASSE_PECA.H"
#include "PECA.H"


/***********************************************************************
*
*  $TC Tipo de dados: PRN Descritor da cabeça de uma simulação
*
*
*  $ED Descrição do tipo
*     Armazena referências para o tabuleiro e para as cabeças das
*     listas de peças e classes de peças.
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

void PRN_Sair( int code ) {
    exit( code );
}

/***********************************************************************
*
*  $FC Função: Destruir Peça
*
*  $ED Descrição da função
*     Função generalizadora de PEC_DestruirPeca
*
***********************************************************************/

void DestruirPeca( void * pValor ) {
    PEC_DestruirPeca( (PEC_tppPeca) pValor );
}


/***********************************************************************
*
*  $FC Função: Destruir Classe Peça
*
*  $ED Descrição da função
*     Função generalizadora de CPC_DestruirClassePeca
*
***********************************************************************/

void DestruirClassePeca( void * pValor ) {
    CPC_DestruirClassePeca( (CPC_tppClassePeca) pValor );
}


/***********************************************************************
*
*  $FC Função: PRN procurar classe de peça
*
*  $ED Descrição da função
*     A partir da string dada, procura na lista de classes de peças
*        por uma classe com tal nome.
*
*  $FV Valor retornado
*     Ponteiro para a classe da peça encontrado, ou NULL se não achar
*
***********************************************************************/

CPC_tppClassePeca PRN_ProcurarClasse (char *nomeProcurado) {
    LIS_tpCondRet lisCondRet;
    CPC_tppClassePeca pClassePeca;
    char *nomeObtido;

    if(nomeProcurado == NULL) {
        return NULL;
    }

    LIS_IrInicioLista(simulacao.pListaClasses);

    do {
        pClassePeca = (CPC_tppClassePeca) LIS_ObterValor(simulacao.pListaClasses);

        if(pClassePeca != NULL) {
            CPC_ObterNome(pClassePeca, &nomeObtido);

            if(strcmp(nomeObtido, nomeProcurado) == 0) {
                return pClassePeca;
            }
        }

        lisCondRet = LIS_AvancarElementoCorrente(simulacao.pListaClasses, 1);
    } while(lisCondRet != LIS_CondRetFimLista && lisCondRet != LIS_CondRetListaVazia);

    return NULL;
}


/***********************************************************************
*
*  $FC Função: PRN - Le arquivo de configuracao
*
***********************************************************************/

void PRN_CarregarArquivoXdz( char * path ) {
    char auxString[200], jogador;
    int i, j;
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
                PRN_Sair( 1 );
            }
            LIS_InserirElementoApos(simulacao.pListaClasses, (void *) pClasse);

        } else if( strcmp( auxString, "MOV") == 0 ) {
            fscanf(fp, " %d %d", &i, &j);
            if( CPC_AdicionarMovimento(pClasse, i, j) != CPC_CondRetOK) {
                printf( "Faltou memória." );
                PRN_Sair( 1 );
            }

        } else if( strcmp( auxString, "TABULEIRO") == 0 ) {
            while( scanf( " %c %c %d %[^\n]", &jogador, &i, &j, auxString) == 4) {
                pClasse = PRN_ProcurarClasse( auxString );
                if(!pClasse)
                    continue;
                if( PEC_CriarPeca( &pPeca, pClasse, (jogador == 'B') ? JOGADOR_BRANCO : JOGADOR_PRETO ) != PEC_CondRetOK ) {
                    printf( "Faltou memória." );
                    PRN_Sair( 1 );
                }
                TAB_DefinirCorrente(simulacao.pTab, i, j);
                TAB_AtribuirValorCorrente(simulacao.pTab, pPeca);
            }
        }
    }

    fclose(fp);
}


/***********************************************************************
*
*  $FC Função: PRN procurar peça no tabuleiro
*
*  $ED Descrição da função
*     Procura a peça dada no tabuleiro corrente e bota nos ponteiros dados
*
*  $FV Valor retornado
*     1 se conseguiu encontrar a peça
*     0 se não conseguiu encontrar a peça
*
***********************************************************************/

int PRN_ProcurarPecaNoTabuleiro (PEC_tppPeca peca, char *i, int *j) {
    char ii, oldI;
    int jj, oldJ;
    PEC_tppPeca pecaObtida;

    TAB_ObterCorrente(simulacao.pTab, &oldI, &oldJ);

    for(ii = 'A'; ii <= 'H'; ii++) {
        for(jj = 1; jj <= 8; jj++) {
            TAB_DefinirCorrente(simulacao.pTab, ii, jj);
            TAB_ObterValorCorrente(simulacao.pTab, &pecaObtida);
            if(pecaObtida == peca) {
                TAB_DefinirCorrente(simulacao.pTab, oldI, oldJ);

                *i = ii;
                *j = jj;

                return 1;
            }
        }
    }

    return 0;
}


/***********************************************************************
*
*  $FC Função: PRN - Obter rei branco
*
*  $ED Descrição da função
*     Procura no tabuleiro a peça um classe de nome "Rei" que pertença
*       ao jogador branco.
*
*  $FV Valor Retornado
*     NULL caso não tenha achado
*     Ponteiro para a peça, caso tenha achado, e nesse caso o valor de i e de j
*       serão atualizados para conter a posição dessa peça no tabuleiro.
*
***********************************************************************/

PEC_tppPeca PRN_ObterReiBranco ( char * i, int * j ) {
    LIS_tpCondRet lisCondRet;
    PEC_tppPeca peca;
    PEC_tpJogador jogador;
    CPC_tppClassePeca classePeca, classeRei = PRN_ProcurarClasse("Rei");

    if(classeRei == NULL){
        return NULL;
    }

    LIS_IrInicioLista( simulacao.pListaPecas );
    do {

        peca = (PEC_tppPeca) LIS_ObterValor(simulacao.pListaPecas);
        PEC_ObterClassePeca(peca, &classePeca);
        PEC_ObterJogador(peca, &jogador)

        if(jogador == JOGADOR_BRANCO && classePeca == classeRei){
            if( PRN_ProcurarPecaNoTabuleiro(peca, &i, &j) ){
                return peca;
            }
        }

        lisCondRet = LIS_AvancarElementoCorrente(simulacao.pListaPecas, 1);
    } while(lisCondRet != LIS_CondRetFimLista && lisCondRet != LIS_CondRetListaVazia);

    return NULL;
}


/***********************************************************************
*
*  $FC Função: PRN checa se movimento é do tipo pulo
*
*  $ED Descrição da função
*     Checa se o movimento descrito pelos parâmetros é do tipo pulo ou não.
*     Se for um movimento vertical, horizontal ou diagonal, não é de pulo.  
*
*  $FV Valor retornado
*     1 se o movimento é pulo
*     0 se o movimento não é pulo
*
***********************************************************************/

int PRN_ChecarMovimentoPulo (int movI, int movJ) {
    if(movI < 0) {
        movI = -movI;
    }
    if(movJ < 0) {
        movJ = -movJ;
    }

    return movI == movJ ? 0 : 1;
}


/***********************************************************************
*
*  $FC Função: PRN checar legalidade de movimento
*
*  $ED Descrição da função
*     Checa se um movimento é legal, CHECANDO SOMENTE OBSTACULOS NO CAMINHO
*       E CONFLITOS DE DESTINO COM PEÇAS DO MESMO JOGADOR.
*     ASSUME-SE QUE O MOVIMENTO PRIMITIVO É UM MOVIMENTO VÁLIDO PARA A
*       CLASSE DA PEÇA NA ORIGEM.
*
*  $FV Valor retornado
*     1 se o movimento é legal
*     0 se o movimento é ilegal
*
***********************************************************************/

int PRN_ChecarLegalidade (PEC_tpJogador jogador, char iOrigem, int jOrigem, char iDestino, int jDestino) {
    PEC_tppPeca defensor;
    PEC_tpJogador jogadorDefensor;
    PEC_tppPeca obstaculo;
    int movI, movJ;
    char i; int j;

    movI = iDestino - iOrigem;
    movJ = jDestino - jOrigem;

    TAB_ObterValorDeCasa(simulacao.pTab, &defensor, iDestino, iOrigem);

    // Se tentar mover uma peça de um jogador para uma casa que está ocupada por
    // uma peça do mesmo jogador, não é um movimento legal.
    // (não é permitido comer peças próprias)
    if( defensor != NULL ) {
        PEC_ObterJogador(defensor, &jogadorDefensor);
        if(jogadorDefensor == jogador){
            return 0;
        }
    }

    //
    if(PRN_ChecarMovimentoPulo(movI, movJ) == 1) {
        // Sendo um movimento de pulo, não há necessidade de checar obstáculos
        // Logo, o movimento é válido

        return 1;
    }

    // Não sendo um movimento de pulo, precisamos saber se há obstáculos.

    if( movJ == 0 ) {
        if( movI > 0 ) {
            // movimento de letra crescente
            j = jOrigem; // = jDestino;

            for( i = iOrigem + 1; i < iDestino; i++ ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        } 
        if ( movI < 0 ) {
            // movimento de letra decrescente
            j = jOrigem; // = jDestino;

            for( i = iOrigem - 1 ; i > iDestino; i-- ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
    }   

    if( movI == 0 ) {
        if( movJ > 0 ) {
            // movimento de numero crescente
            i = iOrigem; // = iDestino;

            for( j = jOrigem + 1; j < jDestino; j++ ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        } 
        if ( movJ < 0 ) {
            // movimento de numero decrescente
            i = iOrigem; // = iDestino;

            for( j = jOrigem - 1; j > jDestino; j-- ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
    } 

    if( movJ > 0 ) {
        if( movI > 0 ) {
            // movimento de letra e numero crescente
            for( i = iOrigem + 1, j = jOrigem + 1; i < iDestino && j < jDestino; i++, j++ ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
        else {
            //movimento de letra crescente e numero decrescente
            for( i = iOrigem - 1, j = jOrigem + 1; i > iDestino && j < jDestino; i--; j++ ) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
    }

    else { 
        if( movI > 0 ) {
            // movimento de letra decrescente e numero crescente
            for( i = iOrigem + 1, j = jOrigem - 1; i < iDestino && j > jDestino; i++, j--) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
        else {
            // movimento de letra e numero decrescente
            for( i = iOrigem - 1, j = jOrigem - 1; i > iDestino && j > jDestino; i--, j--) {
                TAB_ObterValorDeCasa(i, j, &obstaculo);
                if(obstaculo != NULL){
                    return 0;
                }
            }

            return 1;
        }
    }

    return 1;
}

/***********************************************************************
*
*  $FC Função: PRN renderizar menu principal
*
*  $ED Descrição da função
*     Mostra o menu principal na tela para o usuário, solicitando a escolha de uma opcao.
*
***********************************************************************/

void PRN_MenuPrincipal( int * opcao ) {
    printf("\n=== MENU ===\n\n");
    printf("01. Novo\n02. Abrir\n03. Salvar\n09. Mostra diretorio atual.\n\n");
    printf("11. Listar classes de peca\n12. Criar classe de peca\n\n");
    printf("21. Listar pecas\n22. Criar peca\n23. Alterar peca\n24. Excluir peca\n\n");
    printf("31. Exibir tabuleiro.\n32. Checar Xeque-mate\n\n");
    printf("99. Sair\n\nDigite o codigo da opcao desejada: \n> ");

    scanf(" %d", opcao);
}


/***********************************************************************
*
*  $FC Função: PRN criar novo tabuleiro
*
*  $ED Descrição da função
*     Cria um tabuleiro e permite o usuario alocar as pecas onde ele achar necessario.
*
***********************************************************************/

void PRN_NovoTabuleiro( void ) {
    char certeza;

    printf("Voce tem certeza? Suas alteracoes nao serao salvas. (S/N)\n> ");
    scanf(" %c", &certeza);

    if(!(certeza == 'S' || certeza == 's' || certeza == '1' || certeza == 'y' || certeza == 'Y')) {
        return;
    }

    TAB_DestruirTabuleiro( simulacao.pTab );

    if(TAB_CriarTabuleiro( &(simulacao.pTab) ) != TAB_CondRetOK) {
        LIS_DestruirLista( simulacao.pListaClasses );
        LIS_DestruirLista( simulacao.pListaPecas );

        printf("ERRO AO CRIAR TABULEIRO");
        PRN_Sair(1);
    }

    LIS_EsvaziarLista( simulacao.pListaClasses );
    LIS_EsvaziarLista( simulacao.pListaPecas );

    printf("O tabuleiro foi zerado.");
}

/***********************************************************************
*
*  $FC Função: PRN abrir tabuleiro
*
*  $ED Descrição da função
*     Abre um tabuleiro com as configuracoes previamente salvas.
*
***********************************************************************/

void PRN_AbrirTabuleiro( void ) {
    char path[200];

    printf("Digite o path do arquivo:\n");
    scanf(" %[^\n]", path);

    PRN_NovoTabuleiro( );

    PRN_CarregarArquivoXdz( path );
}


/***********************************************************************
*
*  $FC Função: PRN salvar tabuleiro
*
*  $ED Descrição da função
*     Salva as configuracoes de um tabuleiro para ser utilizado mais tarde.
*
***********************************************************************/

void PRN_SalvarTabuleiro( void ) {
    CPC_tppClassePeca pClasse;
    PEC_tppPeca pPeca;
    int i, j, count, nMovs;
    char * nome, auxString[200], ic;
    PEC_tpJogador jogador;
    FILE *fp;

    printf("Digite o path do arquivo:\n");
    scanf(" %[^\n]", auxString);
    fp = fopen(auxString, "w");
    if( !fp ) {
        printf("Path inválido.");
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
    for( ic = 'A'; ic <= 'H'; ic++) {
        for( j = 1; j <= 8; j++) {
            TAB_ObterValorDeCasa(simulacao.pTab, &pPeca, ic, j);
            if(pPeca == NULL)
                continue;

            PEC_ObterJogador(pPeca, &jogador);

            PEC_ObterClassePeca(pPeca, &pClasse);
            CPC_ObterNome(pClasse, &nome);

            fprintf(fp, "%c %c %d %s\n", (jogador == JOGADOR_BRANCO) ? 'B' : 'P', ic, j, nome);
        }
    }

    fclose(fp);
}

/***********************************************************************
*
*  $FC Função: PRN carregar padrao
*
*  $ED Descrição da função
*     Carrega as classes de peças tradicionais do xadrez
*
***********************************************************************/

void PRN_CarregaPadrao( void ) {
    PRN_CarregarArquivoXdz( "default.xdz" );
}

/***********************************************************************
*
*  $FC Função: PRN listar classes
*
*  $ED Descrição da função
*     Lista todas as possibilidades de pecas que podem ser inseridas no tabuleiro.
*
***********************************************************************/

void PRN_ListarClasses( void ) {
    CPC_tppClassePeca pClasse;
    char * nome;
    int count, nMovs;
    int movI, movJ;

    printf("Lista de classes criadas:\n");

    LIS_IrInicioLista( simulacao.pListaClasses );
    while (LIS_ObterValor( simulacao.pListaClasses ) ) {
        pClasse = (CPC_tppClassePeca) LIS_ObterValor( simulacao.pListaClasses );

        CPC_ObterNome(pClasse, &nome);
        printf("* %s ",nome);

        CPC_ObterNumeroMovimentos(pClasse, &nMovs);
        for(count = 0; count < nMovs; count++) {
            CPC_ObterMovimento( pClasse, count, &movI, &movJ);
            printf("{%d,%d} ", movI, movJ);
        }

        printf("\n");

        if( LIS_AvancarElementoCorrente( simulacao.pListaClasses, 1 ) != LIS_CondRetOK )
            break;
    }

    printf("<fim>");
}


/***********************************************************************
*
*  $FC Função: PRN cria classe de peça
*
*  $ED Descrição da função
*     Abre o menu para criar uma nova classe de peça.
*
***********************************************************************/

void PRN_CriarClasse( void ) {
    char nomeClasse[MAXNOME];
    int movI, movJ;
    CPC_tppClassePeca pClassePeca;


    printf("Criacao de Classe de Peca\n");
    printf("Digite o nome da nova classe de peca\n> ");

    scanf(" %" MAXNOME_S "[^ \n]", nomeClasse);

    if(PRN_ProcurarClasse(nomeClasse) != NULL) { 
        printf("Classe com esse nome ja existe\n");
        return;
    }

    CPC_CriarClassePeca(&pClassePeca, nomeClasse);

    if(pClassePeca == NULL) {
        printf("Erro de memoria ao alocar nova classe de peca.");
        PRN_Sair(1);
    }

    printf("Agora serao cadastrados os movimentos dessa classe criada.\n"
           "Um movimento contem uma componente em X em uma em Y.\n"
           "Um conjunto de movimentos indicam a totalidade das jogadas possiveis de uma peca.\n"
           "Por exemplo, uma peca que so se move uma casa para a frente tera somente um movimento: {0,1}.\n"
           "Ja uma casa que se move qualquer numero de casas para a direita ou para tras tera os movimentos:\n"
           "{1,0}, {2,0} ... {7,0} e {0,-1}, {0,-2} ... {0,-7}.\n"
           "Vale lembrar que, ja que o tabuleiro de xadrez tem dimensao 8x8, os componentes de movimentos devem ser inteiros entre -7 e 7.\n")

    while(1) {
        printf("Novo movimento. Digite as componentes do movimento (ou 0 e 0 para acabar).\n");
        printf("Digite a componente horizontal do movimento (entre -7 e 7)\n> ");
        scanf(" %d", &movI);
        printf("Digite a componente vertical do movimento (entre -7 e 7)\n> ");
        scanf(" %d", &movJ);

        if(movI == 0 && movJ == 0) {
            break;
        }
        if(movI > 7 || movI < -7 || movJ > 7 || movJ < -7) {
            break;
        }

        if( CPC_AdicionarMovimento(pClassePeca, movI, movJ) == CPC_CondRetFaltouMemoria) {
            printf("Erro de memoria ao adicionar movimento.");
            PRN_Sair(1);
        }
    };

    LIS_IrFinalLista(simulacao.pListaClasses);
    LIS_InserirElementoApos(simulacao.pListaClasses, pClassePeca);

}


/***********************************************************************
*
*  $FC Função: PRN lista peças
*
*  $ED Descrição da função
*     Lista as peças inseridas no tabuleiro.
*
***********************************************************************/

void PRN_ListarPecas( ) {
    CPC_tppClassePeca pClasse;
    PEC_tppPeca pPeca;
    int j;
    char * nome, ic;
    PEC_tpJogador jogador;

    printf("Lista de pecas criadas:\n");

    for( ic = 'A'; ic <= 'H'; ic++) {
        for( j = 1; j <= 8; j++) {
            TAB_ObterValorDeCasa(simulacao.pTab, &pPeca, ic, j);
            if(pPeca == NULL)
                continue;

            PEC_ObterJogador(pPeca, &jogador);
            PEC_ObterClassePeca(pPeca, &pClasse);
            CPC_ObterNome(pClasse, &nome);

            printf("* [%c] %c%d %s\n", (jogador == JOGADOR_BRANCO) ? 'B' : 'P', ic, j, nome);
        }
    }
    printf("<fim>");
}

/***********************************************************************
*
*  $FC Função: PRN cria peca
*
*  $ED Descrição da função
*     Abre o menu para colocar uma peca no tabuleiro.
*
***********************************************************************/

void PRN_CriarPeca( ) 
{
    char coluna;
    char nomeClasse[MAXNOME];
    int linha;
    PEC_tppPeca pPeca;
    PEC_tppPeca pPecaAux;
    PEC_tpJogador jogador;
    CPC_tppClassePeca pClassePeca;

    printf("Criacao de Peca\n");
    printf("Digite a classe da peca (case sensitive)\n> ");

    scanf(" %" MAXNOME_S "[^ \n]",nomeClasse);

    pClassePeca = PRN_ProcurarClasse(nomeClasse);

    if(pClassePeca==NULL) { 
        printf("Classe inexistente\n");
        return;
    }

    printf("\nDigite 0 para peca do usuario (BRANCO) ou 1 para peca do computador (PRETO)\n> ");

    scanf("%d", &jogador);

    PEC_CriarPeca(&pPeca, pClassePeca, jogador);

    if(pPeca==NULL) {
        printf("Falta de memoria ao criar peca");
        return;
    }

    printf("Digite as coordenadas do tabuleiro onde a peca se encontra\n");
    printf("Digite a coluna (A a H)\n> ");
    scanf(" %c", &coluna);
    printf("Digite a linha (1 a 8)\n> ");
    scanf(" %d", &linha);

    if(TAB_DefinirCorrente( simulacao.pTab, coluna, linha ) == TAB_CondRetPosicaoInvalida) {
        printf("Esta posicao nao existe!\n");
        return;
    }

    TAB_ObterValorCorrente( simulacao.pTab, &pPecaAux );

    if(pPecaAux != NULL) {
        printf("Ja existe uma peca nesta casa. Por favor, escolha outra.\n");
        return;
    }       

    if(TAB_AtribuirValorCorrente( simulacao.pTab, pPeca) == TAB_CondRetFaltouMemoria) {
        printf("Erro de memoria ao atribuir peca ao local do tabuleiro");
        PRN_Sair(1);
    }

    if(LIS_InserirElementoApos(simulacao.pListaPecas, pPeca) == LIS_CondRetFaltouMemoria) {
        printf("Erro de memoria ao inserir peca na lista de pecas");
        PRN_Sair(1);
    }

}


/***********************************************************************
*
*  $FC Função: PRN altera peça
*
*  $ED Descrição da função
*     Abre o menu para alterar uma peça.
*
***********************************************************************/

void PRN_AlterarPeca( ) {

    char coluna, coluna2;
    int linha, linha2, opcao;
    PEC_tppPeca pPeca, pPecaAux;
    CPC_tppClassePeca pClassePeca;
    char nomeClasse[MAXNOME];

    printf("Digite as coordenadas do tabuleiro onde esta a peca que voce deseja alterar\n");
    printf("Digite a coluna (A a H)\n> ");
    scanf(" %c", &coluna);
    printf("Digite a linha (1 a 8)\n> ");
    scanf("%d", &linha);

    if(TAB_DefinirCorrente( simulacao.pTab, coluna, linha ) == TAB_CondRetPosicaoInvalida) {
        printf("Esta posicao nao existe!\n");
        return;
    }

    TAB_ObterValorCorrente( simulacao.pTab, &pPeca );

    if(pPeca == NULL) {
        printf("Esta posicao nao contem uma peca!\n");
        return;
    }

    printf("O que voce deseja alterar?\n");
    printf("1 - Posicao\n2 - Classe\n> ");
    scanf(" %d", &opcao);

    if(opcao == 1) {
        printf("Digite as novas coordenadas da peca\n");
        printf("Digite a coluna (A a H)\n> ");
        scanf(" %c", &coluna2);
        printf("Digite a linha (1 a 8)\n> ");
        scanf(" %d", &linha2);

        if(TAB_DefinirCorrente( simulacao.pTab, coluna2, linha2 ) == TAB_CondRetPosicaoInvalida) {
            printf("Esta posicao nao existe!\n");
            return;
        }

        TAB_ObterValorCorrente( simulacao.pTab, &pPecaAux );

        if(pPecaAux != NULL) {
            printf("Ja existe uma peca nesta casa. Por favor, escolha outra.\n");
            return;
        }       

        TAB_MoverValor(simulacao.pTab, coluna, linha, coluna2, linha2);

    } 
    else if(opcao == 2) {
        printf("Digite o nome da nova classe da peca\n> ");

        scanf(" %" MAXNOME_S "[^ \n]",nomeClasse);

        pClassePeca = PRN_ProcurarClasse(nomeClasse);

        if(pClassePeca==NULL) { 
            printf("Classe inexistente\n");
            return;
        }

        PEC_AtribuirClassePeca(pPeca, pClassePeca);
    }

}

/***********************************************************************
*
*  $FC Função: PRN exclui de peca
*
*  $ED Descrição da função
*     Abre o menu para excluir uma peça do tabuleiro.
*
***********************************************************************/

void PRN_ExcluirPeca( ) {

    char coluna;
    int linha;
    PEC_tppPeca pPeca;

    printf("Digite as coordenadas do tabuleiro onde esta a peca que voce deseja deletar\n");
    printf("Digite a coluna (A a H)\n> ");
    scanf(" %c", &coluna);
    printf("Digite a linha (1 a 8)\n> ");
    scanf("%d", &linha);

    if(TAB_DefinirCorrente( simulacao.pTab, coluna, linha ) == TAB_CondRetPosicaoInvalida) {
        printf("Esta posicao nao existe!\n");
        return;
    }

    TAB_ObterValorCorrente( simulacao.pTab, &pPeca );

    if(pPeca == NULL) {
        printf("Esta posicao nao contem uma peca!\n");
        return;
    }

    if(LIS_ProcurarValor( simulacao.pListaPecas, pPeca) == LIS_CondRetOK) {
        LIS_ExcluirElemento( simulacao.pListaPecas );
    } else {
        printf("Erro ao excluir peca da lista de pecas");
        PRN_Sair( 1 );
    }

    PEC_DestruirPeca(pPeca);

    printf("Peca destruida com sucesso!\n");
}


/***********************************************************************
*
*  $FC Função: PRN exibir tabuleiro
*
*  $ED Descrição da função
*     Exibe a configuracao atual do tabuleiro
*
***********************************************************************/

void PRN_ExibirTabuleiro( ) {
    char i;
    int j;
    PEC_tppPeca pPeca;
    PEC_tpJogador jogador;

    printf("Uma letra B indica uma peca branca. Uma letra P indica uma peca preta.\n\n");
    printf("  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |   \n"
        "  +-------------------------------+\n");

    for(i = 'H'; i >= 'A'; i--) {
        printf("%c |", i);
        for(j = 1; j <= 8; j++) {
            TAB_ObterValorDeCasa(simulacao.pTab, &pPeca, i, j);

            if(pPeca == NULL) {
                printf("   |");
            } else {
                PEC_ObterJogador(pPeca, &jogador);
                if(jogador == JOGADOR_BRANCO) {
                    printf(" B |");
                } else {
                    printf(" P |");
                }
            }
        }
        printf("\n");
        printf("  +-------------------------------+\n");
    }

    PRN_ListarPecas();

}

/***********************************************************************
*
*  $FC Função: PRN checar xeque
*
*  $ED Descrição da função
*     Função auxiliar que verifica se o rei branco está ameaçado pelas peças pretas.
*
*  $FV Valor retornado
*     1, caso esteja
*     0, caso contrário
*
***********************************************************************/


int PRN_ChecarAmeacaReiBranco ( ) {
    // 


    return 1;
}

/***********************************************************************
*
*  $FC Função: PRN checar xeque-mate
*
*  $ED Descrição da função
*     Verifica se a configuração do tabuleiro configura um xeque-mate.
*     Dá informacoes para o usuário sobre o xeque-mate.
*
***********************************************************************/

void PRN_ChecarXequeMate( ) {
    char reiI; int reiJ;
    PEC_tppPeca rei;

    char i, iDest;
    int j, jDest;
    PEC_tppPeca pecaAtual, pPecaComida;
    PEC_tpJogador jogadorDaPecaAtual;
    CPC_tppClassePeca classeDaPecaAtual;
    LIS_tpCondRet lisCondRet;

    int nMovs, i, movI, movJ;

    
    // Primeiro, precisamos ter um rei válido
    rei = PRN_ObterReiBranco(&reiI, &reiJ);
    if(rei == NULL) {
        printf("Nao foi encontrado uma peca com a classe 'Rei' que pertenca "
               "ao jogador branco e que esteja posicionado no tabuleiro.\n"
               "Por favor, ajuste o cenario do tabuleiro e tente novamente.");
        return;
    }

    // CHECAR XEQUE
    // Um pré-requisito para estar em xeque-mate é estar em xeque. Vamos checar essa condição.
    // O jogador branco está (no mínimo) em xeque caso o rei branco esteja ameaçado e seja a vez do jogador branco.
    if( PRN_ChecarAmeacaReiBranco() == 0) {
        printf("O cenario configurado nao eh de xeque-mate (e nem de xeque).");
        return;
    }

    // Agora, precisamos ver se ha algum movimento que possa ser feito que deixe o rei branco fora de ameaça.
    // Para cada casa do tabuleiro, vamos ver se contém uma peça branca; se sim, vamos realizar cada um  
    // de seus movimentos, retornando o tabuleiro para a posição inicial após cada movimento realizado.
    // Depois de cada movimento, será verificado se a posição ainda configura ameaça para o rei branco. 
    // Se houver algum movimento possível que deixe o rei branco fora de perigo, o jogador branco não
    // está em xeque-mate. Caso contrário, ele está em xeque-mate.
    for(i = 'A'; i <= 'H'; i++) {
        for(j = 1; j <= 8; j++) {
            TAB_ObterValorDeCasa( simulacao.pTab, &pecaAtualCorrente, i, j );

            if( pecaAtual != NULL ) {
                PEC_ObterJogador( pecaAtual, &jogadorDaPecaAtual );

                if( jogadorDaPecaAtual == JOGADOR_BRANCO) {
                    PEC_ObterClassePeca( pecaAtual, &classeDaPecaAtual );

                    if( classeDaPecaAtual == NULL ){
                        printf("Erro: peca com classe nula.");
                        PRN_Sair(1);
                    }

                    CPC_ObterNumeroMovimentos( classeDaPecaAtual, &nMovs );

                    for(i = 0; i < nMovs; i++){
                        CPC_ObterMovimento( classeDaPecaAtual, i, &movI, &movJ );

                        iDest = i + movI;
                        jDest = j + movJ;

                        if(TAB_ChecarPosicaoValida(iDest, jDest) == TAB_CondRetOK) {

                            //checar se movimento eh legal
                            if( PRN_ChecarLegalidade( jogadorDaPecaAtual, i, j, iDest, jDest) == 1 ) {

                                TAB_MoverValor( simulacao.pTab, i, j, iDest, jDest, &pPecaComida);

                                if(PRN_ChecarAmeacaReiBranco() == 0){
                                    printf("O jogador branco esta em xeque, mas nao em xeque-mate.\n"
                                           "Movimento: %c%d para %c%d.", iOrig, jOrig, iDest, jDest);
                                    return;
                                }

                                TAB_DesMoverValor( simulacao.pTab, i, j, iDest, jDest, pPecaComida);
                            }
                        }
                    }
                }
            }
        }
    }

    printf("O jogador branco esta em xeque-mate.");

    return;
}


/***********************************************************************
*
*  $FC Função: PRN funcao de inicialização
*
*  $ED Descrição da função
*     Inicializa a variável global, criando as estruturas necessárias.
*
***********************************************************************/

void PRN_Inicializa( void ) {
    if( TAB_CriarTabuleiro( &(simulacao.pTab) ) != TAB_CondRetOK ) {
        printf("ERRO DE MEMORIA AO CRIAR TABULEIRO");
        exit(1);
    }

    simulacao.pListaClasses = LIS_CriarLista( DestruirClassePeca );
    if( simulacao.pListaClasses == NULL ) {
        TAB_DestruirTabuleiro( simulacao.pTab );
        printf("ERRO DE MEMORIA AO CRIAR LISTA DE CLASSES");
        exit(1);
    }

    simulacao.pListaPecas = LIS_CriarLista( DestruirPeca );
    if( simulacao.pListaPecas == NULL ) {
        TAB_DestruirTabuleiro( simulacao.pTab );
        LIS_DestruirLista( simulacao.pListaClasses );
        printf("ERRO DE MEMORIA AO CRIAR LISTA DE PECAS");
        exit(1);
    }
}


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

int main( void ) {
    int opcao;

    PRN_Inicializa( );
    PRN_CarregaPadrao( );

    printf("TRABALHO 3 DE PROGRAMACAO MODULAR - 2013.2\n"
        "AUTORES: Felipe Luiz, Guilherme Berger e Joao Vicente\n"
        "Bem-vindo ao verificador de Xeque-mate!\n"
        "O jogador com o rei em perigo e' o branco.\n"
        "Use as opcoes do menu para construir o cenario desejado.\n"
        "Ja existem as classes de peca padrao do xadrez: Rei, Torre, Bispo, Cavalo e Rainha.\n"
        "O jogador em perigo deve possuir somente um Rei para o Xeque-mate ser verificado.\n");

    do {
        printf("\n(pressione qualquer tecla para exibir o menu)");
        getch();
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
            case 9:
            system("dir");
            break;
            case 11:
            PRN_ListarClasses( );
            break;
            case 12:
            PRN_CriarClasse( );
            break;
            case 21:
            PRN_ListarPecas( );
            break;
            case 22:
            PRN_CriarPeca( );
            break;
            case 23:
            PRN_AlterarPeca( );
            break;
            case 24:
            PRN_ExcluirPeca( );
            break;
            case 31:
            PRN_ExibirTabuleiro( );
            break;
            case 32:
            PRN_ChecarXequeMate( );
            break;
        }
    } while( opcao != 99 );

    PRN_Sair( 0 );

    return 0;
}


/********** Fim do módulo de implementação: Módulo principal **********/
