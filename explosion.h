#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include "animated.h"

#include <QVector>

class Explosion : public GameObject, public Animated
{
public:
  explicit Explosion(QPoint point);
  void animate(Animation type) final override;
  void makeFramesFromPixmap() override;
  void draw(std::shared_ptr<QPainter> painter) override;
};

#endif // EXPLOSION_H
