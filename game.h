#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include "skystar.h"

namespace Ui {
  class Game;
}

class Game : public QWidget
{
  Q_OBJECT

public:
  explicit Game(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  QVector<SkyStar*> sky;
  ~Game();

private:
  Ui::Game *ui;
};

#endif // GAME_H
