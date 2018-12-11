#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QWidget>
#include <QVector>
#include "gameobject.h"
#include "shot.h"
#include "moved.h"
#include "animated.h"

class Player : public GameObject, public Moved, public Animated
{
public:
  explicit Player();
  void move() final override;
  void setDirection(Moved::Path direction = Moved::Path::None);
  void fire();
  QVector<class Shot*> getShots();
  void makeFireGun(bool);
  bool isFireGun();
  void removeShot(int i);
  void read(const QJsonObject &json);
  void write(QJsonObject &json) const;
private:
  bool fireGun;
  QVector<class Shot*> shots;



};

#endif // PLAYER_H
