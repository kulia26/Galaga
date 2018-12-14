#include "enemy.h"
#include "gameobject.h"

#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
#include <QJsonObject>
#include <QJsonArray>

Enemy::Enemy(Enemy::Type type, QPoint start,double speed):GameObject()
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
}
Enemy::Enemy():GameObject()
{
  gameObjectType = GameObject::Type::Enemy;
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
  if(currentRoute->getRoutePath()==Route::Path::Stay){
      animate(Animation::Stay);
    }
  if(currentRoute->isEnded()){
      int i = routes.indexOf(currentRoute);
      if((i+1)!=routes.length()){
          currentRoute = routes[i+1];
        }
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
  framesCount++;
  if(framesCount > 1000){
      framesCount = 0;
  }
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
            Route* route = new Route();
            route->read(routeObject);
            routes.push_back(route);
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
