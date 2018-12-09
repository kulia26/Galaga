#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "shot.h"
#include "animated.h"
#include "track.h"
#include <QVector>
#include <QPoint>

class Enemy : public GameObject, public Animated
{
public:
  enum Type { Lobster, Fly, Wasp };
  explicit Enemy(Type type, QPoint _start, QPoint _end,int speed);
  void move() override;
  void setDirection(GameObject::Direction direction = Direction::none);
  void fire();
  QVector<Shot*> getShots();
private:
  Type type;
  Direction direction;
  QVector<Shot*> shots;
  QVector<Track*> tracks;
  Track* currentTrack;
};

#endif // ENEMY_H
