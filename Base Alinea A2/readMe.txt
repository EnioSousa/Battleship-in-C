How to compile and run:
$make clean
$make

Modulo Ship:

Ship *initiateShip(int size); ---> Cria um array dinamicamente de tipo Ship e retorna o apontador da primeira posição. Cada posição representa um navio diferente. Por exemplo, a posição 0 (ship[0]) representa um carrier que de tamanho 5 e uma forma (T). Para além de inicializar as variáveis, esta função chama defineForm/1 que define a forma de cada barco.

void defineForm(Ship *arrShip); --> Função define o vetor de deslocação de cada barco, para todas as posições do array arrShip. Neste trabalho decidimos guardar um vetor de deslocação para cada ponto do barco para simplificar e generalizar as colocações dos barcos segundo direções diferentes i.e east(0º), north(90º), west(180º), south(240º). Se quisermos mudar a forma de um barco, basta modicar o vetor de deslocação e irá se propagar pelo resto dos módulos.

void freeShip(Ship *ship) --> Liberta a memória alocada dinamicamente na função initiateShip/1.

int someShipLeft(Ship *arrShip); --> Função retorna 1 caso falte por algum navio, caso contrario 0. Chama shipAvaliable/1 para todas as posições do arrShip.

int shipAvaliable(Ship *ship); --> Retorna 1 caso a posição de memória ship tenha algum navio a colocar, 0 caso contrario.

int nextShip(Ship *arrShip); ---> Retorna o índex da posição de memória de arrShip que ainda tenha algum navio para colocar.

int someActiveShip(Ship *arrShip); ---> Retorna 1 caso ainda haja algum navio ativo (não afundado), caso contrario 0.

void printAllShip(Ship *arrShip); ---> Para todas as posições do arrShip chama printShip/1.

void printShip(Ship *ship); ---> Chama printShipInfo/1 e printShipForm/1.

void printShipInfo(Ship *ship); --> Imprime informação contida na posição de memória, como n.º de barcos ativos, tamanho, etc.

void printShipForm(Ship *ship); --> Imprime a forma do barco.

printAllShipInfo(Ship *arrShip); --> Chama a função printShipInfo para todas as posições de memória de arrShip.

Modulo Map:

Map *newMap(int size); ---> Cria uma estrutura Map e retorna o seu apontador. Esta estrutura contem um apontador para um array bidimensional de tipo Cell e
um apontador para o array de tipo Ship. Para iniciar as variáveis board e ship, são chamadas as funções newBiCell/1 e initiateShip/1 respetivamente. nPoint é inicializada a 0 e mapSize é igualada ao argumento passado a função, size.

Cell *newCell(int size); ---> Cria uma array dinamicamente de tipo Cell e para cada posição, inicializa as variáveis bit e shot com valor '0'.

Cell **newBiCell(int size); --> Cria um array dinamicamente de pointers de tipo Cell*. Para cada posição do array a função newCell/1 é chamada.

int lost(Map *map); --> Retorna 1 caso não existam barcos ativos, caso contrario 0. Esta função vai a todas as posições do array de map->ship e para cada, ou seja, para cada tipo de navio, vê se existe algum ativo no mapa.

void freeMap(Map *map); --> Esta função liberta o espaço.

Modulo Search:

Ship *search(Map *map, Point *p); --> Retorna o apontador contido em board[p.y][p.x], se não existir retorna NULL.

int inBound(Map *map, Point *p); --> Retorna 1 caso o point p esta dentro dos limites do mapa, caso contrario 0.

Modulo Insert:

void movePointLeft(Map *map, Point *p) --> Função move o ponto p no sentido east (direita) e caso saia dos limites do mapa, p é reposicionado na posição "abaixo" e a "esquerda".

void modePointIndDir(Point *old, Point *vector, Point *new, char dir); --> Nesta função iremos calcular o ponto new. O ponto new é igual o ponto old segundo uma direção, dir, e vetor, vector.

