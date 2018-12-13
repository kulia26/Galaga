
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "route.h"

class GameObject
{
public:
  enum class Type{Player, Enemy, Explosion, Shot};
  enum class Animation {MoveDownRight,Stay};

  explicit GameObject();
  virtual ~GameObject();

  virtual void makeFramesFromPixmap();
  virtual void animate(Animation type);
  virtual void move();

  QPixmap getFrame();
  int getCurrentFrame();
  QPixmap getPixmap();
  void setPixmap(QString path);
  QRect getRect();
  void addRoute(Route* route);

  virtual void read(const QJsonObject &json);
  virtual void write(QJsonObject &json) const;
protected:
  QRect rect;
  int speed;
  GameObject::Type gameObjectType;
  QPixmap* frame;
  QPixmap pixmap;
  int framesCount;
  QVector<QPixmap*> frames;
  Route* currentRoute;
  QVector<Route*> routes;
private:
  QString imagePath;
};

#endif // GAMEOBJECT_H
