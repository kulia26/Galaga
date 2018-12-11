#include "animated.h"
#include <QVector>
#include <QPixmap>
#include <iostream>
#include <QJsonObject>


Animated::Animated(GameObject::Type gameObject)
{
  this->gameObject = gameObject;
}

Animated::Animated()
{

}

Animated::Animated(QPixmap pixmap)
{
  this->pixmap = pixmap;

}

Animated::Animated(GameObject::Type gameObject, QPixmap pixmap)
{
  this->gameObject = gameObject;
  this->pixmap = pixmap;

}


void Animated::read(const QJsonObject &json)
{
    std::cout <<"Animated::read1"<<std::endl;
    imagePath = json["imagePath"].toString();
    framesCount = 0;
    delay = json["delay"].toInt();
    gameObject = GameObject::Type(json["gameObject"].toInt());

    pixmap = QPixmap(imagePath);
    makeFramesFromPixmap(&pixmap);
    std::cout <<"Animated::read2"<<std::endl;
}

void Animated::write(QJsonObject &json) const
{
  json["imagePath"] = imagePath;
  json["framesCount"] = 0;
  json["delay"] = delay;
  json["gameObject"] = gameObject;
}

void Animated::makeFramesFromPixmap(QPixmap* pixmap){
  frames.clear();
  if(gameObject == GameObject::Type::Enemy){
      for(int i=0; i<9;i++){
          frames.push_back(new QPixmap(pixmap->copy(16*i,0,16,10)));
      }
    }
  if(gameObject == GameObject::Type::Explosion){
      for(int i=0; i<5;i++){
          frames.push_back(new QPixmap(pixmap->copy(30*i,0,30,24)));
      }
    }
  if(!frames.isEmpty()){
      frame = frames.first();
    }else{
      frame = pixmap;
    }
}

void Animated::animate(int delay, Type type, GameObject::Type gameObject){
this->delay = delay;
if(framesCount % delay == 0 && type == Type::Stay && gameObject == GameObject::Type::Enemy){
      if(frames.indexOf(frame)==7){
        frame = frames[6];
      }
      else{
       frame = frames[7];
      }
}
if(framesCount % delay == 0 && type == Type::MoveDownRight && gameObject == GameObject::Type::Enemy){
      if(frames.indexOf(frame)==5){
        frame = frames[4];
      }
      else{
       frame = frames[5];
      }
}
if(gameObject == GameObject::Type::Explosion && framesCount % delay == 0){
    frame = frames[frames.indexOf(frame)+1];

}
if(framesCount > 1000){
    framesCount = 0;
  }
framesCount++;
}

QPixmap Animated::getFrame(){
return *frame;
}

int Animated::getCurrentFrame(){
return frames.indexOf(frame);
}

QPixmap Animated::getPixmap()
{
  return pixmap;
}

void Animated::setPixmap(QString path)
{
  pixmap = QPixmap(path);
  this->imagePath = path;
}
