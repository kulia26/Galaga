#include "shot.h"

Shot::Shot(QRect rect)
{
  this->rect = rect;
  pixmap = QPixmap(":/images/images/sprites.png").copy(QRect(222,213,3,6));
}
void Shot::move(GameObject::Direction direction)
{
  if(direction == GameObject::Direction::top){
        rect.moveTop(rect.y() - 10);
    }
}
