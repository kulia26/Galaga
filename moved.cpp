#include "moved.h"
#include <cmath>
#include <QRect>
#include <iostream>

Moved::Moved(Path _path, QPoint _start, QPoint _end, int _speed)
{
  path =_path;
  start = _start;
  end = _end;
  speed = _speed;
  position = _start;
  theEnd = false;

}

Moved::Moved()
{
  path = Path::None;

}
Moved::~Moved()
{

}

void Moved::move()
{

}

QPoint Moved::getNextPoint(){
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
              dx = dx +speed/3;
            }else{
                  dx = dx - speed/3;
            }
        }
      position = QPoint(static_cast<int>(position.x()+dx),static_cast<int>(position.y()+dy));
    }
  return position;
}


bool Moved::isEnded(){
  return theEnd;
}

Moved::Path Moved::getMovedPath(){
  return path;
}

void Moved::read(const QJsonObject &json)
{
  std::cout <<"Moved::read1"<<std::endl;
    speed = json["speed"].toInt();
    path = Moved::Path(json["path"].toInt());
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
    std::cout <<"Moved::read2"<<std::endl;
}

void Moved::write(QJsonObject &json) const
{
    json["speed"] = speed;
    json["path"] = path;
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
