#ifndef SHOOTER_H
#define SHOOTER_H

#include <QVector>
#include "shot.h"
class Shooter
{
public:
  Shooter();
  virtual ~Shooter();
  virtual void fire();

  void removeShot(std::shared_ptr<Shot> shot);
  void addShot(std::shared_ptr<Shot> shot);
  QVector<std::shared_ptr<Shot>> getShots();
private:
  QVector<std::shared_ptr<Shot>> shots;
};

#endif // SHOOTER_H
