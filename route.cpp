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
  q=M_PI/2;
}

Route::Route(Path path)
{
  this->path =path;
  theEnd = false;
}

Route::Route(Path path, QPoint position)
{
  this->position = position;
  this->path =path;
  theEnd = false;
}

Route::Path Route::getRoutePath(){
  return path;
}

QPoint Route::getNextPoint(double speed){

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
  if(QRect(QRect(end,QSize(30,30)) & QRect(position,QSize(30,30))).size() != QSize(0,0) && path == Path::Line){
      position = end;
      theEnd = true;
      std::cout << QRect(position,end).width()<< std::endl;
    }else{
      if(path== Path::Line){

              dx = (end.x() - start.x())*speed/3000;
              dy = (end.y() - start.y())*speed/3000;

          std::cout << dx << std::endl;
        }
      if(path== Path::Stay){
          if(position.x()-end.x() <= -4){
              dx = dx + 0.75;
            }else{
                  dx = dx - 0.75;
            }
        }
      if(path == Path::Sin){
          q = q + 0.3;
          double t = q;
          dx =  cos(t)*10;
          dy =  sin(t)*sin(t)*10;
        }
      if(path == Path::Lemniscate){
          q = q + 0.08*speed/50;
          double t = q;
          dx =  6*sqrt(2)*cos(t);
          dy =  18*sqrt(2)*cos(t)*sin(t);


          if(q > M_PI/2 and  q < M_PI){
              dy = -dy;
            }
          if(q > M_PI and q < 3*M_PI/2){
              dy = -dy;
            }
          if(q > 3*M_PI/2 and q < 2*M_PI){
            }
          if(q >= 2*M_PI){
              theEnd = true;
              return position;
            }

          position = QPoint(static_cast<int>(position.x()+static_cast<int>(dx)),static_cast<int>(position.y()+static_cast<int>(dy)));
          return position;
        }
      position = QPoint(static_cast<int>(position.x()+dx),static_cast<int>(position.y()+dy));
    }


  return position;
}

QPoint Route::getNextPoint(double speed, QPoint position){
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
