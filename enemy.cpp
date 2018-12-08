#include "enemy.h"
#include "animated.h"
#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
Enemy::Enemy(Enemy::Type type):GameObject(),Animated()
{
  if(type == Type::Lobster){
      pixmap = QPixmap(":/images/images/LobsterSprites.png");
  }
  if(type == Type::Fly){
      pixmap = QPixmap(":/images/images/FlySprites.png");
  }
  if(type == Type::Wasp){
      pixmap = QPixmap(":/images/images/WaspSprites.png");
  }

  direction = Direction::none;
  speed = 1;
  makeFramesFromPixmap(&pixmap, GameObject::Type::Enemy);
  rect  = QRect(QRandomGenerator::global()->bounded(20,500),QRandomGenerator::global()->bounded(20,500),frame->width()*3,frame->height()*3);
}

void Enemy::move()
{
  animate(8, Animated::Type::Stay, GameObject::Type::Enemy);
}
