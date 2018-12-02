#include "shot.h"

Shot::Shot(QRect rect)
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
  speed = 10;
}

void Shot::move()
{
  rect.moveTop(rect.y() - speed);
}
