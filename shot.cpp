#include "shot.h"
#include "gameobject.h"

Shot::Shot(QRect rect):GameObject()
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
  speed = 10;
}

void Shot::move()
{
  rect.moveTop(rect.y() - speed);
}
