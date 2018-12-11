#include "enemy.h"
#include "animated.h"
#include <cmath>
#include <iostream>
#include <QPixmap>
#include <QRandomGenerator>
#include "moved.h"
#include <QJsonObject>
#include <QJsonArray>
Enemy::Enemy(Enemy::Type type, QPoint _start, QPoint _end,int _speed):GameObject(),Animated(GameObject::Type::Enemy), Moved()
{
  start = _start;
  end = _end;
  speed = _speed;
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

  makeFramesFromPixmap(&pixmap);
  rect  = QRect(start.x(),start.y(),frame->width()*3,frame->height()*3);

  tracks.push_back(new Moved(Moved::Path::Line,start,end,speed));
  tracks.push_back(new Moved(Moved::Path::Stay,end,end,2));

  currentMoved  = tracks.first();
}
Enemy::Enemy():GameObject(),Animated(GameObject::Type::Enemy), Moved()
{

}
void Enemy::move()
{
  rect.moveTo(currentMoved->getNextPoint());
  if(currentMoved->getMovedPath()==Moved::Path::Line){
      animate(4, Animated::Type::MoveDownRight, GameObject::Type::Enemy);
    }
  if(currentMoved->getMovedPath()==Moved::Path::Stay){
      animate(8, Animated::Type::Stay, GameObject::Type::Enemy);
    }
  if(currentMoved->isEnded()){
      int i = tracks.indexOf(currentMoved);
      if((i+1)!=tracks.length()){
          currentMoved = tracks[i+1];
        }
    }
}

void Enemy::read(const QJsonObject &json)
{
    GameObject::read(json);
    Moved::read(json);
    Animated::read(json);


    type = Enemy::Type(json["type"].toInt());
    tracks.clear();
        QJsonArray tracksArray = json["tracks"].toArray();
        for (int trackIndex = 0; trackIndex < tracksArray.size(); trackIndex++) {

            QJsonObject trackObject = tracksArray[trackIndex].toObject();
            std::cout << trackIndex<<std::endl;
            Moved* track = new Moved();
            track->read(trackObject);
            tracks.push_back(track);
        }
    std::cout<<tracks.length()<<std::endl;
    currentMoved  = tracks.first();
}

void Enemy::write(QJsonObject &json) const
{
  GameObject::write(json);
  Moved::write(json);
  Animated::write(json);

  json["type"] = type;
  QJsonArray tracksArray;
     foreach (const Moved* track, tracks) {
         QJsonObject trackObject;
         track->write(trackObject);
         tracksArray.append(trackObject);
     }
  json["tracks"] = tracksArray;
}
