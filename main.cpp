#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  Game& game = Game::getInstance();

  game.execute();
  game.show();

  return a.exec();
}
