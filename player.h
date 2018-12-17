#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "gameobject.h"
#include "shot.h"

class Player : public GameObject
{
public:
  explicit Player();
  virtual ~Player() override;
  void move() final override;
  void fire() final override;
  void animate(Animation type) final override;
  void makeFramesFromPixmap() final override;
  void makeFireGun(bool);
  bool isFireGun();
  void removeShot(std::shared_ptr<Shot> shot);
  void setCurrentRoute(Route::Path route);
  void read(const QJsonObject &json) final override;
  void write(QJsonObject &json) const final override;
private:
  bool fireGun;
};

#endif // PLAYER_H
