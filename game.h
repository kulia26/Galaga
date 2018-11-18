#ifndef GAME_H
#define GAME_H

#include <QWidget>

namespace Ui {
  class Game;
}

class Game : public QWidget
{
  Q_OBJECT

public:
  explicit Game(QWidget *parent = nullptr);
  ~Game();

private:
  Ui::Game *ui;
};

#endif // GAME_H