void randomDir(char *dir); --> Gera uma direção aleatória que pode tomar valores 'e'(0º), 'w'(180º), 'n'(90º) e 's'(240º).

void rotateDir(char *dir); --> Roda a direção, dir, no sentido contrário dos ponteiros do relógio.


void randomPoint(Map *map, Point *p); --> Gera um ponto aleatório dentro dos limites do mapa.

int placeIsPossible(Map *map, Ship *ship, Point *p, char dir); --> Retorna 1 caso o ponto esteja dentro dos limites e a configuração seja possível. Chama inBound/2 e confAvaliable/4.

int confAvaliable(Map *m, Ship *ship, Point *ref, char dir); --> Retorna 1 caso seja possível colocar o navio, ship, na posição p e direção dir, caso contrario 0. Basicamente o que esta função faz é ver se todas as posições do barco estão disponíveis no mapa e vé se existe algum barco imediatamente a volta.

int voidAroundPoint(Map *map, Point *p); --> Retorna 1 caso as posições a volta do ponto p estejam vazias. Quando digo a volta refiro-me a east, nort, west and south.

void insertShip(Map *map, Ship *ship, Point *ref, char dir); --> Coloca um navio na posição de referência ref. Basicamente iremos usar o vetor de deslocação definido em Ship para determinar todos os pontos que o navio ocupa e para cada ponto chamamos insertPoint/3. Para determinar sucessivamente os pontos a colocar iremos chamar movePointDir/4. Atenção esta função não verifica se podemos colocar o navio, esse trabalho tem que ser feito antes.

void insertPoint(Map *map, Point *p, Ship *ship); --> Esta função coloca o navio na posição p, alterando o board[p.y][p.x].bit para '1', adicionando o pointer ship e incrementando o número de pontos. Atenção esta função não verifica se é possível colocar o navio, esse trabalho deve ser feito anteriormente.

int shot(Map *map1, Map *map2, Point *p); --> Esta função faz com que o map1 faça um "tiro" em map2 no ponto p. Ela chama sunk/2 para ver se o tiro afundou algum barco.

int sunk(Map *map, Point *p); --> Função recursiva um pouco difícil de explicar, portanto, deixo para o professor perguntar-me quando fizermos a apresentação, mas basicamente ela ve se o navio que esta no ponto p afundou, chamando testCondition/2 para ver se nas possições north, east, west e south tem algum ponto do navio atingido. Retorna 1 caso tenha afundado, 0 caso contrario.

int testCondition(Map *map, Point *p); --> Esta função ve se nas posições a volta se tem algum ponto não atingido, caso tenho voltamos a chamar outra vez a função, mas agora com p igual ao ponto atingido e fazemos o mesmo raciocínio, ate se determinar se todos os pontos foram atingidos ou não.

void insertRandom(Map *m); --> Função coloca todos os navios de forma aleatória. Para casa navio à colocar iremos gerar uma direção aleatória usando randomDir/1 de seguida chamar a função findSomePlace/2 e fazer insertShip/4, com o ponto encontrado na função anterior.

void findSomePlace(Map *m, Ship *ship, Point *p, char *dir); --> Iremos gerar um ponto aleatório e ver se para alguma direção é possível colocar o barco, se sim, perfeito paramos, caso contrario iremos mover o ponto para a direita e vemos e voltar a testar. Fazemos isto ate se encontrar uma direção e um ponto. Esta função chama findSomeDir/4 para gerar as diferentes direção e testar se é possível a colocação.

int findSomeDir(Map *m, Ship *ship, Point *p, char *dir); --> dado um ponto iremos se rodar a direção e ver se é possível colocar o barco em alguma direção. Retornamos 1 caso seja possível 0 caso contrario. Iremos chamar rotateDir/1 para rodar a direção e placeIsPossible/4 para testar se é possível colocar o barco.
