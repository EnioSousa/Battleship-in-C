#include "insert.c"

int main()
{
  Quad *root = initiateTree();
  Ship *ship = initiateShip();

  insertManual(root, ship);
  printMap(root);

}
