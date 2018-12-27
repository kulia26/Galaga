#include "shot.h"
#include "gameobject.h"
#include<iostream>

Shot::Shot(QRect rect, Route::Path path)
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
  if(path == Route::Path::Bottom){
      pixmap = pixmap.transformed(QTransform().rotate(180));
      speed = 20;
    }else{
      speed = -20;
    }
}

void Shot::move()
{
  rect = QRect(rect.left(),rect.top()+qRound(speed),rect.width(),rect.height());
  if (rect.y() < -50 || rect.y() > 850){
      this->hurt();
    }
}

