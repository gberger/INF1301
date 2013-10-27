Cheque-Mate
-----------

**SE é a vez de J, e o rei J está em ataque, e não há nenhum movimento de J possível que deixe o rei fora de ataque, ENTÃO J está em cheque-mate**


Algoritmo
---------

1º Checar se o rei está em ataque.
Dada a casa do rei, checa se alguma peça inimiga pode mover-se para essa casa.

2º Checar se há movimentos que deixem o rei fora de ataque.

Simular cada movimento que o jogador em cheque possa fazer. Isso inclui movimentos do rei e quaisquer movimentos de outras peças. 

Para cada movimento, checar se o rei continua em ataque. 

3º Se houver algum movimento que deixe o rei fora de ataque, não está em cheque-mate. Do contrário, está.


Estruturas
----------

    struct tipo_de_peca {
      int id;
      int flag_movimento_horizontal;
      int limite_movimento_horizontal;
      int flag_movimento_vertical;
      int limite_movimento_vertical;
      int flag_movimento_diagonal;
      int limite_movimento_diagonal;
      int flag_movimento_cavalo;
      int limite_movimento_cavalo[2];
    }
    
    struct peca {
      struct tipo_de_peca *tipo;
      POSICAO posicao;
      JOGADOR jogador;
    }
    
    enum Posicao {
      A1;
      A2;
      ...
      H7;
      H8; 
    }
    
    enum JOGADOR {
      BRANCO;
      PRETO;
    }
    

Funções
-------

* checar se uma peça pode mover-se para uma casa


Menu
----

    01. Novo
    02. Abrir
    03. Salvar
    
    11. Configurar tamanho do tabuleiro
    12. Configurar vez de jogador 
    
    21. Listar tipos de peça
    22. Criar tipo de peça
    23. Alterar tipo de peça
    24. Excluir tipo de peça
    
    31. Listar peças
    32. Criar peça
    33. Alterar peça
    34. Excluir peça
    
    99. Sair
