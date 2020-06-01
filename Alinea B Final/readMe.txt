How to compile:
$make clean
$make

How to run:
./main

O programa é baseado no jogo da batalha naval jogado por duas pessoas.
Os jogadores terão de definir o tamanho do mapa que será usado no jogo, o que corresponde a uma matriz quadrada (maior do que 19 e menor do que 41).
Cada jogador terá de fornecer o seu nickname e escolher o modo de inserir as suas peças referentes aos barcos. Existe dois modos:manual e random. O modo random automaticamente distribui os barcos no mapa. No modo manual, o jogador precisa de inserir manualmente cada barco no mapa. Existe 5 tipos de barcos: Carrier,Battleship,Cruiser,Submarine e o Destroyer.
No modo manual é pedido a identificação do barco (cada tipo de barco tem uma id que vai de 0 até 4),a coordenada x que corresponde à linha, e a coordenada y que corresponde à coluna. As coordenadas x e y vão de 1 até ao máximo definido pelos jogadores(Não esquecer que é uma matriz quadrada).Pede também a direcção do barco que corresponde a norte,sul,leste e oeste.
Selecionando um dos modos anteriores o jogo inicia. Cada jogador terá duas matrizes, uma referente à distribuição dos barcos e a outra  ao histórico dos seus disparos ao longo do jogo.
O jogador precisa de inserir as coordenadas(x e y) do seu tiro. Caso o seu disparo  atinge um barco poderá disparar novamente. Caso contrário passa a vez para outro jogador.As matrizes serão a actualizadas em cada disparo.
O primeiro que eliminar todos os barcos vence o jogo.
No fim do jogo poderá reiniciar uma nova partida.
