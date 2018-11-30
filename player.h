#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include "gameobject.h"
#include "shot.h"

class Player : public GameObject
{
public:
  explicit Player();
  QPixmap getPixmap();
  void move(Direction direction) override;
  void fire();
  QVector<Shot*> getShots();
private:
  QVector<Shot*> shots;


};

#endif // PLAYER_H
