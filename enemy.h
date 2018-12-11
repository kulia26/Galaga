#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "shot.h"
#include "animated.h"
#include "moved.h"
#include <QVector>
#include <QPoint>

class Enemy : public GameObject, public Animated, public Moved
{
public:
  enum Type { Lobster, Fly, Wasp };
  explicit Enemy(Enemy::Type type, QPoint _start, QPoint _end,int _speed);
  explicit Enemy();
  void move() override;
  void fire();
  //QVector<Shot*> getShots();

  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
private:
  Type type;
  //QVector<Shot*> shots;
  QVector<Moved*> tracks;
  Moved* currentMoved;
};

#endif // ENEMY_H
