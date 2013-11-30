O modelo físico está ilustrado no arquivo `Modelo`.

As estruturas são:

- Grafo, que contém:
    - Cabeça do grafo
    - Vértice do grafo
    - Aresta do grafo
- Vértice de string
- Lista, que contém:
    - Cabeça da lista
    - Nó da lista

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

## Assetivas adicionais para grafo auto-verificável

Para todo vértice `pVertice` referenciado em `pGrafo->pListaVertices`, `pVertice->pCabeca == pGrafo`

Para toda aresta `pAresta` referenciada em `pVerticeOrigem->pListaSuc`, `pAresta->pCabeca == pVerticeOrigem->pCabeca` e `pAresta->pCabeca == pAresta->pVerticeApontado->pCabeca`

Para todo vértice `pVertice`
- `pVertice->tamValor` é igual ao tamanho do espaço referenciado por `pVertice->pValor`
- `pVertice->idTipo` é igual ao identificador associado ao tipo de dados referenciado por `pVertice->pValor`

Sejam todos os `n` vértices `pVertice` de um grafo `pGrafo`
- Sempre `pGrafo->totalElem == n`
- Sempre `pGrafo->tamValores` será a soma de todos `pVertice->tamValor`

