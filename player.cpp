#include "player.h"
#include "route.h"
#include "game.h"
#include "shot.h"
#include "gameobject.h"
#include <iostream>
#include <QJsonArray>
#include <QJsonObject>
#include "shotpool.h"

Player::Player()
{
gameObjectType = GameObject::Type::Player;
setPixmap(":/images/images/PlayerSprite.png");
rect  = QRect(268,700,48,48);
addRoute(Route::Path::None);
addRoute(Route::Path::Left);
addRoute(Route::Path::Right);
setCurrentRoute(Route::Path::None);
speed = 10;
lives = 1;
fireGun = false;
}


Player::~Player()
{
std::cout<<"destroy player"<< std::endl;
}

int Player::getLives(){
  return lives;
}

QPixmap Player::getPixmap(){
  return pixmap;
}

void Player::setCurrentRoute(Route::Path route){
  if(route == Route::Path::None){
      currentRoute = routes[0];
    }
  if(route == Route::Path::Left){
      currentRoute = routes[1];
    }
  if(route == Route::Path::Right){
      currentRoute = routes[2];
    }
}

void Player::move()
{
  if(currentRoute->getRoutePath() == Route::Path::Left && rect.x() > 10){
      rect.moveTo(currentRoute->getNextPoint(speed));
    }
  if(currentRoute->getRoutePath() == Route::Path::Right && rect.x() < 590 - rect.width()){
        rect.moveTo(currentRoute->getNextPoint(speed));
      }
  if(this->isFireGun()){
      this->fire();
  }
}

void Player::fire()
{
  this->addShot(ShotPool::getInstance().createNew(this->getPoint()+QPoint(24,24),GameObject::Type::PlayerShot));
}

void Player::makeFireGun(bool firegun)
{
  fireGun = firegun;
}

bool Player::isFireGun()
{
  return fireGun;
}

void Player::read(const QJsonObject &json)
{
  GameObject::read(json);

}

void Player::write(QJsonObject &json) const
{
  GameObject::write(json);
}

