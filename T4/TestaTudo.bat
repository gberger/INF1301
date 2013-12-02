rem testa todos os scripts

cls

if exist estatisticas.estat  del estatisticas.estat

TRAB4-1      /sTesteGrafoInstrum.script             /lTesteGrafoInstrum              /aestatisticas

TRAB4-1      /sTesteGrafoInstrumDeturp.script       /lTesteGrafoInstrumDeturp        /aestatisticas

TRAB4-2      /sTesteGrafo.script                    /lTesteGrafo                     /aestatisticas

type acumulador.count


pause