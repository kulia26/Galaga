#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

#include <QVector>

class Explosion : public GameObject
{
public:
  explicit Explosion(QPoint point);
  void animate(Animation type) final override;
  void makeFramesFromPixmap() final override;
};

#endif // EXPLOSION_H
