#include "explosion.h"
#include "iostream"

Explosion::Explosion(QPoint point, Type type)
{
  this->expType = type;
  this->gameObjectType = GameObject::Type::Explosion;
  if(expType == Type::EnemyDie){
      pixmap = QPixmap(":/images/images/ExplosionSprites.png");
      lives = 5;
      makeFramesFromPixmap();
      rect  = QRect(point.x()-30,point.y()-30,frame->width()*3,frame->height()*3);

    }else{
      pixmap = QPixmap(":/images/images/ExplosionSprites2.png");
      lives = 4;
      makeFramesFromPixmap();
      rect  = QRect(point.x()-10,point.y()-10,frame->width()*3,frame->height()*3);
    }

}

void Explosion::animate(Animation){

if(this->isAlive() && frame != frames.last()){
    int index = frames.indexOf(frame);
    frame = frames[index + 1];
  }
if(!this->isAlive()){
    frame = frames.last();
  }
hurt();
}

void Explosion::makeFramesFromPixmap(){
  frames.reserve(5);
  for(int i=0; i<lives;i++){
      frames.push_back(new QPixmap(pixmap.copy(30*i,0,30,24)));
    }
  QPixmap copy  = frames.first()->copy();
  frames.push_front(&copy);
  frame = frames.first();
}

void Explosion::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(rect,*frame);
}

void Explosion::move()
{

}

void Explosion::reuse(QPoint point)
{
  rect.moveTopLeft(point - QPoint(30,30));
  if(this->expType == Type::PlayerDie){
      rect.moveTopLeft(point-QPoint(10,10));
    }
  if(this->expType == Type::EnemyDie){
      lives = 5;
    }else{
      lives = 4;
    }
  frame = frames.first();
}

Explosion::Type Explosion::getType()
{
  return this->expType;
}
