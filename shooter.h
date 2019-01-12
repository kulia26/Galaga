#ifndef SHOOTER_H
#define SHOOTER_H

#include <QVector>
#include "shot.h"
class Shooter
{
public:
  Shooter() = default;
  virtual ~Shooter() = default;
  virtual void fire() = 0;

  void removeShot(std::shared_ptr<Shot> shot);
  void addShot(std::shared_ptr<Shot> shot);
  QVector<std::shared_ptr<Shot>> getShots();
  std::shared_ptr<Shot> last;
};

#endif // SHOOTER_H
