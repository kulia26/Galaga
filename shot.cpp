#include "shot.h"
#include "gameobject.h"
#include<iostream>

Shot::Shot(QRect rect, Route::Path path)
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
      if(path == Route::Path::Bottom){
      pixmap = pixmap.transformed(QTransform().rotate(180));
}
  speed = 20;
  addRoute(path);
  //currentRoute->setStart();
}

void Shot::move()
{
  rect.moveTo(currentRoute->getNextPoint(speed));
}

void Shot::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(rect,this->pixmap);
}
