#include "shot.h"
#include "gameobject.h"
#include<iostream>

Shot::Shot(QRect rect, Route::Path path):GameObject()
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
      if(path == Route::Path::Bottom){
      pixmap = pixmap.transformed(QTransform().rotate(180));
}
  speed = 20;
  addRoute(path);
  currentRoute->setStart();
}

Shot::~Shot()
{
std::cout << "destruct shot"<< std::endl;
}

void Shot::move()
{
  rect.moveTo(currentRoute->getNextPoint(speed));
}
