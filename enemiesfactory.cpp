#include "enemiesfactory.h"

Enemy* EnemiesFactory::newWasp(QPoint point, int speed){
  return new Enemy(Enemy::Type::Wasp,point,speed);
}

Enemy* EnemiesFactory::newFly(QPoint point, int speed){
  return new Enemy(Enemy::Type::Fly,point,speed);
}

Enemy* EnemiesFactory::newLobster(QPoint point, int speed){
  return new Enemy(Enemy::Type::Lobster,point,speed);
}
