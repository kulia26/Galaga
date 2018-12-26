#include "explosion.h"
#include "iostream"

Explosion::Explosion(QPoint point):GameObject()
{
  gameObjectType = Type::Explosion;
  pixmap = QPixmap(":/images/images/ExplosionSprites.png");
  makeFramesFromPixmap();
  rect  = QRect(point.x()-24,point.y()-24,frame->width()*3,frame->height()*3);
}

Explosion::~Explosion()
{
  std::cout << "destruct explosion"<< std::endl;
}

void Explosion::animate(Animation type){
  if(framesCount % 1 == 0){
      if(frames.indexOf(frame) != 4){
          frame = frames[frames.indexOf(frame)+1];
        }
  }
  if(framesCount > 1000){
      framesCount = 0;
  }
  framesCount++;
}


void Explosion::makeFramesFromPixmap(){
  for(int i=0; i<5;i++){
      frames.push_back(new QPixmap(pixmap.copy(30*i,0,30,24)));
    }
  if(frames.isEmpty()){
      frame = &pixmap;
    }else{
      frame = frames.first();
    }
}

void Explosion::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(this->getRect(),this->getFrame());
}
