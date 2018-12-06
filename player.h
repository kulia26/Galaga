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
  void move() override;
  void setDirection(GameObject::Direction direction = Direction::none);
  void fire();
  QVector<Shot*> getShots();
  void makeFireGun(bool);
  bool isFireGun();
  void removeShot(int i);
private:
  Direction direction;
  bool fireGun;
  QVector<Shot*> shots;



};

#endif // PLAYER_H
