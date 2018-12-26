#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "route.h"
#include <memory>
#include <QPainter>


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
  virtual void draw(std::shared_ptr<QPainter> painter);

  QPixmap getFrame();
  int getCurrentFrame();
  QPixmap getPixmap();
  QVector<std::shared_ptr<class Shot>> getShots();
  void setPixmap(QString path);
  QRect getRect();
  void addRoute(Route::Path path, QPoint end);
  void addRoute(Route::Path path);
  int getFramesCount();
  bool collide(std::shared_ptr<GameObject> object);
  bool collide(GameObject* object);

  virtual void read(const QJsonObject &json);
  virtual void write(QJsonObject &json) const;

protected:
  double speed;
  GameObject::Type gameObjectType;
  QRect rect;
  QPixmap pixmap;
  QPixmap* frame;
  QVector<QPixmap*> frames;
  int framesCount;
  Route* currentRoute;
  QVector<Route*> routes;
  QVector<std::shared_ptr<Shot>> shots;

private:
  QString imagePath;
};

#endif // GAMEOBJECT_H
