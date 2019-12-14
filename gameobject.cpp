#include "gameobject.h"
#include "route.h"
#include <QJsonObject>
#include <iostream>


void GameObject::hurt(){
  --lives;
}

bool GameObject::isAlive(){
  return lives  > 0;
}
GameObject::Type GameObject::getType(){
  return gameObjectType;
}
void GameObject::draw(std::shared_ptr<QPainter> painter)
{
  painter->drawPixmap(rect,this->pixmap);
}

void GameObject::read(const QJsonObject &json)
{

  speed = json["speed"].toInt();

  std::cout <<"GameObject::read1"<<std::endl;
  gameObjectType = GameObject::Type(json["gameObject"].toInt());
  QJsonObject rectObject = json["rect"].toObject();
  rect.setX(rectObject.value("x").toInt());
  rect.setY(rectObject.value("y").toInt());
  rect.setWidth(rectObject.value("width").toInt());
  rect.setHeight(rectObject.value("height").toInt());
  std::cout <<"GameObject::read2"<<std::endl;

  std::cout <<"Animated::read1"<<std::endl;
  imagePath = json["imagePath"].toString();
  //framesCount = 0;
  pixmap = QPixmap(imagePath);
  //makeFramesFromPixmap();
  std::cout <<"Animated::read2"<<std::endl;
}

void GameObject::write(QJsonObject &json) const
{
  json["speed"] = speed;

  json["gameObject"] = static_cast<int>(gameObjectType);
  QJsonObject rectObject;
  rectObject.insert("x",rect.x());
  rectObject.insert("y",rect.y());
  rectObject.insert("width",rect.width());
  rectObject.insert("height",rect.height());
  json["rect"] = rectObject;

  json["imagePath"] = imagePath;
  json["framesCount"] = 0;

}

QPoint GameObject::getPoint()
{
  return rect.topLeft();
}

void GameObject::moveRectTo(QPoint point)
{
  rect.moveTo(point);
}


void GameObject::setPixmap(QString path)
{
  pixmap = QPixmap(path);
  this->imagePath = path;
}


void GameObject::addRoute(Route::Path path, QPoint end)
{
  Route* route = new Route(this, path, end);
  routes.push_back(route);
  if(routes.first()==route){
      currentRoute = routes.first();
      currentRoute->setStart();
    }
}

void GameObject::addRoute(Route::Path path)
{
  Route* route = new Route(this, path);
  routes.push_back(route);
  if(routes.first()==route){
      currentRoute = routes.first();
    }
}




