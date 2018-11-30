#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QVector>
#include "skystar.h"
#include "player.h"

namespace Ui {
  class Game;
}

class Game : public QWidget
{
  Q_OBJECT
private:
  Player* player;
  Ui::Game *ui;
public:
  explicit Game(QWidget *parent = nullptr);
  void paintEvent(QPaintEvent *event);
  void keyPressEvent(QKeyEvent *event);
  void keyReleaseEvent(QKeyEvent *event);
  QVector<SkyStar*> sky;
  ~Game();

};

#endif // GAME_H
