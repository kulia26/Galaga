#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "gameobject.h"
#include "animated.h"

#include <QVector>

class Explosion : public GameObject, protected Animated
{
public:
  enum class Type{EnemyDie, PlayerDie};
  explicit Explosion(QPoint point, Type type);
  Type getType();
  void animate(Animation type) final override;
  void makeFramesFromPixmap() override;
  void draw(std::shared_ptr<QPainter> painter) override;
  void move() override;
  void reuse(QPoint point);
private:
  Type expType;
};

#endif // EXPLOSION_H
