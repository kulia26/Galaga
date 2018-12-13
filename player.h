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
  void move() final override;
  void fire();
  void animate(Animation type) final override;
  void makeFramesFromPixmap() final override;
  QVector<class Shot*> getShots();
  void makeFireGun(bool);
  bool isFireGun();
  void removeShot(int i);
  void setCurrentRoute(Route::Path route);
  void read(const QJsonObject &json) final override;
  void write(QJsonObject &json) const final override;
private:
  bool fireGun;
  QVector<class Shot*> shots;
};

#endif // PLAYER_H
