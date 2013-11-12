Argumentação de corretude para a função PEC_CriaPeca(), no módulo PECA.

A função recebe três parâmetros:

 -Um ponteiro para um ponteiro para um tipo peça.
 -Um ponteiro para um tipo classe de peça.
 -Um tipo jogador.
 
O ponteiro para o ponteiro de tipo peça deve ser nulo, a fim de evitar estruturas sem apontamento na memória.

A função sempre retorna uma das seguintes condições de retorno para o tipo peça:

 -Ponteiro nulo
 -Falta de memória
 -OK

Com o ponteiro para o tipo de classe apontando para null, a função não pode transferir este valor para
a instância de peça criada. Logo ela retorna a condição de ponteiro nulo.

A única alocação dinâmica necessária para realizar a função é verificada a fim de saber se ela retornou
um ponteiro nulo. Caso isto ocorra a função retorna a condição de falta de memória, impedindo a execução
incorreta dos comandos restantes.

A função não pode gerar erros de atribuição do tipo de jogador a peça, visto que ela recebe uma instância do tipo
jogador (que, naturalmente, deve ser válida) e não um ponteiro.

A atribuicão da nova peça através da passagem por referência também não irá gerar erros pois o único
caso passível (que seria falta de memória) já foi tratado anteriormente. 

Tendo não ocorrido erros de parametro nulo ou falta de memória, a função irá alocar com sucesso a nova
peça, então é responsabilidade do usuário utilizar um ponteiro para um ponteiro que não esteja nulo para
evitar que uma estrutura fique sem apontamento. Seria uma má pratica impedir a execução da função sendo que
a tarefa para a qual ela é feita (alocar a peça), funcionaria sem maiores problemas.
