#include "animated.h"
#include <QVector>
#include <QPixmap>
#include <iostream>


Animated::Animated(GameObject::Type gameObject)
{
  this->gameObject = gameObject;
}


void Animated::makeFramesFromPixmap(QPixmap* pixmap){
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
  frame = frames.first();
}

void Animated::animate(int delay, Type type, GameObject::Type gameObject){
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
