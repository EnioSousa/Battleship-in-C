How to compile and run:
$make clean
$make

Funções que te vai dar geito. Não aconselho a usares outras funções a menos que saibas realmente o que elas estão a fazer


Map *newMap(int size); ---> Cria um novo mapa com tamanho size. 

void deletePoint(Map *, Point *p); --> remove o ponto p do mapa. Caso não exista não faz nada

int *search(Map *, Point *p); ---> Procura o ponto p no mapa e RETORNA 1 caso exista, 0 caso contrario

void insertManual(Map *, Ship *); ---> Insere os barcos manualmente

void insertRandom(Map *, Ship*); ---> Insere os barcos random. Não te esqueças de iniciar a seed

void insertShip(Map *, Ship *, Point *, char ); ---> insere um navio, numa possição

void insertPoint(Map *, Point *, int ); ---> insere um ponto no mapa

void printMap(Map *m); ---> faz print do mapa

Ship* initiateShip(); ---> inicia o ship, com as formas que definimos
