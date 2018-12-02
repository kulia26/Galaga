#include "enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(Enemy::Type _type):GameObject()
{
  rect  = QRect(0,0,36,36);
  type = _type;
  if(type == Type::Lobster){
      pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(156,83,10,10));
       rect.moveLeft(rect.x()+36);
  }
  if(type == Type::Fly){
      pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(156,99,10,10));
  }
  if(type == Type::Wasp){
      pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(156,115,10,10));
      rect.moveLeft(rect.x()+72);
  }

  direction = Direction::none;
  speed = 1;
}

void Enemy::move()
{
  rect.moveTop(rect.x()+speed);
  rect.moveLeft(rect.y()+speed);
}
