#include "explosion.h"

Explosion::Explosion(QPoint point):GameObject()
{
  gameObjectType = Type::Explosion;
  pixmap = QPixmap(":/images/images/ExplosionSprites.png");
  makeFramesFromPixmap();
  rect  = QRect(point.x()-24,point.y()-24,frame->width()*3,frame->height()*3);
}

void Explosion::animate(Animation type){
  if(framesCount % 2 == 0){
      frame = frames[frames.indexOf(frame)+1];
  }
  if(framesCount > 1000){
      framesCount = 0;
  }
  framesCount++;
}


void Explosion::makeFramesFromPixmap(){
  frames.clear();
  for(int i=0; i<5;i++){
      frames.push_back(new QPixmap(pixmap.copy(30*i,0,30,24)));
    }
  if(frames.isEmpty()){
      frame = &pixmap;
    }else{
      frame = frames.first();
    }
}
