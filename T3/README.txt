3º Trabalho de Programação Modular
==================================

- Tema: verificador de xeque-mate
- Período: 2013.2
- Professor: Flávio Bevilacqua
- Componentes do grupo:
    - 1210586, Felipe Luiz, ferocha@globo.com
    - 1210518, Guilherme Berger, guilherme.berger@gmail.com
    - 1210573, João Vicente, joao_kubo_@hotmail.com

Xadrez e Xeque-Mate
===================

O objetivo deste trabalho foi permitir ao usuário que verifique se uma configuração do tabuleiro de xadrez é um xeque-mate.

Para isso, é necessário que o usuário crie e posicione peças no tabuleiro. Tais peças podem ter movimentos personalizados, até mesmo diferentes dos do xadrez.

Através das opções numéricas apresentadas pelo programa, é possível cadastrar classes de peças, que tem um nome e uma série de movimentos. Por exemplo, a classe "Torre" tem todos os movimentos horizontais e verticais possíveis.

Um movimento contem uma componente vertical e um horizontal. Um conjunto de movimentos indicam a totalidade das jogadas possiveis de uma peça. 

Por exemplo, uma peca que so se move uma casa para a frente tera somente um movimento: {0,1}.

Ja uma casa que se move qualquer numero de casas para a direita ou para tras tera os movimentos: Vale lembrar que, ja que o tabuleiro de xadrez tem dimensao 8x8, os componentes de movimentos devem ser inteiros entre -7 e 7.

Também deve-se prestar atenção que, para as peças pretas, os movimentos são "invertidos", já que são calculados na perspectiva do jogador preto.

Há o conceito de movimento de pulo: qualquer movimento que não seja horizontal, vertical ou diagonal é um movimento que permite que a peça pule outras peças. Por exemplo, o cavalo possui somente movimentos de pulo.

Após cadastrar uma classe de peça, o usuário, pode criar uma peça com tal classe e posicioná-la no tabuleiro.

Se mudar de ideia, o usuário pode alterar a posição ou a classe da peça, ou até mesmo excluí-la. Se desejar mudar os movimentos de uma peça já posicionada, o usuário deve antes certificar-se de que há uma classe que realize os novos movimentos desejados.

É possível salvar a configuração das classes e das peças no tabuleiro em um arquivo. Posteriormente, esse arquivo pode ser carregado pelo programa para retornar ao cenário salvo.

Na inicialização é carregado o arquivo `default.xdz`. Esse arquivo disponibiliza ao usuário classes clássicas do xadrez: Rei, Torre, Bispo, Cavalo e Rainha.

Há um modo de visualização do tabuleiro, com uma lista das peças posicionadas. Também podem ser listadas as peças posicionadas sem mostrar o tabuleiro, ou mostrar as classes existentes.

Finalmente, há uma opção que verifica se o cenário no tabuleiro é de xeque-mate. O algoritmo leva em conta todos os movimentos possíveis de todas as peças para chegar à conclusão correta.
