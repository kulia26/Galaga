#ifndef ENEMY_H
#define ENEMY_H

#include "gameobject.h"
#include "shot.h"
#include "route.h"
#include <QVector>
#include <QPoint>

class Enemy : public GameObject
{
public:
  enum class Type { Lobster, Fly, Wasp };
  explicit Enemy(Enemy::Type type, QPoint start,double speed);
  explicit Enemy();
  void move() final override;
  void animate(Animation type) final override;
  void makeFramesFromPixmap() final override;
  void fire();
  QPoint* getPosition();

  void read(const QJsonObject &json) final override;
  void write(QJsonObject &json) const final override;
private:
  Type type;
};

#endif // ENEMY_H
