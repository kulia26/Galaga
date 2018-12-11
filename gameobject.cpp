#include "gameobject.h"
#include <QJsonObject>
#include <iostream>

GameObject::GameObject()
{

}
GameObject::GameObject(QRect rect)
{
  this->rect  = rect;
}

GameObject::~GameObject()
{
  delete this;
}

void GameObject::read(const QJsonObject &json)
{
  std::cout <<"GameObject::read1"<<std::endl;
  QJsonObject rectObject = json["rect"].toObject();
  rect.setX(rectObject.value("x").toInt());
  rect.setY(rectObject.value("y").toInt());
  rect.setWidth(rectObject.value("width").toInt());
  rect.setHeight(rectObject.value("height").toInt());
  std::cout <<"GameObject::read2"<<std::endl;
}

void GameObject::write(QJsonObject &json) const
{

  QJsonObject rectObject;
  rectObject.insert("x",rect.x());
  rectObject.insert("y",rect.y());
  rectObject.insert("width",rect.width());
  rectObject.insert("height",rect.height());
  json["rect"] = rectObject;

}
QRect GameObject::getRect()
{
  return rect;
}




