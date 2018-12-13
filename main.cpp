#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game w; 
  //w.loadGame();
  w.newGame();
  w.show();
  w.saveGame();
 // w.show();

  return a.exec();
}
