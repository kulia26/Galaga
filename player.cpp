#include "player.h"
#include "game.h"
#include "shot.h"
#include "moved.h"
#include "gameobject.h"
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>

Player::Player():GameObject (), Moved (), Animated (GameObject::Type::Player)
{
setPixmap(":/images/images/sprites.png");
pixmap = pixmap.copy(QRect(172,35,9,10));
rect  = QRect(268,700,48,48);
path = Moved::Path::None;
speed = 10;
fireGun = false;
}



void Player::move()
{
      if  (rect.x() > 4 && path == Path::Left){
         rect.moveLeft(rect.x()-speed);
      }
      if  (rect.x() < 548 && path == Path::Right){
         rect.moveLeft(rect.x()+speed);
      }
}
void Player::setDirection(Path _direction)
{
  path = _direction;
}

void Player::fire()
{
  if(shots.length() > 0){
      if (shots.last()->getRect().top() < 650){
          shots.push_back(new class Shot(QRect(rect.x()+21,rect.y(),6,12)));
      }
      for (int i = 1; i < shots.length(); i++){
          if (shots[i]->getRect().top() < 0){
              shots.remove(i);
          }
      }
    }
  else{
      shots.push_back(new class Shot(QRect(rect.x()+21,rect.y(),6,12)));
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
  return fireGun;
}

void Player::removeShot(int i)
{
  shots.remove(i);
}

void Player::read(const QJsonObject &json)
{
  std::cout <<"Player::read"<<std::endl;

  GameObject::read(json);
  Animated::read(json);
  Moved::read(json);
  pixmap = pixmap.copy(QRect(172,35,9,10));
}

void Player::write(QJsonObject &json) const
{
  GameObject::write(json);
  Animated::write(json);
  Moved::write(json);
}

