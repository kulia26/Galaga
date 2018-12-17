
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "route.h"
#include <memory>

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
  virtual void fire();

  QPixmap getFrame();
  int getCurrentFrame();
  QPixmap getPixmap();
  QVector<std::shared_ptr<class Shot>> getShots();
  void setPixmap(QString path);
  QRect getRect();
  void addRoute(Route::Path path, QPoint end);
  void addRoute(Route::Path path);
  int getFramesCount();

  virtual void read(const QJsonObject &json);
  virtual void write(QJsonObject &json) const;

protected:
  QRect rect;
  double speed;
  GameObject::Type gameObjectType;
  QPixmap* frame;
  QPixmap pixmap;
  int framesCount;
  QVector<QPixmap*> frames;
  Route* currentRoute;
  QVector<Route*> routes;
  QVector<std::shared_ptr<Shot>> shots;
private:
  QString imagePath;
};

#endif // GAMEOBJECT_H
