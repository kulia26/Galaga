#include "player.h"
#include "game.h"
#include "shot.h"
#include <iostream>

Player::Player()
{
rect  = QRect(268,700,48,48);
pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(172,35,9,10));
direction = Direction::none;
speed = 10;
fireGun = false;
}

void Player::move()
{
      if  (rect.x() > 4 && direction == GameObject::Direction::left){
         rect.moveLeft(rect.x()-speed);
      }
      if  (rect.x() < 548 && direction == GameObject::Direction::right){
         rect.moveLeft(rect.x()+speed);
      }
}
void Player::setDirection(GameObject::Direction _direction)
{
  direction = _direction;
}

void Player::fire()
{
  if(shots.length() > 0){
      if (shots.last()->getRect().top() < 650){
          shots.push_back(new Shot(QRect(rect.x()+21,rect.y(),6,12)));
      }
      for (int i = 1; i < shots.length(); i++){
          if (shots[i]->getRect().top() < 0){
              shots.remove(i);
          }
      }
    }
  else{
      shots.push_back(new Shot(QRect(rect.x()+21,rect.y(),6,12)));
    }
}

QVector<Shot*> Player::getShots()
{
  return shots;
}
void Player::makeFireGun(bool firegun)
{
  fireGun = firegun;
}

bool Player::isFireGun()
{
  return fireGun ? true : false;
}

void Player::removeShot(int i)
{
  shots.remove(i);
}

