#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game& game = Game::getInstance();
  //w.loadGame();
  game.newGame();
  game.show();
  //w.saveGame();
 // w.show();

  return a.exec();
}
