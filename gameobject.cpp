#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{
  delete this;
}


QRect GameObject::getRect()
{
  return rect;
}

QPixmap GameObject::getPixmap()
{
  return pixmap;
}

void GameObject::move()
{

}

void GameObject::setSpeed(int _speed)
{
  speed = _speed;
}
