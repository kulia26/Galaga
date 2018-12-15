#include "route.h"
#include "gameobject.h"
#include <cmath>
#include <QRect>
#include <iostream>

Route::Route()
{

}

Route::~Route()
{

}

Route::Route(class GameObject* object, Path path, QPoint end)
{
  this->parent = object;
  this->path =path;
  this->start = QPoint(parent->getRect().x(),parent->getRect().y());
  this->end = end;
  this->position = QPoint(parent->getRect().x(),parent->getRect().y());
  theEnd = false;
  q=M_PI/2;
}

Route::Route(class GameObject* object, Path path)
{
  this->parent = object;
  this->path =path;
  this->start = QPoint(object->getRect().x(),object->getRect().y());
  this->position.setX(object->getRect().x());
  this->position.setX(object->getRect().y());
  this->path =path;
  theEnd = false;
}


Route::Path Route::getRoutePath(){
  return path;
}

void Route::setStart(){
  start.setX(parent->getRect().x());
  start.setY(parent->getRect().y());
  position = start;
  theEnd = false;
}


QPoint Route::getNextPoint(double speed){
  if(QRect(end - QPoint(5,5),end+QPoint(5,5)).contains(position)){
      theEnd = true;
      return end;
    }
  if(path == Path::Left){
      dx = -speed;
      dy = 0;
    }
  if(path == Path::Right){
      dx = speed;
      dy = 0;
    }
  if(path == Path::None){
      dx = 0;
      dy = 0;
    }
  if(path== Path::Line){
    double length = sqrt((end.x() - start.x())*(end.x() - start.x())+(end.y() - start.y())*(end.y() - start.y()));
    if(length > 5){
        setStart();
      }
    dx = speed*(end.x() - start.x())/length;
    dy = speed*(end.y() - start.y())/length;
    }
  if(path== Path::Stay){
      if(parent->getRect().x() - start.x() > -6){
          dx =dx - 1;
        }else{
          dx = dx+1;
        }
    }
  if(path == Path::Sin){
      q = q + 0.4;
      double t = q;
      double length = sqrt((end.x() - start.x())*(end.x() - start.x())+(end.y() - start.y())*(end.y() - start.y()));
      if(length > 5){
          setStart();
        }
      dx = speed*(end.x() - start.x())/length+ 4*cos(t);
      dy = speed*(end.y() - start.y())/length + 4*sin(t)*sin(t);
    }
  if(path == Path::Lemniscate){
      q = q + 0.05;
      double t = q;
      dx =  speed/2*sqrt(2)*cos(t);
      dy =  speed*sqrt(2)*cos(t)*sin(t);
      if(q > M_PI/2 and  q < M_PI){
          dy = -dy;
        }
      if(q > M_PI and q < 3*M_PI/2){
          dy = -dy;
        }
      if(q > 3*M_PI/2 and q < 2*M_PI){
        }
      if(q > 2*M_PI){
          theEnd = true;
          return position;
        }
    }

  position = QPoint(position.x()+qRound(dx),position.y()+qRound(dy));
  return position;
}


bool Route::isEnded(){
  return theEnd;
}

void Route::read(const QJsonObject &json)
{
    std::cout <<"Route::read1"<<std::endl;
    path = Route::Path(json["path"].toInt());
    theEnd = json["theEnd"].toBool();

    QJsonObject startObject = json["start"].toObject();
    QJsonObject endObject = json["end"].toObject();
    QJsonObject positionObject = json["position"].toObject();

    start.setX(startObject.value("x").toInt());
    start.setY(startObject.value("y").toInt());
    end.setX(endObject.value("x").toInt());
    end.setY(endObject.value("y").toInt());
   // position.setX(positionObject.value("x").toInt());
   // position.setY(positionObject.value("y").toInt());
    std::cout <<"Route::read2"<<std::endl;
}

void Route::write(QJsonObject &json) const
{
    json["path"] = static_cast<int>(path);
    json["theEnd"] = false;

    QJsonObject startObject, endObject, positionObject;

    startObject.insert("x",start.x());
    startObject.insert("y",start.y());
    endObject.insert("x",end.x());
    endObject.insert("y",end.y());
   // positionObject.insert("x",position.x());
   // positionObject.insert("y",position.y());

    json["start"] = startObject;
    json["end"] = endObject;
    json["position"] = positionObject;
}
