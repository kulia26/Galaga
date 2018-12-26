#include "player.h"
#include "route.h"
#include "game.h"
#include "shot.h"
#include "gameobject.h"
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>

Player::Player()
{
gameObjectType = GameObject::Type::Player;
setPixmap(":/images/images/sprites.png");
pixmap = pixmap.copy(QRect(172,35,9,10));
rect  = QRect(268,700,48,48);
addRoute(Route::Path::None);
addRoute(Route::Path::Left);
addRoute(Route::Path::Right);
setCurrentRoute(Route::Path::None);
speed = 10;
fireGun = false;
}


Player::~Player()
{
std::cout<<"destroy player"<< std::endl;
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
{ if(currentRoute->getRoutePath() == Route::Path::Left && rect.x() > 10){
      rect.moveTo(currentRoute->getNextPoint(speed));
    }
  if(currentRoute->getRoutePath() == Route::Path::Right && rect.x() < 590 - rect.width()){
        rect.moveTo(currentRoute->getNextPoint(speed));
      }

}

void Player::fire()
{
  std::shared_ptr<Shot> newShot(new class Shot(QRect(rect.x()+21,rect.y(),6,12), Route::Path::Top));
  this->addShot(newShot);
}

void Player::makeFireGun(bool firegun)
{
  fireGun = firegun;
}

bool Player::isFireGun()
{
  return fireGun;
}

void Player::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(rect,this->pixmap);
}

void Player::read(const QJsonObject &json)
{
  GameObject::read(json);

}

void Player::write(QJsonObject &json) const
{
  GameObject::write(json);
}

