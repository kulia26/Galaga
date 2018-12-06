#include "explosion.h"

Explosion::Explosion(QPoint point)
{
  pixmap = QPixmap(":/images/images/ExplosionSprites.png");
  makeFramesFromPixmap(&pixmap, GameObjectType::Explosion);
  rect  = QRect(point.x()-24,point.y()-24,frame->width()*3,frame->height()*3);
}
void Explosion::move()
{
  animate(1, Animated::Type::Stay, GameObjectType::Explosion);
}
