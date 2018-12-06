#include "animated.h"
#include <QVector>
#include <QPixmap>
#include <iostream>


Animated::Animated()
{
  framesCount = 0;
}


void Animated::makeFramesFromPixmap(QPixmap* pixmap, GameObjectType gameObject){
  if(gameObject == GameObjectType::Enemy){
      for(int i=0; i<9;i++){
          frames.push_back(new QPixmap(pixmap->copy(16*i,0,16,10)));
      }
    }
  if(gameObject == GameObjectType::Explosion){
      for(int i=0; i<9;i++){
          frames.push_back(new QPixmap(pixmap->copy(30*i,0,30,24)));
      }
    }
  frame = frames.first();
  std::cout << frames.length()<<std::endl;


}

void Animated::animate(int delay, Type type, GameObjectType gameObject){
if(framesCount % delay == 0 && type == Type::Stay && gameObject == GameObjectType::Enemy){
      if(frames.indexOf(frame)==7){
        frame = frames[6];
      }
      else{
       frame = frames[7];
      }
  }
if(gameObject == GameObjectType::Explosion && framesCount % delay == 0){
    int i = frames.indexOf(frame);
    frame = frames[++i];
}
if(framesCount > 1000){
    framesCount = 0;
  }
framesCount++;
}

QPixmap Animated::getFrame(){
return *frame;
}

int Animated::getFramesCount(){
return frames.indexOf(frame);
}
