#include "explosion.h"

Explosion::Explosion(QPoint point):GameObject (), Animated(GameObject::Explosion)
{
  pixmap = QPixmap(":/images/images/ExplosionSprites.png");
  makeFramesFromPixmap(&pixmap);
  rect  = QRect(point.x()-24,point.y()-24,frame->width()*3,frame->height()*3);
}
void Explosion::move()
{
  animate(1, Animated::Type::Stay, GameObject::Type::Explosion);
}
