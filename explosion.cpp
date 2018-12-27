#include "explosion.h"
#include "iostream"

Explosion::Explosion(QPoint point)
{
  pixmap = QPixmap(":/images/images/ExplosionSprites.png");
  makeFramesFromPixmap();
  rect  = QRect(point.x()-24,point.y()-24,frame->width()*3,frame->height()*3);
  lives = 4;
}

void Explosion::animate(Animation){
hurt();
int index = frames.indexOf(frame);
frame = frames[index + 1];

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
  painter->drawPixmap(rect,*frame);
}
