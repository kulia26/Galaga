#include "player.h"
#include "route.h"
#include "game.h"
#include "shot.h"
#include "gameobject.h"
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>

Player::Player():GameObject ()
{
gameObjectType = GameObject::Type::Player;
setPixmap(":/images/images/sprites.png");
pixmap = pixmap.copy(QRect(172,35,9,10));
rect  = QRect(268,700,48,48);
routes.push_back(new Route(this, Route::Path::None));
routes.push_back(new Route(this, Route::Path::Left));
routes.push_back(new Route(this, Route::Path::Right));
setCurrentRoute(Route::Path::None);
speed = 10;
fireGun = false;
makeFramesFromPixmap();
}

void Player::setCurrentRoute(Route::Path route){
  if(route == Route::Path::None){
      currentRoute = routes[0];
      currentRoute->setStart();
    }
  if(route == Route::Path::Left){
      currentRoute = routes[1];
      currentRoute->setStart();
    }
  if(route == Route::Path::Right){
      currentRoute = routes[2];
      currentRoute->setStart();
    }
}

void Player::move()
{
  rect.moveTo(currentRoute->getNextPoint(speed));
}

void Player::makeFramesFromPixmap(){
  frame = &pixmap;
}


void Player::fire()
{
  if(shots.length() > 0){
      if (shots.last()->getRect().top() < 650){
          shots.push_back(new class Shot(QRect(rect.x()+21,rect.y()-10,6,12)));
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

void Player::animate(Animation type){
  framesCount++;
  if(framesCount > 1000){
      framesCount = 0;
  }
}

void Player::read(const QJsonObject &json)
{
  GameObject::read(json);

  //pixmap = pixmap.copy(QRect(172,35,9,10));
}

void Player::write(QJsonObject &json) const
{
  GameObject::write(json);
}

