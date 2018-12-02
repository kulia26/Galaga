#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "shot.h"
#include <QVector>

class Enemy : public GameObject
{
public:
  enum Type { Lobster, Fly, Wasp };
  explicit Enemy(Type _type);
  void move() override;
  void setDirection(GameObject::Direction direction = Direction::none);
  void fire();
  QVector<Shot*> getShots();
private:
  Type type;
  Direction direction;
  QVector<Shot*> shots;
};

#endif // ENEMY_H
