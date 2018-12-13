#include "route.h"
#include <cmath>
#include <QRect>
#include <iostream>

Route::Route()
{

}

Route::~Route()
{

}

Route::Route(Path path, QPoint start, QPoint end)
{
  this->path =path;
  this->start = start;
  this->end = end;
  this->position = start;
  theEnd = false;
}

Route::Route(Path path)
{
  this->path =path;
  theEnd = false;
}

Route::Path Route::getRoutePath(){
  return path;
}

QPoint Route::getNextPoint(int speed){

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
  if((QRect(position,end).height()<2 || QRect(position,end).width()<2) && path == Path::Line){
      position = end;
      theEnd = true;
    }else{
      if(path== Path::Line){
          dx = (end.x() - start.x())/speed;
          dy = (end.y() - start.y())/speed;
        }
      if(path== Path::Stay){
          if(position.x()-end.x() <= -4){
              dx = dx +speed/30;
            }else{
                  dx = dx - speed/30;
            }
        }
      position = QPoint(static_cast<int>(position.x()+dx),static_cast<int>(position.y()+dy));
    }
  return position;
}

QPoint Route::getNextPoint(int speed, QPoint position){
 this->position = position;
 return getNextPoint(speed);
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
    position.setX(positionObject.value("x").toInt());
    position.setY(positionObject.value("y").toInt());
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
    positionObject.insert("x",position.x());
    positionObject.insert("y",position.y());

    json["start"] = startObject;
    json["end"] = endObject;
    json["position"] = positionObject;
}
