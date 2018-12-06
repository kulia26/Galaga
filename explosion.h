#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include "animated.h"
#include <QVector>

class Explosion : public GameObject, public Animated
{
public:
  explicit Explosion(QPoint point);
  void move();
};

#endif // EXPLOSION_H
