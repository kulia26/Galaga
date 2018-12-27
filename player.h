#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "gameobject.h"
#include "shot.h"
#include "animated.h"
#include "shooter.h"
#include "physicalobject.h"
#include "routed.h"

class Player : public PhysicalObject, public Shooter
{
public:
  explicit Player();
  virtual ~Player() override;
  void move() final override;
  void fire() final override;
  void makeFireGun(bool);
  bool isFireGun();
  void setCurrentRoute(Route::Path route);
  void read(const QJsonObject &json) final override;
  void write(QJsonObject &json) const final override;
private:
  bool fireGun;
};

#endif // PLAYER_H
