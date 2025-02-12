﻿#include "enemy.h"
#include "gameobject.h"
#include "shotpool.h"

#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonArray>
#include <memory>

Enemy::Enemy(Enemy::Type type, QPoint start,double speed)
{
  gameObjectType = GameObject::Type::Enemy;
  this->speed = speed;
  this->type = type;
  if(type == Type::Lobster){
      setPixmap(":/images/images/LobsterSprites.png");
  }
  if(type == Type::Fly){
      setPixmap(":/images/images/FlySprites.png");
  }
  if(type == Type::Wasp){
      setPixmap(":/images/images/WaspSprites.png");
  }
  makeFramesFromPixmap();
  rect  = QRect(start.x(),start.y(),frame->width()*3,frame->height()*3);
  canAttack = false;
  lives = 1;

}

Enemy::~Enemy()
{

}

void Enemy::makeFramesFromPixmap(){
  frames.clear();
  for(int i=0; i<9;i++){
      frames.push_back(new QPixmap(pixmap.copy(16*i,0,16,10)));
    }
  if(frames.isEmpty()){
      frame = &pixmap;
    }else{
      frame = frames.first();
    }
}

void Enemy::move()
{
  rect.moveTo(currentRoute->getNextPoint(speed));
  if(currentRoute->getRoutePath() == Route::Path::Line){
      animate(Animation::MoveDownRight);
    }
  if(currentRoute->getRoutePath() == Route::Path::Lemniscate){
      animate(Animation::Rotate);
    }
  if(currentRoute->getRoutePath()==Route::Path::Stay){
      animate(Animation::Stay);
      if(currentRoute != routes.last()){
         currentRoute->setTheEnd(true);
        }
    }
  if(currentRoute->isEnded()){
      int i = routes.indexOf(currentRoute);
      if((i+1)!=routes.length()){
          currentRoute = routes[i+1];
          currentRoute->setStart();
        }
      if(currentRoute == routes.last()){
          //canAttack = true;
        }
    }
  this->fire();
}

void Enemy::fire()
{
  if(framesCount%QRandomGenerator::global()->bounded(60,120) == 0 && currentRoute->getRoutePath() == Route::Path::Stay){
          this->addShot(ShotPool::getInstance().createNew(this->getPoint()+QPoint(10,10),GameObject::Type::EnemyShot));
    }
}

void Enemy::attack(std::shared_ptr<GameObject> player){
  if(canAttack){
      std::cout << "attack" << std::endl;
      addRoute(Route::Path::Sin, player->getPoint());
      addRoute(Route::Path::Sin, this->getPoint());
      addRoute(Route::Path::Stay);
      canAttack = false;
    }
}

void Enemy::animate(Animation type){
  if(framesCount % 8 == 0 && type == Animation::Stay){
        if(frames.indexOf(frame)==7){
          frame = frames[6];
        }
        else{
         frame = frames[7];
        }
  }
  if(framesCount % 4 == 0 && type == Animation::MoveDownRight){
        if(frames.indexOf(frame)==5){
          frame = frames[4];
        }
        else{
         frame = frames[5];
        }
  }
  if(framesCount % 4 == 0 && type == Animation::Rotate){
        if(frames.indexOf(frame)==4){
          frame = frames[3];
        }
        else{
         frame = frames[4];
        }
  }
  if(framesCount % 4 == 0 && type == Animation::Attack){
        if(frames.indexOf(frame)==1){
          frame = frames[2];
        }
        else{
         frame = frames[1];
        }
  }
  framesCount++;
  if(framesCount > 10000){
      framesCount = 0;
  }
}

void Enemy::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(rect,*frame);
}

void Enemy::read(const QJsonObject &json)
{
    GameObject::read(json);

    type = Enemy::Type(json["type"].toInt());
    routes.clear();
        QJsonArray routesArray = json["routes"].toArray();
        for (int routeIndex = 0; routeIndex < routesArray.size(); routeIndex++) {

            QJsonObject routeObject = routesArray[routeIndex].toObject();
            std::cout << routeIndex<<std::endl;
            //auto route = new Route();
            //route->read(routeObject);
            //routes.push_back(route);
        }
    std::cout<<routes.length()<<std::endl;
    currentRoute  = routes.first();
}

void Enemy::write(QJsonObject &json) const
{
  GameObject::write(json);

  json["type"] = static_cast<int>(type);
  QJsonArray routesArray;
     foreach (const Route* route, routes) {
         QJsonObject routeObject;
         route->write(routeObject);
         routesArray.append(routeObject);
     }
  json["routes"] = routesArray;
}
