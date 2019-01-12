#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include "animated.h"

#include <QVector>

class Explosion : public GameObject, protected Animated
{
public:
  explicit Explosion(QPoint point);
  void animate(Animation type) final override;
  void makeFramesFromPixmap() override;
  void draw(std::shared_ptr<QPainter> painter) override;
  void move() override;
  void reuse(QPoint point);
};

#endif // EXPLOSION_H
