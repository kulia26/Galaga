#include "gameobject.h"

GameObject::GameObject()
{

}

GameObject::~GameObject()
{

}
QRect GameObject::getRect()
{
  return rect;
}

QPixmap GameObject::getPixmap()
{
  return pixmap;
}

void GameObject::move(Direction direction)
{

}
