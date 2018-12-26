#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QObject>
#include <QRect>
#include <QPixmap>
#include "route.h"
#include <memory>
#include <QPainter>
#include <memory>
#include "drawed.h"

class GameObject: public Drawed
{
public:
  enum class Type{Player, Enemy, Explosion, Shot};

  GameObject() = default;
  virtual ~GameObject() = default;

  virtual void move();
  void draw(std::shared_ptr<QPainter> painter);

  int getCurrentFrame();
  void setPixmap(QString path);
  QPoint getPoint();
  void addRoute(Route::Path path, QPoint end);//
  void addRoute(Route::Path path);//
  int getFramesCount();

  virtual void read(const QJsonObject &json);
  virtual void write(QJsonObject &json) const;

protected:
  double speed;
  GameObject::Type gameObjectType;
  QRect rect;//
  QPixmap pixmap;
  QPixmap* frame;
  QVector<QPixmap*> frames;
  int framesCount;
  Route* currentRoute;
  QVector<Route*> routes;

private:
  QString imagePath;
};

#endif // GAMEOBJECT_H
