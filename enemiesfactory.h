#ifndef ENEMIESFACTORY_H
#define ENEMIESFACTORY_H
#include"enemy.h"

class EnemiesFactory
{
public:
  EnemiesFactory() = delete;
  static Enemy* newWasp(QPoint point, int speed);
  static Enemy* newFly(QPoint point, int speed);
  static Enemy* newLobster(QPoint point, int speed);
};

#endif // ENEMIESFACTORY_H
