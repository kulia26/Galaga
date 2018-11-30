#include "player.h"
#include "game.h"
#include "shot.h"

Player::Player()
{
rect  = QRect(268,700,48,48);
pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(172,35,9,10));
}

QPixmap Player::getPixmap()
{
return pixmap;
}


void Player::move(GameObject::Direction direction)
{
  if  (rect.x() > 4 && direction == GameObject::Direction::left){
     rect.moveLeft(rect.x()-4);
  }
  if  (rect.x() < 548 && direction == GameObject::Direction::right){
     rect.moveLeft(rect.x()+4);
  }
}

void Player::fire()
{
  shots.push_back(new Shot(QRect(rect.x()+21,rect.y(),6,12)));
}

QVector<Shot*> Player::getShots()
{
  return shots;
}



