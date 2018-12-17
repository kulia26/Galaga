#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"

#include <QVector>

class Explosion : public GameObject
{
public:
  explicit Explosion(QPoint point);
  virtual ~Explosion();
  void animate(Animation type) final override;
  void makeFramesFromPixmap() final override;
  void draw(std::shared_ptr<QPainter> painter) final override;
};

#endif // EXPLOSION_H
