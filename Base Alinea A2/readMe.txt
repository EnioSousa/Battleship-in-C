How to compile and run:
$make clean
$make

Funções que te vai dar geito. Não aconselho a usares outras funções a menos que saibas realmente o que elas estão a fazer


Map *newMap(int size); ---> Cria um novo mapa com tamanho size. 

Ship *search(Map *map, Point *p); ---> Procura o ponto p no mapa e RETORNA o apontador para o ship ou null caso não exista

void insertManual(Map *map); ---> Insere os barcos manualmente

void insertRandom(Map *map); ---> Insere os barcos random. Não te esqueças de iniciar a seed

void insertShip(Map *map, Ship *ship, Point *p, char dir); ---> insere um navio, na possição p e coloca o navio em direção a dir

void insertPoint(Map *map, Point *p, Ship *ship ); ---> insere um ponto no mapa

void printAll(Map *m) --> void printMapShip(Map *m); + void printMapHistory(Map *m);

void printMapShip(Map *m); ---> faz print das possições dos navios do jogador com mapa m

void printMapHistory(Map *m); ---> faz print da historia de ataques do jogador com mapa m

Ship* initiateShip(int size); ---> inicia o ship, com as formas que definimos e atribui automaticamente o numero de navios

void printAllShip(Ship *); --> faz print das formas de cada navio
