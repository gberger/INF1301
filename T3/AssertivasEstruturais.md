
As estruturas são:

- Grafo, que contém:
    - Cabeça do grafo
    - Vértice do grafo
    - Aresta do grafo
- Matriz, que contém:
    - Cabeça da matriz
- Tabuleiro, que contém:
	- Cabeça do tabuleiro
- Lista, que contém:
    - Cabeça da lista
    - Nó da lista
- Classe, peça que contém:
    - 
- Peca, que contém:
    - 
- Simulação, que contém
	- Cabeça da simulação


# Assertivas Estruturais

## Lista

	Seja `lista` um ponteiro para estrutura cabeça da lista

	Seja `no` um ponteiro para estrutura nó da lista

	Se `no->pProx != NULL`, então `no->pProx->pAnt == no`

	Se `no->pAnt != NULL`, então `no->pAnt->pProx == no`

	Se `lista->numElem == 0`, então

	 - `lista->pElemCorr == NULL`
	 - e `lista->pOrigemLista == NULL` 
	 - e `pFimLista == NULL`.

	Se `lista->numElem > 0`, então `lista->pElemCorr != NULL`

	Se `lista->numElem == 1`, então

	 -  `lista->pElemCorr == lista->pOrigemLista` 
	 -  e `lista->pOrigemLista == lista->pFimLista`


## Grafo

	Seja `grafo` um ponteiro para estrutura cabeça do grafo

	Seja `vertice` e `vertice2` ponteiros para estruturas vértice do grafo

	Se `grafo->pListaVertices->numElem > 0`, então `grafo->pVerticeCorrente != NULL`

	Se `grafo->pListaVertices->numElem == 1`, então `grafo->pVerticeCorrente == grafo->pListaVertices->pOrigemLista`

	Se `vertice` pertence a `grafo->pListaOrigens`, então `vertice` também pertence a `grafo->pListaVertices`

	Sempre `grafo->pVerticeCorrente` pertence a `grafo->pListaVertices`

	Se `vertice2` pertence a  `vertice->pListaAnt`, então existe uma aresta em `vertice2->pListaSuc` cujo `pVerticeApontado == vertice`

	Para toda aresta `a` em `vertice->pListaSuc`, `vertice` pertence a `a->pVerticeApontado->pListaAnt`


## Matriz
	Seja `matriz` um ponteiro para estrutura cabeça da matriz

	Se `matriz != NULL` então `matriz->pGrafo != NULL` e `pGrafo` aponta para estrutura cabeça de grafo, valendo as assertivas estruturais do grafo

	Sejam `i` e `j` as coordenadas vertical e horizontal, respectivamente, de um elemento da matriz, que variam entre `0` e `matriz->n - 1`

	Se `matriz != NULL` então `matriz->n > 0` e o grafo referenciado por `matriz->pGrafo` contém n*n vértices, onde o idVertice de cada vértice é dado por i * (matriz->pMatriz) + j

	Sejam `idVertice1` e `idVertice2` os identificadores de vértices distintos de `matriz->pMatriz`

	Se um vértice possui `idVertice1 >= matriz->n` então este possui uma aresta de id MAT_N que aponta para o vértice cujo `idVertice2 == idVertice1 - matriz->n`

	Se um vértice possui `idVertice1 < matriz->n * (matriz->n - 1)` então este possui uma aresta de id MAT_S que aponta para o vértice cujo `idVertice2 == idVertice1 + matriz->n`

	Se um vértice possui `(idVertice1 + 1) % (matriz->n) != 0` então este possui uma aresta de id MAT_L que aponta para o vértice cujo `idVertice2 == idVertice1 + 1`

	Se um vértice possui `idVertice1 % (matriz->n) != 0` então este possui uma aresta de id MAT_O que aponta para o vértice cujo `idVertice2 == idVertice1 - 1`


## Tabuleiro
	Seja `tabuleiro` um ponteiro para estrutura cabeça do tabuleiro

	Se `tabuleiro != NULL` então `tabuleiro->pMatriz` aponta para estrutura cabeça de matriz, onde valem as assertivas estruturais da matriz e a mesma é 8x8

	Se `tabuleiro != NULL` então `tabuleiro->i` possui valor entre 'A' e 'H' e `tabuleiro->j` possui valor entre 1 e 8

	Seja (X,Y) a posição corrente do tabuleiro

	Sempre `tabuleiro->i == X` e `tabuleiro->j == Y`

	Sempre a posição corrente da matriz terá suas coordenadas i e j dadas por `X - 'A'` e `Y - 1`, respectivamente

	Seja `pValor` o valor referenciado por uma posição do tabuleiro

	Se `pValor != NULL` então `pValor` aponta para estrutura cabeça de peça


## Simulação
	Seja `simulacao` um ponteiro para estrutura cabeça da simulação

	Se `simulacao->pTab != NULL` então `simulacao->pTab` aponta para estrutura cabeça do tabuleiro, valendo as assertivas estruturais do tabuleiro

	Se `simulacao->pListaClasses != NULL` então `simulacao->pListaClasses` aponta para estrutura cabeca da lista, onde valem as assertivas estruturais da lista e para os valores referenciados nesta lista, valem as assertivas estruturais de Classe

	Se `simulacao->pListaPecas != NULL` então
	 - `simulacao->pListaPecas` aponta para estrutura cabeca da lista, onde valem as assertivas estruturais da lista e para os valores referenciados nesta lista, valem as assertivas estruturais de Peça
	 - para cada estrutura cabeça de peça referenciada na lista em `simulacao->pListaPecas` a mesma deve estar referenciada por uma única posição do tabuleiro referenciado por `simulacao->pTab`
	 - para cada estrutura cabeça de peça referenciada na lista em `simulacao->pListaPecas` a mesma deve ser de uma classe referenciada em algum elemento de `simulacao->pListaClasses`



